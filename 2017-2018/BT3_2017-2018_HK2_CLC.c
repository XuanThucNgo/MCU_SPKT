#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=2400,XMIT=PIN_C6,RCV=PIN_C7)
#DEFINE PQC_1           PIN_C0
#DEFINE PQC_2           PIN_C1
#DEFINE LINE_LEADER_1   PIN_C2
#DEFINE LINE_LEADER_2   PIN_C3

UNSIGNED CHAR DATA=0;
UNSIGNED INT8 DEM1=11,DEM2=12,DEM3=21,DEM4=22;

VOID MAIN()
{
   SET_TRIS_B(0);
   SET_TRIS_C(0B10001111);
   SET_TRIS_D(0);
   OUTPUT_B(0XBF);
   OUTPUT_D(0XBF);   
   WHILE (TRUE)
   {
      IF(INPUT(PIN_C0)==0)
      {
         DELAY_MS(20);
         IF(INPUT(PIN_C0)==0)
         {
            WHILE (INPUT(PIN_C0)==0);
            OUTPUT_B(0XF9);
            PUTC(DEM1);
         }
      }
      IF(INPUT(PIN_C1)==0)
      {
         DELAY_MS(20);
         IF(INPUT(PIN_C1)==0)
         {
            WHILE (INPUT(PIN_C1)==0);
            OUTPUT_B(0XA4);
            PUTC(DEM2);
         }
      } 
      IF(INPUT(PIN_C2)==0)
      {
         DELAY_MS(20);
         IF(INPUT(PIN_C2)==0)
         {
            WHILE (INPUT(PIN_C2)==0);
            OUTPUT_D(0XF9);
            PUTC(DEM3);
         }
      }
      IF(INPUT(PIN_C3)==0)
      {
         DELAY_MS(20);
         IF(INPUT(PIN_C3)==0)
         {
            WHILE (INPUT(PIN_C3)==0);
            OUTPUT_D(0XA4);
            PUTC(DEM4);
         }
      }
      IF (KBHIT()==1)
      {
         DATA=GETC();
      }
      IF(DATA=='R')
      {
         OUTPUT_B(0XBF);
         OUTPUT_D(0XBF);
      }
   }   
}
