#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))

void main ()
{
  clr_bit(PORTD, 2)
}
