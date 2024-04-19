#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

#define LCD_ENABLE_PIN  PIN_E0                                   
#define LCD_RS_PIN      PIN_E1                                   
#define LCD_RW_PIN      PIN_E2                                   
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                   
#define LCD_DATA6       PIN_D6                                  
#define LCD_DATA7       PIN_D7 

#INCLUDE<LCD.C>

UNSIGNED INT16 TEMP1=0, TEMP2=0;

VOID READ_ADC1()
{
   SET_ADC_CHANNEL(1);
   DELAY_US(20);
   TEMP1=READ_ADC()/3.41;
   LCD_GOTOXY(1,2);
   PRINTF(LCD_PUTC,"K1=%02LU",TEMP1);
   LCD_PUTC(223); LCD_PUTC('C');
}

VOID READ_ADC2()
{
   SET_ADC_CHANNEL(2);
   DELAY_US(20);
   TEMP2=READ_ADC()/3.41;
   LCD_GOTOXY(10,2);
   PRINTF(LCD_PUTC,"K2=%02LU",TEMP2);
   LCD_PUTC(223); LCD_PUTC('C');
}

VOID MAIN()
{
   SET_TRIS_A(0B00001110);
   SET_TRIS_D(0X00);
   SET_TRIS_E(0X00);
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN1|SAN2|VSS_VREF);
   //INSTALL LCD
   LCD_INIT();
   LCD_GOTOXY(3,1);
   LCD_PUTC("DO NHIET DO");
   WHILE(TRUE)
   {
      READ_ADC1();
      READ_ADC2();
   }  
}
