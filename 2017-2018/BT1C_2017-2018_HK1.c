#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE ON_OFF    PIN_B0
INT1 STATUS=0;    //O OFF
                  //1 ON

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   //SETUP PWM
   //PR2=124 -> MAXDUTY=500
   SETUP_TIMER_2(T2_DIV_BY_16,124,1);
   SETUP_CCP2(CCP_PWM);//RC1
   SET_TIMER2(0);
   SET_PWM2_DUTY(0); //BAN DAU TAT
   WHILE(TRUE)
   {
      IF(INPUT(ON_OFF)==0)
      {
         DELAY_MS(10);
         IF(INPUT(ON_OFF)==0)
         {
            STATUS=~STATUS;
            WHILE(INPUT(ON_OFF)==0);
         }
      }
      IF(STATUS==1)
      {
         //ON
         SETUP_CCP2(CCP_PWM); //SETUP LAI
         SET_PWM2_DUTY(350);
      }
      ELSE
      {
         //OFF
         SETUP_CCP2(CCP_OFF);
      }
   }
   
}

