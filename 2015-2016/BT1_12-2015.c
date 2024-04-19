#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE LED_A PIN_B0
#DEFINE LED_B PIN_B1

#define LCD_ENABLE_PIN  PIN_D3                                    
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                    
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                    
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>
UNSIGNED INT16 TEMP1,TEMP2;
UNSIGNED INT8 I;

VOID MAIN()
{
   SET_TRIS_B(0X00);
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   
   //INSTALL LCD
   LCD_INIT();
   
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN5|SAN6|VSS_VDD);
   
   LCD_GOTOXY(1,1);
   LCD_PUTC("NGOXUANTHUC 21151360");
   
   WHILE(TRUE)
   {
      //DOC TEMP1
      SET_ADC_CHANNEL(5);
      FOR(I=0;I<100;I++)
      {
         TEMP1=TEMP1+READ_ADC();       
      }
      TEMP1=TEMP1/100/2.046;
      LCD_GOTOXY(1,2);
      PRINTF(LCD_PUTC,"T1=%03LU",TEMP1);
      LCD_PUTC(223); LCD_PUTC('C');
      //DOC TEMP1
      SET_ADC_CHANNEL(6);
      FOR(I=0;I<100;I++)
      {
         TEMP2=TEMP2+READ_ADC();       
      }
      TEMP2=TEMP2/100/2.046;
      LCD_GOTOXY(13,2);
      PRINTF(LCD_PUTC,"T2=%03LU",TEMP2);
      LCD_PUTC(223); LCD_PUTC('C');
      //LED_A
      IF(TEMP1>40)   OUTPUT_HIGH(LED_A);
      ELSE           OUTPUT_LOW(LED_A);
      //LED_B
      IF(TEMP2>45)   OUTPUT_HIGH(LED_B);
      ELSE           OUTPUT_LOW(LED_B);
   }
}

