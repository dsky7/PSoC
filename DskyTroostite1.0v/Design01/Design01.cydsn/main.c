/* ========================================
 * dsky
 * troostite 1.0v
 * 2014/06/20
 * this module has lcd and many communication connector.
 * ========================================
*/
#include	"global01.h"
#include <project.h>
#include "LCD_Char_1.h"
#include "LCD_Char_1.c"

volatile uint32 gTick = 0;
uint8 num0, num1, num2, num3, num4, num5, num6, num7, num8 = 0;
uint8 num[17];
uint8 astic[4];
uint8 ButtonStatus1,ButtonStatus2,CheckSum;
uint8 sum1 = 0;
uint8 mode = 0;
uint8 modeBuff = 0;
uint8 dskynum2;
uint8	buff[4];
uint8 dPhoto[4];
uint8 avePhoto;
uint8 fMode;
uint8 LedR,LedG,LedB;
uint8 BuffLedPwm;
uint16 ms_count;
    uint8 I2C_Wdata=7;
    
char str1[5][2][20] = {{" dsky troostite", "start page"},{"   config", "   select"},{"   mode1", "    temp"}};

void send_config(uint8 addr, int32 c_data, uint8 length);
void printOK(uint8 l);
void printNG(uint8 l);
void print4num(uint8 n1,uint8 n2,uint8 n3,uint8 n4);
void printMARK(uint8 n1,uint8 n2);
void printPS3(uint8 l,uint8 n1,uint8 n2,uint8 n3,uint8 n4,uint8 n5,uint8 n6,uint8 n7,uint8 n8);
void print8num(uint8 l, uint8 n1,uint8 n2,uint8 n3,uint8 n4,uint8 n5,uint8 n6,uint8 n7,uint8 n8);
void sendPCA(uint8 reg,uint8 dat1);
void servo(uint8 servoN, uint8 value);
void motor(uint8 motorN, uint8 value);



 
CY_ISR(MY_ISR) {
    ms_count++;
   //  LED2_Write(1); // Toggle LED
    if(ms_count > 100) { // 1 second
        LED2_Write(!LED2_Read()); // Toggle LED
        
        ms_count = 0; // reset ms counter
    }

        I2C_1_MasterSendStart(0,1);//ADDRESS,RW;    0:WRITE 1:READ
        I2C_Wdata=I2C_1_MasterReadByte(0);
        I2C_1_MasterSendStop();
        
        LCD_Char_1_Position(1,0);
        LCD_Char_1_PrintInt8(I2C_Wdata);        
        
        
        I2C_1_MasterSendStart(1,1);//ADDRESS,RW;    0:WRITE 1:READ
        I2C_Wdata=I2C_1_MasterReadByte(0);
        I2C_1_MasterSendStop();
        
        LCD_Char_1_Position(1,3);
        LCD_Char_1_PrintInt8(I2C_Wdata);        
        
        
        I2C_1_MasterSendStart(3,1);//ADDRESS,RW;    0:WRITE 1:READ
        I2C_Wdata=I2C_1_MasterReadByte(0);
        I2C_1_MasterSendStop();
        
        LCD_Char_1_Position(1,6);
        LCD_Char_1_PrintInt8(I2C_Wdata);        
        
    
    
    
    
//    isr_2_ClearPending();
}

CY_ISR(SysTick_Handler){
    gTick++; 
}

CY_ISR(myHandler){
    num[8] = num[7];
    num[7] = num[6];
    num[6] = num[5];
    num[5] = num[4];
    num[4] = num[3];
    num[3] = num[2];
    num[2] = num[1];
    num[1] = UART_1_ReadRxData();

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
		} 
        
	    if((num[7] & B_R1) != 0){//R1
			if(mode==4){mode=0;}else{mode = mode + 1;}
		}
    }               
}

