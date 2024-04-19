#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#BIT TMR0IF = 0X0B.2
#DEFINE ON        PIN_B0
#DEFINE OFF       PIN_B1
#DEFINE PULSE     PIN_C1

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   //SETUP_TIMER0 DINH THOI GIAN
   SETUP_TIMER_0(T0_INTERNAL|T0_DIV_8);
   //DINH THOI 0.1MS: 6 BC8
   //DINH THOI 0.7MS=0.1MSx7 -> HIGH
   //DINH THOI 0.3MS=0.1MSx3 -> LOW
   SET_TIMER0(231);
   OUTPUT_HIGH(PULSE);
   UNSIGNED INT8 COUNT;
   INT1 MODE=1;
   WHILE(TRUE)
   {
      IF(INPUT(ON)==0)     MODE=0;
      IF(INPUT(OFF)==0)    MODE=1;
      IF(MODE==0)
      {
         IF(TMR0IF==1)
         {
            //0.1MS
            COUNT++;
            SET_TIMER0(231);
            TMR0IF=0;
            
            IF(COUNT<=7)   OUTPUT_HIGH(PULSE);
            ELSE IF(COUNT<10)   OUTPUT_LOW(PULSE);
            ELSE           COUNT=0;
         }
      }
      ELSE
      {
         OUTPUT_LOW(PULSE);
      }
   }
}