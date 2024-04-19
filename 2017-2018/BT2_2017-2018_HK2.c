#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE LED PIN_E2

#define LCD_ENABLE_PIN  PIN_D3                                 
#define LCD_RS_PIN      PIN_D1                                 
#define LCD_RW_PIN      PIN_D2                               
#define LCD_DATA4       PIN_D4                               
#define LCD_DATA5       PIN_D5                              
#define LCD_DATA6       PIN_D6                                
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>

UNSIGNED INT16 TEMP1=0,TEMP2=0;

VOID MAIN()
{
   SET_TRIS_E(0XFF);
   SET_TRIS_D(0X00);
   //INSTALL LCD
   LCD_INIT();
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN5|SAN6|VSS_VDD);
   WHILE(TRUE)
   {
      //READ TEMPERATURE ADC1
      SET_ADC_CHANNEL(5);
      DELAY_MS(100);
      TEMP1=READ_ADC()/2.046;
      //DISPLAY_LCD
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"Tx=%03LU",TEMP1);
      LCD_PUTC(223); LCD_PUTC('C');
      
      //READ TEMPERATURE ADC2
      SET_ADC_CHANNEL(6);
      DELAY_MS(100);
      TEMP2=READ_ADC()/2.046;
      //DISPLAY_LCD
      LCD_GOTOXY(1,2);
      PRINTF(LCD_PUTC,"Ty=%03LU",TEMP2);
      LCD_PUTC(223); LCD_PUTC('C');
      
      //QUA NHIET KENH 1
      IF(TEMP1>=100)
      {
         LCD_GOTOXY(14,1);
         LCD_PUTC("[H]");
      }
      ELSE
      {
         LCD_GOTOXY(14,1);
         LCD_PUTC("[L]");
      }
      //QUA NHIET KENH 2
      IF(TEMP2>=100)
      {
         LCD_GOTOXY(14,2);
         LCD_PUTC("[H]");
      }
      ELSE
      {
         LCD_GOTOXY(14,2);
         LCD_PUTC("[L]");
      }
      IF(TEMP1>100||TEMP2>100)     
      {
         OUTPUT_TOGGLE(LED);
         DELAY_MS(500);
         OUTPUT_LOW(LED);
      }
      ELSE                 OUTPUT_LOW(LED);
   }   
}
