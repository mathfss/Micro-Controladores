/*
Inatel - EC209
Exemplo - Portão Eletrônico
Máquina de Estados

Autor: Prof. Daniel Mosca*/

#define ABERTO 0
#define ABRINDO 1
#define FECHADO 2
#define FECHANDO 3

int main (void)
{
  /*Variável que armazena o estado da máquina*/
  unsigned char estado;

  /*Variáveis que simulam a Entrada/Saída*/
  unsigned char MF, MA, SF, SA, CF, CA;

  DDRB = 0x03;

  /*Loop Infinito*/
  for (;;) {

  /*Máquina de Estados*/
      switch (estado)
      {
        case ABERTO:
            PORTB = 0b00000000;
            if(PINC & (1<<PC6) == 1)
            {
                estado = FECHANDO;
            }
        break;

        case FECHANDO:
            PORTB = 0b00000010; // ativa o segundo bit (MF)
            if (PINC & (1 << PC5)) // ve se SF esta ativado
            {
                estado = FECHADO;
            }
        break;

        case FECHADO:
            PORTB = 0b00000000; // desativa todos os bits
            if (PINC & (1 << PC4)) // ve de CA esta ativado
            {
                estado = ABRINDO;
            }
        break;

        case ABRINDO:
            PORTB = 0b00000001; // ativa o bit do MA
            if(PINC & (1 << PC3))// ve se SA ta ativado
            {
                estado = ABERTO;
            }
        break;
      }
  }
  
  return 0;
}
