#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=2400,BITS=8,STOP=1,PARITY=N, XMIT=PIN_C6,RCV=PIN_C7)

#DEFINE SEND PIN_E0

CONST UNSIGNED CHAR KT[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
SIGNED INT8 I=-1;

VOID MAIN()
{
   SET_TRIS_E(0XFF);
   SET_TRIS_C(0X80);
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN SEND
      IF(INPUT(SEND)==0)
      {
         DELAY_MS(20);
         IF(INPUT(SEND)==0)
         {
            I++;     
            PUTC(KT[I]);
            PRINTF(KT[I]);
         }
         WHILE(INPUT(SEND)==0);
      }
      IF(I>8)    I=-1;      
   }
}
