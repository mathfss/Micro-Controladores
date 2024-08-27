#define set_bit(Y, bit_x) (Y|=(1<<bit_x)

void main ()
{
  set_bit(PORTD, 2)
}
