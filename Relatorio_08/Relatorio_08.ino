#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_PIN_5 PD5
#define LED_PIN_6 PD6
#define LED_PIN_7 PD7
#define LED_PIN_15 PB1

// Manipulador de interrupção para PCINT0
ISR(PCINT0_vect) {
   short int lpb2 = PINB & (1 << PCINT2);
  if (lpb2 == (1 << PCINT2)){
   PORTD |= (1 << LED_PIN_6); 
   _delay_ms(500); 
   PORTD &= ~(1 << LED_PIN_6); 
  }
  short int lpb0 = PINB & (1 << PCINT0);
  if (lpb0 == (1 << PCINT0)){
    PORTD |= (1 << LED_PIN_7); 
   _delay_ms(1000); 
   PORTD &= ~(1 << LED_PIN_7); 
  }
}
// Manipulador de interrupção para PCINT2
ISR(PCINT2_vect) {
    PORTB |= (1 << LED_PIN_15); 
   _delay_ms(2000); 
   PORTB &= ~(1 << LED_PIN_15);
}
// Manipulador de interrupção para PCINT20

int main(void) {
   DDRD |= (1 << LED_PIN_5) | (1 << LED_PIN_6) | (1 << LED_PIN_7);
   DDRB |= (1 << LED_PIN_15);
   // Habilita interrupção no grupo PCINT2
   PCICR |= (1 << PCIE2);
   // Habilita PCINT no pino PD4 -> PCINT20
   PCMSK2 |= (1 << PCINT20);
   // Habilita Interrupções globais
   sei();
   for (;;) {
       PORTD ^= (1 << LED_PIN_5); 
       _delay_ms(250); 
   }
}
