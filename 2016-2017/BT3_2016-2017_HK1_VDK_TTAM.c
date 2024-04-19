#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)

#USE RS232(BAUD=4800, XMIT=PIN_C6,RCV=PIN_C7)

#DEFINE BUTTON_MODE PIN_B0

UNSIGNED INT8 I,MODE=1;

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X80);
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN CHON CHE DO
      IF(INPUT(BUTTON_MODE)==0)
      {
         DELAY_MS(10);
         IF(INPUT(BUTTON_MODE)==0)
         {
            MODE++;
            WHILE(INPUT(BUTTON_MODE)==0);
         }
      }
      IF(MODE>3)  MODE=1;
      IF(MODE==1)
      {
         //KHONG LAM GI
      }
      IF(MODE==2)
      {
         FOR(I=0;I<4;I++)
         {
            PUTC('I');
            DELAY_MS(2000);
         }       
      }
      IF(MODE==3)
      {
         PUTC('T');
      }
   }
}

