#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES HS
#USE DELAY(CLOCK=20M)

#USE RS232(BAUD=4800,BITS=8,STOP=1,PARITY=N, XMIT=PIN_C6,RCV=PIN_C7)
#DEFINE LED PIN_E0

#define LCD_ENABLE_PIN  PIN_D3                                 
#define LCD_RS_PIN      PIN_D1                                 
#define LCD_RW_PIN      PIN_D2                               
#define LCD_DATA4       PIN_D4                               
#define LCD_DATA5       PIN_D5                              
#define LCD_DATA6       PIN_D6                                
#define LCD_DATA7       PIN_D7

#INCLUDE<LCD.C>

CHAR RXDATA;
UNSIGNED INT16 TEMP1=0,TEMP2=0;

VOID READ_ADC1()
{
   //READ TEMPERATURE ADC1
   SET_ADC_CHANNEL(1);
   DELAY_US(20);
   TEMP1=READ_ADC()/2.046;
   //DISPLAY_LCD
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"CH1=%03LU",TEMP1);
   LCD_PUTC(223); LCD_PUTC('C');
   IF(TEMP1>=50)
   {
      LCD_GOTOXY(14,1); 
      LCD_PUTC("[H]");
   }
   ELSE
   {
      LCD_GOTOXY(14,1); 
      LCD_PUTC("[L]");
   }
}

VOID READ_ADC2()
{
   //READ TEMPERATURE ADC1
   SET_ADC_CHANNEL(2);
   DELAY_US(20);
   TEMP2=READ_ADC()/2.046;
   //DISPLAY_LCD
   LCD_GOTOXY(1,2);
   PRINTF(LCD_PUTC,"CH2=%03LU",TEMP2);
   LCD_PUTC(223); LCD_PUTC('C');
   IF(TEMP2>=50)
   {
      LCD_GOTOXY(14,2); 
      LCD_PUTC("[H]");
   }
   ELSE
   {
      LCD_GOTOXY(14,2); 
      LCD_PUTC("[L]");
   }
}

VOID MAIN()
{
   SET_TRIS_A(0XFF);
   SET_TRIS_B(0X00);
   SET_TRIS_C(0X80);
   SET_TRIS_D(0X00);
   
   //INSTALL LCD
   LCD_INIT();
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN1|SAN2|VSS_VDD);
   
   WHILE(TRUE)
   {
      IF(KBHIT()==1)
      {
         RXDATA=GETC();
         IF(RXDATA=='1')
         {
            //READ ONLY ADC1
            READ_ADC1();
            LCD_GOTOXY(1,2);
            LCD_PUTC("CH2=OFF");
            LCD_GOTOXY(14,2);
            LCD_PUTC("[x]");
            IF(TEMP1>=50)  OUTPUT_HIGH(LED);
            ELSE           OUTPUT_LOW(LED);
         }  
         ELSE IF(RXDATA=='2')
         {
            //READ ONLY ADC2
            READ_ADC2();
            LCD_GOTOXY(1,1);
            LCD_PUTC("CH1=OFF");
            LCD_GOTOXY(14,1);
            LCD_PUTC("[x]");
            IF(TEMP2>=50)  OUTPUT_HIGH(LED);
            ELSE           OUTPUT_LOW(LED);
         }
         ELSE IF(RXDATA=='3')
         {
            //READ ADC1 AND ADC2
            READ_ADC1();
            READ_ADC2();
            IF(TEMP1>=50||TEMP2>=50)  OUTPUT_HIGH(LED);
            ELSE           OUTPUT_LOW(LED);
         }  
         ELSE IF(RXDATA=='4')
         {
            //OFF
            LCD_GOTOXY(1,1);
            LCD_PUTC("CH1=OFF");
            LCD_GOTOXY(14,1);
            LCD_PUTC("[x]");
            LCD_GOTOXY(1,2);
            LCD_PUTC("CH2=OFF");
            LCD_GOTOXY(14,2);
            LCD_PUTC("[x]");
            OUTPUT_LOW(LED);
         }
      }
   }  
}
