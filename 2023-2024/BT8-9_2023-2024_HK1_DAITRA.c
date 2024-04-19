#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE SPEED     PIN_B1
#DEFINE ON_OFF    PIN_B2

UNSIGNED INT8 LEVEL=1;
UNSIGNED INT1 STATUS=0; //0 OFF
                        //1 ON

VOID MAIN()
{
   SET_TRIS_D(0X00);
   SET_TRIS_B(0XFF);
   //SETUP PWM
   SETUP_TIMER_2(T2_DIV_BY_16,99,1); //PR2=99 => MAXDUTY=(99+1)X4=400
                                      //5 CAP DO 1-2-3-4-5 
   SET_TIMER2(0);
   SETUP_CCP1(CCP_PWM); //RC2
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN ON OFF
      IF(INPUT(ON_OFF)==0)
      {
         DELAY_MS(20);
         IF(INPUT(ON_OFF)==0)
         {
            STATUS=~STATUS;
            LEVEL=1;
            WHILE(INPUT(ON_OFF)==0);
         }
      }
      //KIEM TRA NUT NHAN SPEED
      IF(INPUT(SPEED)==0)
      {
         DELAY_MS(20);
         IF(INPUT(SPEED)==0)
         {
            LEVEL++;
            WHILE(INPUT(SPEED)==0);
         }
      }
      IF(LEVEL>5)    LEVEL=1;
      IF(STATUS==0)
      {
         //OFF
         SETUP_CCP1(CCP_OFF); 
      }
      ELSE
      {
         //ON
         //SETUP LAI
         SETUP_CCP1(CCP_PWM);
         //CHAY LAI CAP DO 1
         //LEVEL=1;
         IF       (LEVEL==1)  SET_PWM1_DUTY((UNSIGNED INT16)40);  //10%
         ELSE IF  (LEVEL==2)  SET_PWM1_DUTY((UNSIGNED INT16)80);  //20%
         ELSE IF  (LEVEL==3)  SET_PWM1_DUTY((UNSIGNED INT16)200); //50%
         ELSE IF  (LEVEL==4)  SET_PWM1_DUTY((UNSIGNED INT16)320); //80%
         ELSE IF  (LEVEL==5)  SET_PWM1_DUTY((UNSIGNED INT16)400); //100%
      }
   }
}

