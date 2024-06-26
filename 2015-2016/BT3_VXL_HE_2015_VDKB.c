#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=9600,BITS=8,STOP=1,PARITY=N, XMIT=PIN_C6,RCV=PIN_C7)

UNSIGNED CHAR RXDATA=0;

VOID MAIN()
{
   SET_TRIS_C(0X80);
   SETUP_TIMER_2(T2_DIV_BY_16,124,1);  //PR2=124 => MAXDUTY=(124+1)X4=500                                     
   SETUP_CCP1(CCP_PWM); //RC2
   SET_TIMER2(0);
   SET_PWM1_DUTY(0); //BAN DAU DUNG DONG CO
   WHILE(TRUE)
   {
      IF(KBHIT()==1)
      {
         RXDATA=GETC();
      }
      IF(RXDATA=='R')
      {
         //XUAT XUNG DUTY BANG 0.4
         SETUP_CCP1(CCP_PWM);
         SET_PWM1_DUTY((UNSIGNED INT16)200);
      }
      ELSE IF(RXDATA=='S')
      {
         SETUP_CCP1(CCP_OFF);
      }
   }
}
