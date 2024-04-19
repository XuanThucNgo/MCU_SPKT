#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=10M)

#DEFINE SW PIN_C0
#DEFINE STOP PIN_B0
#DEFINE BTN_STOP PIN_B0
#DEFINE BTN_1_6 PIN_B1
#DEFINE BTN_2_7 PIN_B2
#DEFINE BTN_3_8 PIN_B3
#DEFINE BTN_4_9 PIN_B4
#DEFINE BTN_5_10 PIN_B5

#define LCD_ENABLE_PIN  PIN_D3                                    
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                    
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                    
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>

UNSIGNED INT8 MAXSPEED=250;
INT1 STATUS=0; //0 CHAY CAP DO BEN TRAI
               //1 CHAY CAP DO BEN PHAI

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   
   LCD_INIT();
   
   SETUP_TIMER_2(T2_DIV_BY_16,124,1);  //PR2=124 => MAXDUTY=(124+1)X4=500  
                                       //10 CAP DO 1-2-3-4-5-6-7-8-9-10      500/10=50
                                       //MOI CAP DO TUONG UNG VOI 50 DUTY
   SETUP_CCP1(CCP_PWM); //RC2
   SET_TIMER2(0);
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   
   WHILE(TRUE)
   {   
      IF(INPUT(BTN_STOP)==0)
      {
         DELAY_MS(10);
         IF(INPUT(BTN_STOP)==0)
         {  
            //DUNG DONG CO
            SETUP_CCP1(CCP_OFF);
            WHILE(INPUT(BTN_STOP)==0);
         }
      }
      //KIEM TRA NUT NHAN CHON CAP DONG CO
      IF(INPUT(SW)==0)
      {   
         STATUS=1;
      }
      ELSE  STATUS=0;
      //KIEM TRA RUN/STOP
      IF(STATUS==0)
      {
         //CHAY CAP DONG CO BEN TRAI
         IF(INPUT(BTN_1_6)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_1_6)==0)
            { 
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)50);
               WHILE(INPUT(BTN_1_6)==0);
            }
         }
         IF(INPUT(BTN_2_7)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_2_7)==0)
            {  
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)100);
               WHILE(INPUT(BTN_2_7)==0);
            }
         }
         IF(INPUT(BTN_3_8)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_3_8)==0)
            {  
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)150);
               WHILE(INPUT(BTN_3_8)==0);
            }
         }
         IF(INPUT(BTN_4_9)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_4_9)==0)
            { 
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)200);
               WHILE(INPUT(BTN_4_9)==0);
            }
         }
         IF(INPUT(BTN_5_10)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_5_10)==0)
            { 
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)250);
               WHILE(INPUT(BTN_5_10)==0);
            }
         }
      }
      ELSE
      {
         //CHAY CAP DONG CO BEN PHAI
         IF(INPUT(BTN_1_6)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_1_6)==0)
            {  
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)300);
               WHILE(INPUT(BTN_1_6)==0);
            }
         }
         IF(INPUT(BTN_2_7)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_2_7)==0)
            {  
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)350);
               WHILE(INPUT(BTN_2_7)==0);
            }
         }
         IF(INPUT(BTN_3_8)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_3_8)==0)
            {  
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)400);
               WHILE(INPUT(BTN_3_8)==0);
            }
         }
         IF(INPUT(BTN_4_9)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_4_9)==0)
            { 
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)450);
               WHILE(INPUT(BTN_4_9)==0);
            }
         }
         IF(INPUT(BTN_5_10)==0)
         {
            DELAY_MS(10);
            IF(INPUT(BTN_5_10)==0)
            { 
               SETUP_CCP1(CCP_PWM);
               SET_PWM1_DUTY((UNSIGNED INT16)500);
               WHILE(INPUT(BTN_5_10)==0);
            }
         }
      }
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"STATUS=%U",STATUS);
   }
   
}

