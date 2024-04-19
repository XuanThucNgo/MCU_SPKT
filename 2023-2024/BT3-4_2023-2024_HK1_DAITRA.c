#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE START PIN_A0

CONST UNSIGNED INT8 MA7DOAN[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
UNSIGNED INT16 MSSV = 360;
VOID MAIN()
{
   SET_TRIS_A(0X01);
   SET_TRIS_B(0X00);
   SET_TRIS_C(0X00);
   SET_TRIS_D(0X00);
   //BAN DAU TAT HET
   OUTPUT_B(0X00);
   OUTPUT_C(0X00);
   OUTPUT_D(0X00);
   WHILE(TRUE)
   {
      IF(INPUT(START)==0)
      {
         DELAY_MS(20);
         IF(INPUT(START)==0)
         {
            /*OUTPUT_C(0X4F);
            OUTPUT_D(0X7D);
            OUTPUT_B(0X3F);*/
            OUTPUT_C(MA7DOAN[MSSV/100]);
            OUTPUT_D(MA7DOAN[MSSV/10%10]);
            OUTPUT_B(MA7DOAN[MSSV%10]);
            WHILE(INPUT(START)==0);
         }
      }
   }
}
