//HE THONG A
#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=10M)
#USE RS232(BAUD=19200,BITS=8,STOP=1,PARITY=N, XMIT=PIN_C6,RCV=PIN_C7)

#DEFINE A  PIN_B0
#DEFINE B  PIN_B1
#DEFINE C  PIN_B2
#DEFINE D  PIN_B3
#DEFINE E  PIN_B4

VOID MAIN()
{
   SET_TRIS_B(0XFF);
   SET_TRIS_C(0X80);
   WHILE(TRUE)
   {
      IF(INPUT(A)==0) 
      {
         PUTC(0X00);
      }
      IF(INPUT(B)==0)
      {
         PUTC(0X01);
      }
      IF(INPUT(C)==0)
      {
         PUTC(0X02);
      }
      IF(INPUT(D)==0)
      {
         PUTC(0X03);
      }
      IF(INPUT(E)==0)
      {
         PUTC(0X04);
      }
   }
}
