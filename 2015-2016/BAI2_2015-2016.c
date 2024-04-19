#INCLUDE<16F887.H>
#DEVICE ADC=10
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE ON_OFF PIN_E2

#define LCD_ENABLE_PIN  PIN_D3                                  
#define LCD_RS_PIN      PIN_D1                                    
#define LCD_RW_PIN      PIN_D2                                    
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                    
#define LCD_DATA6       PIN_D6                                    
#define LCD_DATA7       PIN_D7 

#INCLUDE<LCD.C>

INT1 STATUS=0; //0 STOP
               //1 RUN               
UNSIGNED INT16 TEMP;
UNSIGNED INT8 PRODUCT=0;

VOID MAIN()
{
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   SET_TRIS_E(0XFF);
   
   //INSTALL LCD
   LCD_INIT();
   
   //SETUP ADC
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(SAN5|VSS_VDD);
   SET_ADC_CHANNEL(5);
   
   //SETUP COUNTER DEM
   SETUP_TIMER_1(T1_EXTERNAL|T1_DIV_BY_1);
   SET_TIMER1(0);
   SETUP_TIMER_2(T2_DIV_BY_16,249,1);
   SETUP_CCP1(CCP_PWM); //RC2
   SET_TIMER2(0);
   
   WHILE(TRUE)
   {
      //READ TEMP
      TEMP=READ_ADC()/2.046;
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"T=%02LU",TEMP);
      LCD_PUTC(223); LCD_PUTC('C');
      
      //DEM SAN PHAM
      PRODUCT=GET_TIMER1();
      IF(PRODUCT>24)
      {
         PRODUCT=0;
         SET_TIMER1(0);
      }
      LCD_GOTOXY(10,1);
      PRINTF(LCD_PUTC,"P=%02U",PRODUCT);
      //XUAT XUNG
      IF(INPUT(ON_OFF)==0)
      {
         DELAY_MS(10);
         IF(INPUT(ON_OFF)==0)
         {
            STATUS=~STATUS;
            WHILE(INPUT(ON_OFF)==0);
         }
      }
      IF(STATUS==0)
      {
         //STOP
         SETUP_CCP1(CCP_OFF);
         LCD_GOTOXY(1,2);
         LCD_PUTC("PWM=OFF    ");
      }
      ELSE
      {
         //RUN
         SETUP_CCP1(CCP_PWM); //SETUP LAI
         SET_PWM1_DUTY(700); //70/100.1000
         LCD_GOTOXY(1,2);
         LCD_PUTC("PWM=2ms,70%");
      }
   }
}


