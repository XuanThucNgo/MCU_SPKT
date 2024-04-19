#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)

CONST UNSIGNED INT8 MA7DOAN[10] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

#DEFINE SPEED     PIN_B1
#DEFINE RUN_STOP  PIN_B2 

UNSIGNED INT8 LEVEL=0;
INT1 STATUS=0; //0 STOP
               //1 RUN

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   
   SETUP_TIMER_2(T2_DIV_BY_16,124,1);  //PR2=124 => MAXDUTY=(124+1)X4=500  
                                       //4 CAP DO 1-2-3-4      500/4=125
                                       //MOI CAP DO TUONG UNG VOI 125 DUTY
   SETUP_CCP1(CCP_PWM); //RC2
   SET_TIMER2(0);
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   OUTPUT_D(MA7DOAN[0]);
   
   WHILE(TRUE)
   {
   
      //KIEM TRA NUT NHAN SPEED
      IF(INPUT(SPEED)==0)
      {
         DELAY_MS(10);
         IF(INPUT(SPEED)==0)
         {
            LEVEL++;
            WHILE(INPUT(SPEED)==0);
         }
      }
      IF(LEVEL>4)    LEVEL=1;
      
      //KIEM TRA NUT NHAN RUN_STOP
      IF(INPUT(RUN_STOP)==0)
      {
         DELAY_MS(10);
         IF(INPUT(RUN_STOP)==0)
         {
            STATUS=~STATUS;
            WHILE(INPUT(RUN_STOP)==0);
         }
      }
      
      //KIEM TRA RUN/STOP
      IF(STATUS==0)
      {
         //STOP
         SETUP_CCP1(CCP_OFF);
      }
      ELSE
      {
         //RUN
         SETUP_CCP1(CCP_PWM); //SETUP LAI
         SET_PWM1_DUTY((UNSIGNED INT16)LEVEL*125);
         OUTPUT_D(MA7DOAN[LEVEL]);
      }
   }
   
}