void Delay(uint32 tick_delay){
    uint32 tick_entry = gTick;
    // wait for tick
    while((gTick - tick_entry) < tick_delay);
}
void pi(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    Delay(50);
    PWM_1_WriteCompare(0);
    PWM_1_Stop();    
}
void pipi(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    Delay(50);
    PWM_1_WriteCompare(0);
    Delay(50);

    PWM_1_WriteCompare(127);
    Delay(50);
    PWM_1_WriteCompare(0);
    Delay(50);
    
    PWM_1_Stop();
}
void LCD_Char_1_Init2(void) {
    /* INIT CODE */
    CyDelay(500u);                                                        /* Delay 500 ms */
    
    LCD_Char_1_WrCntrlNib(0x02u);
    LCD_Char_1_WrCntrlNib(0x02u);
    LCD_Char_1_WrCntrlNib(0x00u);

    LCD_Char_1_WrCntrlNib(0x00u);
    LCD_Char_1_WrCntrlNib(0x08u);
    
//    LCD_Char_1_WriteControl(0X08u); 
    CyDelay(50u);
    LCD_Char_1_WriteControl(0x13u);
 //   LCD_Char_1_WrCntrlNib(0x13u);
//    LCD_Char_1_WriteControl(0x13u);
    CyDelay(50u);
    LCD_Char_1_WrCntrlNib(0x00u);
    CyDelay(50u);
        LCD_Char_1_WrCntrlNib(0x00u);
            LCD_Char_1_WrCntrlNib(0x00u);
                LCD_Char_1_WrCntrlNib(0x00u);
                    LCD_Char_1_WrCntrlNib(0x00u);
                        LCD_Char_1_WrCntrlNib(0x00u);
                    
    LCD_Char_1_WriteControl(0x20u);
    LCD_Char_1_WriteControl(0x28u);
    LCD_Char_1_WriteControl(0x0Bu);
    LCD_Char_1_WriteControl(0x06u);

    LCD_Char_1_WriteControl(0x01u);
    CyDelay(20u);
    LCD_Char_1_WriteControl(0x02u);
    CyDelay(100u);
    LCD_Char_1_WriteControl(0x17u);
    CyDelay(50u);
    LCD_Char_1_WriteControl(0x0Fu);
    LCD_Char_1_WriteControl(0x0Cu);
    
    #if(LCD_Char_1_CUSTOM_CHAR_SET != LCD_Char_1_NONE)
        LCD_Char_1_LoadCustomFonts(LCD_Char_1_customFonts);
    #endif /* LCD_Char_1_CUSTOM_CHAR_SET != LCD_Char_1_NONE */
}
void printOK(uint8 l){
    LCD_Char_1_Position(l,19);
    LCD_Char_1_PrintString("!");
}
void printNG(uint8 l){
    LCD_Char_1_Position(l,19);
    LCD_Char_1_PrintString("?");
}
void printMARK(uint8 n1,uint8 n2){
//    uint8 flg = n1 & B_L1;
    LCD_Char_1_Position(0,1);
    if((n1 & B_L1) != 0){
        LCD_Char_1_PrintString("L1");
    }else{
        LCD_Char_1_PrintString("  ");
    }
    LCD_Char_1_Position(0,3);
    if((n1 & B_L2) != 0){
        LCD_Char_1_PrintString("L2");
    }else{
        LCD_Char_1_PrintString("  ");
    }
    
    LCD_Char_1_Position(0,5);
    if((n1 & B_R1) != 0){
        LCD_Char_1_PrintString("R1");
    }else{
        LCD_Char_1_PrintString("  ");
    }
    LCD_Char_1_Position(0,7);
    if((n1 & B_R2) != 0){
        LCD_Char_1_PrintString("R2");
    }else{
        LCD_Char_1_PrintString("  ");
    }
    
    LCD_Char_1_Position(0,14);
    if((n2 & B_SE) == B_SE){
        LCD_Char_1_PrintString("SELECT");
    }else{
            LCD_Char_1_Position(0,14);
        if((n2 & B_ST) == B_ST){
            LCD_Char_1_PrintString("START");
        }else{
            LCD_Char_1_PrintString("       ");
        }
    }

}
void print4num(uint8 n1,uint8 n2,uint8 n3,uint8 n4){
    LCD_Char_1_Position(1,1);

    LCD_Char_1_PrintString("0x");
    LCD_Char_1_PrintInt8(n1);        
    LCD_Char_1_PrintString(" 0x");
    LCD_Char_1_PrintInt8(n2);
    LCD_Char_1_PrintString(" 0x");
    LCD_Char_1_PrintInt8(n3);    
    LCD_Char_1_PrintString(" 0x");
    LCD_Char_1_PrintInt8(n4);  
}
void printPS3(uint8 l,uint8 n1,uint8 n2,uint8 n3,uint8 n4,uint8 n5,uint8 n6,uint8 n7,uint8 n8){
    LCD_Char_1_Position(l,0);

    LCD_Char_1_PrintInt8(n1);        
    LCD_Char_1_PrintInt8(n2);
    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n3);
    LCD_Char_1_PrintInt8(n4);  
    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n5);
    LCD_Char_1_PrintInt8(n6);   
    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n7);   
    LCD_Char_1_PrintInt8(n8);   
}    
void print8num(uint8 l, uint8 n1,uint8 n2,uint8 n3,uint8 n4,uint8 n5,uint8 n6,uint8 n7,uint8 n8){

    LCD_Char_1_Position(l,0);

    LCD_Char_1_PrintInt8(n1);        
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n2);
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n3);
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n4);  
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n5);
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n6);   
//    LCD_Char_1_PrintString(" ");
    LCD_Char_1_PrintInt8(n7);
    LCD_Char_1_PrintInt8(n8);
}
void LCD_Char_1_Start2(void){
    /* If not initialized then perform initialization */
    if(LCD_Char_1_initVar == 0u)    {
        LCD_Char_1_Init2();
        LCD_Char_1_initVar = 1u;
    }

    /* Turn on the LCD */
    LCD_Char_1_Enable();
}
void PageShift(uint8 page){
    LCD_Char_1_PrintString(str1[page][0]);    
    LCD_Char_1_PrintString(str1[page][1]);
}
void mode0(){
	LCD_Char_1_Position(0,0);
	LCD_Char_1_PrintString(" dsky troostite 1.0v");
						  /*123456789!123456789!*/
	LCD_Char_1_Position(1,0);
	LCD_Char_1_PrintString("    select mode     ");
						  /*123456789!123456789!*/
}
void mode1(){
	    /*DieTemp*/    
    int16 DieTemp = 0;

    cystatus diestatus;
    LCD_Char_1_Position(0,0);
    LCD_Char_1_PrintString("   DieTemperature   ");
						  /*123456789!123456789!*/

        DieTemp_1_Start();
        diestatus = DieTemp_1_Query(&DieTemp);
        LCD_Char_1_Position(1,0);
	    LCD_Char_1_PrintString(" ");
        LCD_Char_1_PrintInt16(DieTemp);
	    LCD_Char_1_PrintString(" status:");
		switch (diestatus){
			case CYRET_SUCCESS:
						LCD_Char_1_PrintString("SUCCESS  ");      
						break;
						
			case CYRET_UNKNOWN:
						LCD_Char_1_PrintString("UNKNOWN  ");
						break;
						
			case CYRET_STARTED:
						LCD_Char_1_PrintString("STARTED  ");
						break;
						
			case CYRET_TIMEOUT:
						LCD_Char_1_PrintString("TIMEOUT  ");
						break;
		}
	
}
void mode2(){
	LCD_Char_1_Position(0,0);
	LCD_Char_1_PrintString(" Bluetooth Monitor  ");
		  				  /*123456789!123456789!*/                    	
        //printPS3(1,num[7],num[6],num[5],num[4],num[3],num[2],num[1],sum1);
	printPS3(1,ButtonStatus1,ButtonStatus2,astic[0],astic[1],astic[2],astic[3],CheckSum,sum1);    
	LCD_Char_1_PrintString(" ");

}
void mode3(){
	LCD_Char_1_Position(0,0);
	LCD_Char_1_PrintString(" Configuration Mode ");
						  /*123456789!123456789!*/
		LCD_Char_1_Position(1,0);
	LCD_Char_1_PrintString("    device onof     ");
}
void mode4(){
	LCD_Char_1_Position(0,0);
	LCD_Char_1_PrintString(" Bluetooth Controll ");
		  				  /*123456789!123456789!*/                    	
	printPS3(1,ButtonStatus1,ButtonStatus2,astic[0],astic[1],astic[2],astic[3],CheckSum,sum1);    
	MotorPwmRight_WriteCompare1(astic[0]);
	MotorPwmLeft_WriteCompare1(astic[1]);
	MotorPwmRight_WriteCompare2(astic[2]);
	MotorPwmLeft_WriteCompare2(astic[3]);
}


