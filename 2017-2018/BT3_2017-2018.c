#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE RUN PIN_B0
#DEFINE STOP PIN_B1
// NUT RESET NOI MCLR -> KHONG CAN PHAI DINH NGHIA
//                       KHONG PHAI DOC INPUT
//                       KHONG CAN CHONG DOI
// KHI NHAN CHUONG TRINH CHAY LAI TU DAU

#define LCD_ENABLE_PIN  PIN_D3                                    
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                    
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                    
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>

UNSIGNED INT8 PRODUCT=0; //BAN DAU
UNSIGNED INT16 BOX=0; //BAN DAU
UNSIGNED INT8 MODE = 0; //BAN DAU LA TRANG THAI RESET GIONG LUC MOI CAP DIEN
//RUN    -> MODE 1
//STOP   -> MODE 2
//RESET  -> MODE 0

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_D(0X00);
   //INSTALL LCD
   LCD_INIT();
   //SETUP COUNTER
   SETUP_TIMER_1(T1_EXTERNAL|T1_DIV_BY_1);
   SET_TIMER1(0);
   
   WHILE(TRUE)
   {
      IF(INPUT(RUN)==0)    MODE=1;
      IF(INPUT(STOP)==0)   MODE=2;
      
      PRODUCT=GET_TIMER1();
      IF(PRODUCT==50)
      {
         BOX++;
         SET_TIMER1(0);
      }
      IF(BOX==50000)
      {
         SETUP_TIMER_1(T1_DISABLED);
         LCD_GOTOXY(12,1);
         LCD_PUTC("STOP");
         LCD_GOTOXY(12,2);
         LCD_PUTC("FULL");
      }
      //XU LY BIEN MODE
      IF(MODE==1) //RUN
      {
         SETUP_TIMER_1(T1_EXTERNAL|T1_DIV_BY_1);   //SETUP LAI BO DEM COUTER
         LCD_GOTOXY(12,1);
         LCD_PUTC("RUN  ");
      }
      IF(MODE==2) //STOP
      {
         SETUP_TIMER_1(T1_DISABLED);   //TAT COUNTER
         LCD_GOTOXY(12,1);
         LCD_PUTC("STOP ");
      }
      IF(MODE==0) //RESET
      {
         SETUP_TIMER_1(T1_DISABLED);   //TAT COUNTER
         LCD_GOTOXY(12,1);
         LCD_PUTC("RESET");
      }
      
      // HIEN THI LEN LCD
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"P=%02U",PRODUCT);
      LCD_GOTOXY(1,2);
      PRINTF(LCD_PUTC,"Box=%05LU",BOX);    
   }
}
