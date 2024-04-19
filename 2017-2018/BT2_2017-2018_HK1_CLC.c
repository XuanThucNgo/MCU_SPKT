#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE LED    PIN_C1
#DEFINE BUZZER PIN_C3

#define LCD_ENABLE_PIN  PIN_D3                                   
#define LCD_RS_PIN      PIN_D1                                   
#define LCD_RW_PIN      PIN_D2                                   
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                  
#define LCD_DATA7       PIN_D7 

#INCLUDE<LCD.C>

UNSIGNED INT16 TEMP1=0, TEMP2=0;

VOID READ_ADC2()
{
   SET_ADC_CHANNEL(2);
   DELAY_US(20);
   TEMP1=READ_ADC()/2.046;
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"%02LU",TEMP1);
   LCD_PUTC(223); LCD_PUTC('C');
}

VOID READ_ADC4()
{
   SET_ADC_CHANNEL(4);
   DELAY_US(20);
   TEMP2=READ_ADC()/2.046;
   LCD_GOTOXY(10,1);
   PRINTF(LCD_PUTC,"%02LU",TEMP2);
   LCD_PUTC(223); LCD_PUTC('C');
}

VOID MAIN()
{
   SET_TRIS_A(0B00100100);
   SET_TRIS_D(0X00);
   SET_TRIS_C(0X08);
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN2|SAN4|VSS_VDD);
   //INSTALL LCD
   LCD_INIT();
   
   WHILE(TRUE)
   {
      READ_ADC2();
      READ_ADC4();
      
      IF(TEMP1<50&&TEMP2<50)
      {
         OUTPUT_LOW(LED);
         OUTPUT_HIGH(BUZZER);
         LCD_GOTOXY(1,2);
         LCD_PUTC("LM35-2");
         LCD_GOTOXY(10,2);
         LCD_PUTC("LM35-4");
      }
      ELSE IF(TEMP1>50&&TEMP2<50)
      {
         LCD_GOTOXY(1,2);
         LCD_PUTC("QNHIET");
         LCD_GOTOXY(10,2);
         LCD_PUTC("LM35-4");
         OUTPUT_HIGH(LED);
         OUTPUT_HIGH(BUZZER);
      }
      ELSE IF(TEMP1<50&&TEMP2>50)
      {
         LCD_GOTOXY(10,2);
         LCD_PUTC("QNHIET");
         LCD_GOTOXY(1,2);
         LCD_PUTC("LM35-2");
         OUTPUT_HIGH(LED);
         OUTPUT_HIGH(BUZZER);
      }
      ELSE IF(TEMP1>50&&TEMP2>50)
      {
         LCD_GOTOXY(1,2);
         LCD_PUTC("QNHIET");
         LCD_GOTOXY(10,2);
         LCD_PUTC("QNHIET");
         OUTPUT_HIGH(LED);
         OUTPUT_LOW(BUZZER);
      }
   }
   
   
}
