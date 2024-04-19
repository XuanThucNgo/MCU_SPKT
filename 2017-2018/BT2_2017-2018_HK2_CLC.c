#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE SPEED     PIN_B1
#DEFINE RUN_STOP  PIN_B2 

#define LCD_ENABLE_PIN  PIN_D3                                   
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                   
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                  
#define LCD_DATA7       PIN_D7 

#INCLUDE<LCD.C>

UNSIGNED INT8 LEVEL=0;
INT1 STATUS=0; //0 STOP
               //1 RUN

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   
   //INSTALL LCD
   LCD_INIT();
   
   SETUP_TIMER_2(T2_DIV_BY_16,124,1);  //PR2=124 => MAXDUTY=(124+1)X4=500  
                                       //3 CAP DO 30% 70% 100%       
   SETUP_CCP1(CCP_PWM); //RC2
   SET_TIMER2(0);
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   //HIEN THI LCD
   LCD_GOTOXY(1,1);
   LCD_PUTC("DUTY CYCLE");
   LCD_GOTOXY(1,2);
   LCD_PUTC("STATUS");
   
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
      IF(LEVEL>2)    LEVEL=0;
      IF(LEVEL==0)
      {
         LCD_GOTOXY(12,1);
         LCD_PUTC("030%");
      }
      IF(LEVEL==1)
      {
         LCD_GOTOXY(12,1);
         LCD_PUTC("070%");
      }
      IF(LEVEL==2)
      {
         LCD_GOTOXY(12,1);
         LCD_PUTC("100%");
      }            
      
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
         LCD_GOTOXY(12,2);
         LCD_PUTC("STOP");
      }
      ELSE
      {
         //RUN
         LCD_GOTOXY(12,2);
         LCD_PUTC("RUN ");
         SETUP_CCP1(CCP_PWM); //SETUP LAI
         IF(LEVEL==0)   SET_PWM1_DUTY((UNSIGNED INT16)150);
         IF(LEVEL==1)   SET_PWM1_DUTY((UNSIGNED INT16)350);
         IF(LEVEL==2)   SET_PWM1_DUTY((UNSIGNED INT16)500);             
      }
   }
   
}

