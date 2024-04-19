#INCLUDE<16F887.H>
#FUSES HS
#USE DELAY(CLOCK=20M)

#DEFINE RESET PIN_C3

#USE RS232 (BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)

CONST UNSIGNED INT8 MA7DOAN[10] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

UNSIGNED INT8 DEM2;

VOID MAIN()
{
   SET_TRIS_D(0X00);
   SET_TRIS_B(0X00);
   SET_TRIS_C(0XFF);
   
   WHILE(TRUE)
   {
      //KIEM TRA NUT NHAN
      IF(INPUT(RESET)==0)
      {
         DELAY_MS(10);
         IF(INPUT(RESET)==0)
         {
            DEM2=0;           
            //TRUYEN SO SAN PHAM
            PUTC('0');
            WHILE(INPUT(RESET)==0);
         }
      }
      //NHAN DU LIEU
      IF(KBHIT()==1)
      {
         DEM2=GETC();      
      }
      //HIEN THI LED 7 DOAN
      OUTPUT_D(MA7DOAN[DEM2/10]);
      OUTPUT_B(MA7DOAN[DEM2%10]);
   }
}