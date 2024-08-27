#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y, bit_x) (Y&(1<<bit_x))

void main ()
{
  clr_bit(PORTD, 5)
  PORTD |= 0b00100000; // pull up
  int botao = tst_bit(PIND, 5);

  if(botao==(1<<PD5){
    printf("O pino esta em HIGH");
  }
  else
  {
    printf("O pino esta em LOW");
  }
}
