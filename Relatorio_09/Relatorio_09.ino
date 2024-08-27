#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>

#define CAPACIDADE 8

uint8_t esteira1 = 0b11111111;
uint8_t esteira2 = 0b00000000;

#define LED_VERMELHO_1_PINO 2 // Pino digital 2 (PORTD2)
#define LED_VERMELHO_2_PINO 3 // Pino digital 3 (PORTD3)
#define LED_AMARELO_PINO 4    // Pino digital 4 (PORTD4)
#define MOTOR1_PINO 9         // Pino digital 9 (PORTB1)
#define MOTOR2_PINO 10        // Pino digital 10 (PORTB2)
#define BOTAO_S1_PINO 5       // Pino digital 5 (PORTD5)
#define BOTAO_S2_PINO 6       // Pino digital 6 (PORTD6)

bool verificarDefeito(uint8_t esteira, int posicao) {
    return (esteira >> posicao) & 1;
}

void inicializar() {
    // Configurar LEDs como saídas
    DDRD |= (1 << LED_VERMELHO_1_PINO) | (1 << LED_VERMELHO_2_PINO) | (1 << LED_AMARELO_PINO); 

    // Configurar pinos dos motores como saídas
    DDRB |= (1 << MOTOR1_PINO) | (1 << MOTOR2_PINO);

    // Configurar botões como entradas
    DDRD &= ~((1 << BOTAO_S1_PINO) | (1 << BOTAO_S2_PINO));

    // Ativar pull-up nos pinos dos botões
    PORTD |= (1 << BOTAO_S1_PINO) | (1 << BOTAO_S2_PINO);

    // Configurar interrupção externa INT0 (Botão S1)
    EICRA |= (1 << ISC01);  // Configura interrupção na borda de descida
    EIMSK |= (1 << INT0);   // Habilita a interrupção externa INT0

    // Configurar interrupção de mudança de estado (Botão S2)
    PCICR |= (1 << PCIE2);  // Habilita interrupção para o PORTD (PCINT16 a PCINT23)
    PCMSK2 |= (1 << PCINT21); // Habilita interrupção para o pino PCINT21 (correspondente ao pino digital 6)
}

void acenderLEDVermelho(int pino) {
    PORTD |= (1 << pino); // Acende o LED VERMELHO
}

void acenderLEDAmarelo() {
    PORTD |= (1 << LED_AMARELO_PINO); // Acende o LED AMARELO
}

void moverEsteira() {
    uint8_t primeiraPosicao = 1 << (CAPACIDADE - 1);
    uint8_t ultimaPosicao = 1;

    // Verifica se há peças defeituosas na última posição da esteira 1
    if ((esteira1 & ultimaPosicao) == ultimaPosicao) {
        esteira2 |= primeiraPosicao;
        acenderLEDVermelho(LED_VERMELHO_1_PINO);
        printf("LED VERMELHO aceso! Peça defeituosa despachada para a próxima esteira.\n");
    }

    // Move a esteira 1 para a direita
    for (int i = CAPACIDADE - 1; i > 0; i--) {
        if ((esteira1 & (1 << i)) != 0)
            esteira1 |= (1 << (i - 1));
        else
            esteira1 &= ~(1 << (i - 1));
    }
    esteira1 |= 1;

    // Aciona o motor 1 (esteira 1)
    PORTB |= (1 << MOTOR1_PINO);
}

void recolherDefeituosas() {
    printf("Recolhendo peças defeituosas...\n");
    while (esteira2 != 0) {
        if (esteira2 & 0b10000000) {
            acenderLEDAmarelo();
            printf("LED AMARELO aceso! Peça defeituosa recolhida.\n");
        }
        esteira2 <<= 1;
    }

    // Aciona o motor 2 (esteira 2)
    PORTB |= (1 << MOTOR2_PINO);
}

ISR(INT0_vect) {
    // Rotina de interrupção para o Botão S1
    moverEsteira();
}

ISR(PCINT2_vect) {
    // Rotina de interrupção para o Botão S2
    recolherDefeituosas();
}

int main() {
    inicializar();

    sei(); // Habilita as interrupções globais

    while (1) {
   
    }

    return 0;
}
