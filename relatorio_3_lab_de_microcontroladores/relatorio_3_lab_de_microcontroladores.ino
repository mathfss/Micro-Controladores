int main (){

  for (;;){

     DDRC = 0b00000000; // DDRX DIZ SE É SAIDA (1) OU ENTRADA (0) 
     DDRD = 0b00001110;
     DDRB = 0b00000000;
     PORTB = 0b00001110; // PORTX COLOCA NIVEL LOGICO ALTO (1) OU BAIXO (0)
     PIND = 0b10000100;

     short int receber = PIND; 0b00000001;
     if (recebe = 0b00000001)
     {
      //Botao foi pressionado
      PORTD = 0b10000100;
     }
    
  }
  
}
