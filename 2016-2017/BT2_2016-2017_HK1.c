#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE C_DOI  PIN_C0 
#DEFINE LOA    PIN_C1

#define LCD_ENABLE_PIN   PIN_D3                                   
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                  
#define LCD_DATA4       PIN_D4                                   
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                   
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>

UNSIGNED INT16 XX=0,YY=45,ZZZ,QQQ=318;
INT1 STATUS=0; //0 DO DO C
               //1 DO DO K

VOID MAIN()
{
   SET_TRIS_C(0X01);
   SET_TRIS_D(0X00);
   SET_TRIS_A(0XFF);
   //INSTALL LCD
   LCD_INIT();
   //SETUP_ADC
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN4|VSS_VDD);
   SET_ADC_CHANNEL(4);
   //CONG VIEC THUC HIEN 1 LAN
   LCD_GOTOXY(1,1);
   LCD_PUTC("N.Do=");
   LCD_GOTOXY(1,2);
   LCD_PUTC("GT cai=");
   
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN C_DOI
      IF(INPUT(C_DOI)==0)
      {
         DELAY_MS(10);
         IF(INPUT(C_DOI)==0)
         {
            STATUS=~STATUS;
            WHILE(INPUT(C_DOI)==0);
         }
      }
      XX=READ_ADC()/2.046;
      ZZZ=XX+273;
      IF(STATUS==0)
      {
         //DO DO C VA DISPLAY LCD
         //DISPLAY ROW 1
         LCD_GOTOXY(9,1);
         PRINTF(LCD_PUTC," %02LU do C",XX);
         //DISPLAY ROW 2
         LCD_GOTOXY(9,2);
         PRINTF(LCD_PUTC," %02LU do C",YY);
         //KIEM TRA VA NHAP NHAY
         IF(XX>=YY)
         {
            //NHAP NHAY XX 0.5S SANG 0.5S TAT
            LCD_GOTOXY(9,1);
            PRINTF(LCD_PUTC," %02LU do C",XX);
            DELAY_MS(500);
            LCD_GOTOXY(9,1);
            LCD_PUTC("    do C");
            DELAY_MS(500);
            OUTPUT_LOW(LOA);
            /*//FOR SIMULATION
            IF(INPUT(C_DOI)==0)
            {
               DELAY_MS(10);
               IF(INPUT(C_DOI)==0)
               {
                  STATUS=~STATUS;
                  WHILE(INPUT(C_DOI)==0);
                  BREAK;
               }
            }*/
         }
      }
      ELSE
      {
         //DO DO K VA DISPLAY LCD
         //DISPLAY ROW 1
         LCD_GOTOXY(9,1);
         PRINTF(LCD_PUTC,"%03LU do K",ZZZ);
         //DISPLAY ROW 2
         LCD_GOTOXY(9,2);
         PRINTF(LCD_PUTC,"%03LU do K",QQQ);
         //KIEM TRA VA NHAP NHAY
         IF(ZZZ>=QQQ)
         {
            //NHAP NHAY XX 0.5S SANG 0.5S TAT
            LCD_GOTOXY(9,1);
            PRINTF(LCD_PUTC,"%03LU do K",ZZZ);
            DELAY_MS(500);
            LCD_GOTOXY(9,1);
            LCD_PUTC("    do K");
            DELAY_MS(500);
         }
      }
   }
}

