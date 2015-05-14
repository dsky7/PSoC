/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include	"global01.h"
#include <project.h>

void PI(void);
void B_LED_ON(void);
void R_LED_ON(void);
void B_LED_OFF(void);
void R_LED_OFF(void);

uint8 num[17],astic[4];
uint8 sum1,mode;
uint8 ButtonStatus1,ButtonStatus2,CheckSum;

CY_ISR(myHandler){
    num[8] = num[7];
    num[7] = num[6];
    num[6] = num[5];
    num[5] = num[4];
    num[4] = num[3];
    num[3] = num[2];
    num[2] = num[1];
    num[1] = UART_1_ReadRxData();
B_LED_ON();
    if(num[8]==0x80){
        sum1 = num[2]+num[3]+num[4]+num[5]+num[6]+num[7];
        sum1 = sum1 & 0X7f;
		CheckSum = num[1];
		
		astic[3] = num[2];//Right UD
		astic[2] = num[3];//Right RL
		astic[1] = num[4];//Left UD
		astic[0] = num[5];//Left RL
		
		ButtonStatus1 = num[7];
		ButtonStatus2 = num[6];

	    if((num[7] & B_L1) != 0){//L1
			if(mode==0){mode=4;}else{mode = mode - 1;}
            R_LED_ON();
		} 
        
	    if((num[7] & B_R1) != 0){//R1
			if(mode==4){mode=0;}else{mode = mode + 1;}
            R_LED_OFF();
		}
    }               
}

int main()
{
    isr_1_StartEx((cyisraddress)myHandler);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PI();
  Enable2_Write(1);
    CyDelay(100);
    PI();
  //  I2C_1_Start();
    I2C_2_Start();
   // I2C_3_Start();
            //        I2C_1_MasterSendStart(0,1);//ADDRESS,RW;    0:WRITE 1:READ
                
    CYGlobalIntEnable; 
    isr_1_Enable();
    while(1){
    R_LED_ON();
    CyDelay(1000);
    R_LED_OFF();
    CyDelay(1000);
    }
    
    //            I2C_3_MasterSendStart(0,1);//ADDRESS,RW;    0:WRITE 1:READ
while(1){

//                
//              //  I2C_1_MasterWriteByte('A');
            I2C_2_MasterSendStart(4,0);//ADDRESS,RW;    0:WRITE 1:READ

            I2C_2_MasterWriteByte(84);
//  //              I2C_3_MasterWriteByte('A');
////                        I2C_1_MasterSendStop();
//                CyDelay(10);
//
            I2C_2_MasterSendStop();
//
//                                        I2C_3_MasterSendStop();
        R_LED_ON();            
        CyDelay(1);

        R_LED_OFF();
        CyDelay(1);


}
    

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
                I2C_1_MasterSendStart(0,1);//ADDRESS,RW;    0:WRITE 1:READ
        
        I2C_1_MasterSendStop();
        
        
            I2C_2_MasterSendStart(4,0);//ADDRESS,RW;    0:WRITE 1:READ
    I2C_2_MasterWriteByte('A');
        I2C_2_MasterSendStop();
        /* Place your application code here. */
        
    }
}

void PI(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    CyDelay(200);
    PWM_1_WriteCompare(0);
    PWM_1_Stop();    
}
void R_LED_ON(void){
    R_LED_Write(1);
}
void R_LED_OFF(void){
        R_LED_Write(0);
}
void B_LED_ON(void){
    B_LED_Write(1);
}
void B_LED_OFF(void){
    B_LED_Write(0);
}

/* [] END OF FILE */
