#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x)
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)

void main ()
{
  set_bit(PORTD, 3);
  set_bit(PORTB, 4); 
  cpl_bit(PORTD, PORTB);
}
