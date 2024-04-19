#INCLUDE<16F887.H>
#FUSES INTRC
#USE DELAY(CLOCK=8M)

#DEFINE SW PIN_B0
#DEFINE BT PIN_B1
#DEFINE D1 PIN_D0

UNSIGNED INT1 STATUS=0; //0 OFF
                        //1 ON

VOID MAIN()
{
   SET_TRIS_B(0X03);
   SET_TRIS_D(0X00);
   //BAN DAU LED TAT
   OUTPUT_LOW(D1);
   WHILE(TRUE)
   {
      IF(INPUT(SW)==0)  STATUS=1;

      ELSE              STATUS=0;  
     
      IF(STATUS==0)
      {
         OUTPUT_LOW(D1);   
      }
      ELSE
      {
         IF(INPUT(BT)==0)
         {
            DELAY_MS(20);
            IF(INPUT(BT)==0)
            {
               OUTPUT_TOGGLE(D1);
               WHILE(INPUT(BT)==0);
            }
         }
      }
      
   }
}
