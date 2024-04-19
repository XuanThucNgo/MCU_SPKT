#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

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
   SET_TRIS_D(0X00);
   SET_TRIS_A(0XFF);
   //INSTALL LCD
   LCD_INIT();
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN1|SAN2|VSS_VDD);
   
   WHILE(TRUE)
   {
      //READ_TEMP1
      SET_ADC_CHANNEL(1);
      DELAY_MS(10);
      TEMP1=READ_ADC()/2.046;
      
      //READ_TEMP2
      SET_ADC_CHANNEL(2);
      DELAY_MS(10);
      TEMP2=READ_ADC()/2.046;
      
      //DISPLAY LCD
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"T1=%02LU",TEMP1);
      LCD_PUTC(223);  LCD_PUTC('C');
      LCD_GOTOXY(10,1);
      PRINTF(LCD_PUTC,"T2=%02LU",TEMP2);
      LCD_PUTC(223);  LCD_PUTC('C');
      IF(TEMP1>60&&TEMP2<=60)
      {
         LCD_GOTOXY(3,2);
         LCD_PUTC("QUA NHIET K1");
      }
      ELSE IF(TEMP2>60&&TEMP1<=60)
      {
         LCD_GOTOXY(3,2);
         LCD_PUTC("QUA NHIET K2");
      }
      ELSE IF(TEMP2>60&&TEMP1>60)
      {
         LCD_GOTOXY(3,2);
         LCD_PUTC("QUA NHIET 2K");
      }
      ELSE
      {
         LCD_GOTOXY(3,2);
         LCD_PUTC("            ");  
      }
   }
}
