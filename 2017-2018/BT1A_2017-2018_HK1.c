#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE SW        PIN_B0
#DEFINE PULSE     PIN_C1

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   WHILE(TRUE)
   {
      IF(INPUT(SW)==0)
      {
         OUTPUT_HIGH(PULSE);
         DELAY_US(700);
         OUTPUT_LOW(PULSE);
         DELAY_US(300);
      }
      ELSE
      {
         OUTPUT_LOW(PULSE);
      }
   }
}

