#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE RAND PIN_B0

CONST UNSIGNED INT8 MA7DOAN[10] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

UNSIGNED INT8 I,LEVEL=0;

VOID MAIN()
{
   SET_TRIS_D(0X00);
   SET_TRIS_B(0X01);
   //SETUP PWM
   SETUP_TIMER_2(T2_DIV_BY_16,124,1); //PR2=124 => MAXDUTY=(124+1)X4=500
                                      //10 CAP DO 0-1-2-3-4-5-6-7-8-9 
                                      //MOI CAP TUONG UNG VOI DUTY=50
   SET_TIMER2(0);
   SETUP_CCP1(CCP_PWM); //RC2
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   OUTPUT_D(MA7DOAN[0]);
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN RAND
      FOR(I=0;I<10;I++)
      {
         IF(INPUT(RAND)==0)
         {
            DELAY_MS(20);
            IF(INPUT(RAND)==0)
            {
               OUTPUT_D(MA7DOAN[I]);
               LEVEL=I;
               //BREAK;
               WHILE(INPUT(RAND)==0);
            }
         }
      }
      SET_PWM1_DUTY((UNSIGNED INT16)LEVEL*50);
   }
}