void initPSoC(){
    pi();
    LCD_Char_1_Start2();						//555555555555555555555555555
    UART_1_Start();

//    LCD_Char_1_WriteControl(0x81u);
    LCD_Char_1_Position(0,0);

                          /*123456789!123456789!*/
    LCD_Char_1_PrintString("      HILL TOP      ");

    LCD_Char_1_Position(1,0);
    LCD_Char_1_PrintString(" dsky troostite1.9v ");	
  //  pipi(); 	
}
void RightFrontMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            RightFront_Rev_Write(1);            
            nPwm = -nRotate;
        }else{
            RightFront_Rev_Write(0);            
            nPwm = nRotate;
        }    
    }
    MotorPwmRight_WriteCompare1(nPwm);
}

void RightRearMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}        
        if(nRotate<0){
            RightRear_Rev_Write(1);            
            nPwm = -nRotate;
        }else{
            RightRear_Rev_Write(0);            
            nPwm = nRotate;
        }    
    }
    MotorPwmRight_WriteCompare2(nPwm);
}
void LeftFrontMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}        
        if(nRotate<0){
            LeftFront_Rev_Write(0);            
            nPwm = -nRotate;
        }else{
            LeftFront_Rev_Write(1);            
            nPwm = nRotate;
        }    
    }
    MotorPwmLeft_WriteCompare1(nPwm);
}

void LeftRearMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            LeftRear_Rev_Write(0);            
            nPwm = -nRotate;
        }else{
            LeftRear_Rev_Write(1);            
            nPwm = nRotate;
        }    
    }
    MotorPwmLeft_WriteCompare2(nPwm);
}


int main()
{
    // Set the SysTick Interrupt Vector (=15) in Vector Table in RAM
    CyIntSetSysVector(15, (cyisraddress)SysTick_Handler);
	
	//isr_1_SetVector((cyisraddress)myHandler);
    isr_1_StartEx((cyisraddress)myHandler);
    isr_2_StartEx((cyisraddress)MY_ISR); // Point to MY_ISR to carry out the interrupt sub-routine

    // Start SysTick Periodic Interrupt
    SysTick_Config(BCLK__BUS_CLK__HZ/1000); // SysTick=1000Hz(1ms)
    // Enable Interrupt Detection]
    
//    Timer_1_Start(); // Configure and enable timer

	
    CYGlobalIntEnable; 
    
    
    
    
    
    isr_1_Enable();
    isr_2_Enable();
    
    I2C_1_Start();
    I2C_1_Enable();
    
//    while(1){
//        RightFront_Rev_Write(1);
//        RightRear_Rev_Write(1);
//        LeftFront_Rev_Write(1);
//        LeftRear_Rev_Write(1);
//        
//        Delay(1000);
//        RightFront_Rev_Write(0);
//        RightRear_Rev_Write(0);
//        LeftFront_Rev_Write(0);
//        LeftRear_Rev_Write(0);
//        Delay(1000);
//    }
	
	pi();
    
	MotorPwmLeft_Start();
	MotorPwmRight_Start();

	initPSoC();
    Delay(100);
    LCD_Char_1_WriteControl(0x02u);
    
 //   pipi();
	//メカナム
	while(1){
	//	LCD_Char_1_Position(0,0);
	//	LCD_Char_1_PrintString(" Bluetooth Controll ");
				  			   /*123456789!123456789!*/                    	
	//	printPS3(1,ButtonStatus1,ButtonStatus2,astic[0],astic[1],astic[2],astic[3],CheckSum,sum1);    
		
//	    if((num[7] & B_L1) != 0){//L1
//			if(mode==0){mode=4;}else{mode = mode - 1;}
//		}         
        int16 nFR,nRL,nRotate;
       
        if(astic[1]==0){nFR = 0x40;}else{
            nFR = astic[1];
        }
        if(astic[0]==0){nRL = 0x40;}else{
            nRL = astic[0];
        }
        if(astic[2]==0){nRotate = 0x40;}else{
            nRotate = astic[2];
        }
//        RightFrontMotor(255);        
//        RightRearMotor(255);
//        LeftFrontMotor(255);        
//        LeftRearMotor(255);
        
    RightFrontMotor(nFR+nRL-0x80+nRotate-0x40);        
    RightRearMotor(nFR-nRL+nRotate-0x40);
    LeftFrontMotor(nFR-nRL-nRotate+0x40);        
    LeftRearMotor(nFR+nRL-0x80-nRotate+0x40);
    
//		MotorPwmRight_WriteCompare1(astic[0]);
//		MotorPwmLeft_WriteCompare1(astic[1]);
//		MotorPwmRight_WriteCompare2(astic[2]);
//		MotorPwmLeft_WriteCompare2(astic[3]);
				
	}


	
    LCD_Char_1_ClearDisplay();



	while(1){		
		switch (mode){
			case 0:
				mode0();
				break;
			case 1:
				mode1();
				break;
			case 2:
				mode2();
				break;
			case 3:
				mode3();
				break;
			case 4:
				mode4();
				break;
		}
		Delay(1);
		
        if(modeBuff != mode){LCD_Char_1_ClearDisplay();}
        modeBuff = mode;		
	}
    
}
