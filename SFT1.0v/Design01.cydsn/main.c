#include	"global01.h"
#include    <project.h>
#define     AddLineSensor       4
#define     AddSub1             11
#define     LineFront           0
#define     LineRear            1
#define     LineRight           2
#define     LineLeft            3
#define     flgState2           10

int8        Sforward=-40,Sback=40,Sleft=-40,Sright=40,DirectionFR,DirectionRL,DirectionNextFR;
uint8       Speed=20,ZigBeeModeStage,AutoModeStage,oldRFID;//max0x40
int16      dx[2],dy[2],dangle[2],dvx,dvy,dvangle;
int8        x1=64;
int16        goalFR;
int8        maxSpeed=100;
uint16      delaytime=500;
float       nFR,nRL,nRotate;
int8        OffSetRotate=5,OffSetRL=-1;//rotate+leftmawari,RL+hidariyori        -5
int8        EnabelPS3;
void        PI(void);
void        B_LED_ON(void);
void        R_LED_ON(void);
void        B_LED_OFF(void);
void        R_LED_OFF(void);
uint8       i1,i2,i3,i4,i5;
uint8       LineSensor[4],SendData[4],RFID[9];
uint8       oldRFID,OLD_RFID[8],CheckSumRFID;
uint8       flgException,flgPIPI,flgSlide,flgCompA,flgZigBeeReceived,flgCaught,flgZigBeeMode=0,flgErr;;


uint8       num[17],astic[4];
uint8       sum1,mode;
uint8       ButtonStatus1,ButtonStatus2,CheckSum;
float       Kp=1,ki=1,kd=1;
uint8       ZigBeeMsg;
uint8       CheckRFID(void);
uint8       flgNewRFID;
void PIII(void);
void PI(void);
void PIPI(void);
void RightFrontMotor(int16 nRotate);
void RightRearMotor(int16 nRotate);
void LeftFrontMotor(int16 nRotate);
void LeftRearMotor(int16 nRotate);
void CalMotorSpeed(void);
void Core(void);
void CalcRLRotate(void);
void AcceleratingFR(int16 maxSpeed,float pitch);
void AcceleratingRL(int16 maxSpeed,float pitch);
void CatchRFID(uint8 );
void AssignmentRFID(void);
/*
0:Front
1:Rear
2:Right
3:Left
*/
void LED(uint8 RGB, uint8 time){
    switch(RGB){
        case 1:
            R_LED_ON();
        break;
            
        case 3:
            B_LED_ON();
        break;
    }
    CyDelay(time);
    switch(RGB){
        case 1:
            R_LED_OFF();
        break;
            
        case 3:
            B_LED_OFF();
        break;
    }
}
CY_ISR(mytimer1){
        if(I2C_2_MasterSendStart(AddLineSensor,1)==I2C_2_MSTR_NO_ERROR ){R_LED_OFF();flgErr=0;}else{R_LED_ON();flgErr=1;}
        LineSensor[LineFront]=I2C_2_MasterReadByte(1);
        LineSensor[LineRear]=I2C_2_MasterReadByte(1);
        LineSensor[LineRight]=I2C_2_MasterReadByte(1);
        LineSensor[LineLeft]=I2C_2_MasterReadByte(0);
        I2C_2_MasterSendStop();        
        if(flgErr==1){
        LineSensor[LineFront]=21;
        LineSensor[LineRear]=21;
        LineSensor[LineRight]=21;
        LineSensor[LineLeft]=21;
        }
        
        /*RFID*/
        I2C_2_MasterSendStart(AddSub1,1);
        for(i5=0;i5<8;i5++){RFID[i5]=I2C_2_MasterReadByte(1);}       
        RFID[8]=I2C_2_MasterReadByte(0);
        I2C_2_MasterSendStop();
        
        /*for processing*/
        SendData[0]=RFID[0];
        SendData[1]=RFID[1];
        SendData[2]=RFID[2];
        SendData[3]=RFID[2];

        I2C_2_MasterSendStart(AddLineSensor,0);
        for(i3=0;i3<4;i3++){
            I2C_2_MasterWriteByte(SendData[i3]);
        }
        I2C_2_MasterSendStop();
        
        Core();
}
CY_ISR(myHandler2){
    flgZigBeeReceived=1;
    ZigBeeMsg = UART_2_ReadRxData();
}

CY_ISR(myHandler){
    timer1_Disable();
    uint8 status;
    
    isr_1_ClearPending();
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
	//	if(){
		astic[3] = num[2];//Right UD
		astic[2] = num[3];//Right RL
		astic[1] = num[4];//Left UD
		astic[0] = num[5];//Left RL
      //  }
   	    if((num[7] & B_L1) != 0){//L1
            EnabelPS3 = 0;
		}
   	    if((num[7] & B_R1) != 0){//R1
            EnabelPS3 = 1;
        }
        
		ButtonStatus1 = num[7];
		ButtonStatus2 = num[6];
    }    
    
  //      status=UART_1_ReadRxStatus();
//    switch(status){
//        case UART_1_RX_STS_FIFO_NOTEMPTY:
//            PI();
//            break;
//        case UART_1_RX_STS_PAR_ERROR:
//            PI();
//            break;
//        case UART_1_RX_STS_STOP_ERROR:
//            PI();
//            break;
//        case UART_1_RX_STS_BREAK:
//            PI();
//            break;
//        case UART_1_RX_STS_OVERRUN:
//            PI();
//            break;
//        case UART_1_RX_STS_ADDR_MATCH:
//            PI();
//            break;
//        case UART_1_RX_STS_MRKSPC:
//            PI();
//            break;
//        case UART_1_RX_STS_SOFT_BUFF_OVER:
//            PI();
//            break;
           
 //   }
    timer1_Enable();
}
/*
1:RightRear
2:RightFront
3:LeftFront
4:LeftRear
*/
uint8 CheckRFID(void){//1:new id 
    for( i2=0;i2<8;i2++){
        if(RFID[i2]!=OLD_RFID[i2]){
            flgNewRFID=1;
            AssignmentRFID();
                   
            return 1;
        }        
    }
    return 0;
}
void AssignmentRFID(void){
    for( i2=0;i2<8;i2++){
        OLD_RFID[i2]=RFID[i2];            
    }
}
void CalMotorSpeed(){
    if(flgException!=1){
        if(LineSensor[LineFront]==21 || LineSensor[LineRear]==21){nRotate=0x40;nFR=0x40;nRL=0x40;}
    }
    RightFrontMotor(-1*(nFR+nRL-0x80+nRotate-0x40));        
    RightRearMotor(-1*(nFR-nRL+nRotate-0x40));
    LeftFrontMotor(-1*(nFR-nRL-nRotate+0x40));        
    LeftRearMotor(-1*(nFR+nRL-0x80-nRotate+0x40));
}

void RightFrontMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            CW_CCW_2_Write(1);           
            nPwm = -nRotate;
        }else{
            CW_CCW_2_Write(0);           
            nPwm = nRotate;
        }    
    }
    VDAC8_2_SetValue(nPwm);
}
void RightRearMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            CW_CCW_1_Write(1);           
            nPwm = -nRotate;
        }else{
            CW_CCW_1_Write(0);           
            nPwm = nRotate;
        }    
    }
    VDAC8_1_SetValue(nPwm);
}
void LeftFrontMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            CW_CCW_3_Write(0);           
            nPwm = -nRotate;
        }else{
            CW_CCW_3_Write(1);           
            nPwm = nRotate;
        }    
    }
    VDAC8_3_SetValue(nPwm);
}
void LeftRearMotor(int16 nRotate){
    int16 nPwm;
    if(nRotate==0){
        nPwm = 0;
    }else{
        if(nRotate<-255){nRotate=-255;}
        if(nRotate>255){nRotate=255;}
        if(nRotate<0){
            CW_CCW_4_Write(0);           
            nPwm = -nRotate;
        }else{
            CW_CCW_4_Write(1);           
            nPwm = nRotate;
        }    
    }
    VDAC8_4_SetValue(nPwm);
}

void configPSoC(){
    PI();  
    CyDelay(3000);
    
    /*I2C*/
    I2C_2_Start();
    I2C_1_Start();
    I2C_1_Enable();
    Enable2_Write(1);
    PI();  
    CyDelay(300);


    /*interrupt*/
    isr_1_StartEx((cyisraddress)myHandler);
    isr_1_Enable();    
    
    isr_2_StartEx((cyisraddress)myHandler2);
    isr_2_Enable();
    
    timer1_StartEx((cyisraddress)mytimer1);
    timer1_Enable();
    PI();  
    CYGlobalIntEnable;
        
            /*uart*/
    UART_1_Start();
    UART_1_EnableRxInt();
    
    UART_2_Start();
    //UART_2_EnableRxInt();

    VDAC8_1_Start();
    VDAC8_1_SetValue(0u);
    VDAC8_2_Start();
    VDAC8_2_SetValue(0u);
    VDAC8_3_Start();
    VDAC8_3_SetValue(0u);
    VDAC8_4_Start();
    VDAC8_4_SetValue(0u);

    RUN_BRAKE_1_Write(1);
    RUN_BRAKE_2_Write(1);
    RUN_BRAKE_3_Write(1);
    RUN_BRAKE_4_Write(1);
        
     
    if(astic[1]==0){astic[1] = 0x40;}else{
        nFR = astic[1];
    }
    if(astic[0]==0){astic[0] = 0x40;}else{
        nRL = astic[0];
    }
    if(astic[2]==0){astic[2] = 0x40;}else{
        nRotate = astic[2];
    }
    nFR=0x40;
}
void CalcRLRotate(){
    dx[1]=dx[0];
    dx[0]=( LineSensor[LineFront]-LineSensor[LineRear]);
    dvx=dx[0]-dx[1];
    nRL = 0x40 + Kp*0.9*dx[0] -OffSetRL;//- 1.8*kd*dvx;   
    nRotate = 0x40 + Kp*0.8*( LineSensor[LineFront]+LineSensor[LineRear]-126-OffSetRotate );
}
void AcceleratingFR(int16 maxSpeed,float pitch){//pitch:0-1
    nFR=(maxSpeed-nFR)*pitch+nFR;
}
void AcceleratingRL(int16 maxSpeed,float pitch){//pitch:0-1
    nRL=(maxSpeed-nRL)*pitch+nRL;
    //nRL=0x50;
}


void Core(void){
    if(EnabelPS3==1){/*BluetoothMode*/
//    if(1){/*BluetoothMode*/
    flgException=1;
        B_LED_ON();     
        nRL = astic[0];   
        nFR = astic[1];
        nRotate = astic[2];
        CalMotorSpeed();
    }else{
  //      flgException=0;
        B_LED_OFF();

        if(flgZigBeeMode==1){//ZigBeeMode
            switch(ZigBeeModeStage){
                case 0:
                    if(RFID[8]==0){
                        CalcRLRotate();
                        AcceleratingFR(0x40+DirectionFR,0.1);
                        CalMotorSpeed();                
                    }else{
                        if(CheckRFID()){//caught & stop
                            //DirectionFR=0;
                            R_LED_ON();
                            flgCaught=1;
                            CalcRLRotate();
                            nFR=0x40;
                            //AcceleratingFR(0x40,1);
                            CalMotorSpeed();
                            ZigBeeModeStage++;
                            
                        }
                    }
                    break;
                    
                case 1:  //ZigBeeControl
                    if(flgZigBeeReceived==1){
                        ZigBeeModeStage++;flgPIPI=1;
                        flgZigBeeReceived=0;
                        CatchRFID(ZigBeeMsg);
                    }
                    break;
                    
                case 2://go straight
                    if(DirectionFR!=0){
                        //CatchRFID(ZigBeeMsg);
                        CalcRLRotate();nFR=0x40+DirectionFR;CalMotorSpeed();
                        
                        if(CheckRFID()){//catch
                            CalcRLRotate();nFR=0x40;CalMotorSpeed();flgCaught=1;ZigBeeModeStage--;                           
                        }
                        
                    }else{
                        //R_LED_ON();
                        ZigBeeModeStage++;
                    }
                    break;
                    
                case 3://Slide jump
                    if(LineSensor[LineFront]!=21 && LineSensor[LineRear]!=21){
 //                           AcceleratingRL(0x40+(float)DirectionRL,0.1);
                        flgException=1;nRL=0x40+DirectionRL;
                            nFR=0x40;nRotate=0x40;CalMotorSpeed();
                        }else{//disengage
                            ZigBeeModeStage ++;
                        }
                    
                    break;
                case 4:
                    if(LineSensor[LineFront]!=21 && LineSensor[LineRear]!=21){//catch
                        CalcRLRotate();
                        nFR=0x40;CalMotorSpeed();
                        i4++;
                        if(i4==10){i4=0;ZigBeeModeStage=5;}
                        flgException=0;
                    }else{//slide
                        
                        AcceleratingRL(0x40+(float)DirectionRL,1);
                        nFR=0x40;nRotate=0x40;CalMotorSpeed();
                    }
                        
                     break;
                    
                case 5:
                        CalcRLRotate();nFR=0x40+DirectionNextFR;CalMotorSpeed();
                        
                        if(CheckRFID()){//catch
                            CalcRLRotate();nFR=0x40;CalMotorSpeed();flgCaught=1;ZigBeeModeStage=ZigBeeModeStage-4;                         
                        }
                    
                    break;
                        
                    
            }            
            
        }else{//AutoMode
      
            switch (AutoModeStage){
                case 0:
                    if(oldRFID==RFID[0]){
                        CalcRLRotate();nFR=0x40+DirectionNextFR;
//                        AcceleratingFR(0x40+DirectionNextFR,0.1);
                        CalMotorSpeed();
                    }else{
                        AutoModeStage++;   
                        oldRFID=RFID[0];
                    }

                    break;
                
                case 1:
                    if(DirectionFR!=0){
                        DirectionNextFR=DirectionFR;AutoModeStage=0;
                    }else{
//                        AcceleratingFR(0x40,0.5);
                            nFR=0x40;
                        if(nFR==0x40){AutoModeStage=2;}               
                        }
                    break;
                
                case 2://jump
                    if(LineSensor[LineFront]!=21 || LineSensor[LineRear]!=21){
 //                           AcceleratingRL(0x40+(float)DirectionRL,0.1);
                        nRL=0x40+(float)DirectionRL;
                            nFR=0x40;nRotate=0x40;CalMotorSpeed();
                        }else{//disengage
                            AutoModeStage ++;
                        }
                    break;

                case 3:
                    if(LineSensor[LineFront]!=21 && LineSensor[LineRear]!=21){//catch
                        CalcRLRotate();
                        nFR=0x40;CalMotorSpeed();
                        i4++;
                        if(i4==10){i4=0;AutoModeStage=0;}
                    }else{//slide
                        
                        AcceleratingRL(0x40+(float)DirectionRL,1);
                        nFR=0x40;nRotate=0x40;CalMotorSpeed();
                    }
                    break;
                    
                default:
                    break;
            }
        }               
    }    
}
void CatchRFID(uint8 direction){
    switch(direction){
        case 1:
            DirectionFR = Sforward;DirectionRL = 0;
            break;
        case 2:
            DirectionFR = Sback;DirectionRL = 0;
            break;
        case 3:
            DirectionFR = 0;DirectionRL = Sleft;DirectionNextFR=Sforward;
            break;
        case 4:
            DirectionFR = 0;DirectionRL = Sleft;DirectionNextFR=Sback;
            break;
        case 5:
            DirectionFR = 0;DirectionRL = Sright;DirectionNextFR=Sforward;
            break;
        case 6:
            DirectionFR = 0;DirectionRL = Sright;DirectionNextFR=Sback;
            break;
        case 7:
            break;
        
    }

}
int main()
{
    configPSoC();
    flgZigBeeMode=1;

    
    if(flgZigBeeMode==1){//ZigBee Mode
        oldRFID=1;
        DirectionFR=Sforward;

                
        while(1){
            if(flgNewRFID==1){
                UART_2_PutString("s");
                UART_2_PutArray(RFID,8);
                flgNewRFID=0;
                PIII();
            }
            if(flgCaught==1){
                flgCaught=0;
               // PIPI();
            }
        }
        
        
        
        while(flgCaught!=1){}//wait for caught
        flgCaught=0;
        PIII();
        while(1){
            CyDelay(1000);
            UART_2_PutString("s");
        }
        while(1){

        }
        
        
        while(1){
//            while(flgPIPI!=1){}//wait for ZigBeeMSG
//            flgPIPI=0;PIPI();
       //     UART_2_PutString("s");
         //   UART_2_PutArray(RFID,8);
         //   UART_2_PutString("en");
      //      while(flgCaught!=1){}//wait for caught
        //    PI();flgCaught=0;            
        }
    
    }else{//Auto Mode
        oldRFID=0;
        DirectionNextFR=Sforward;
        while(1){

            switch(RFID[0]){
            case 1:
                DirectionFR = Sforward;DirectionRL = 0;       
                break;
            case 2:
                DirectionFR = 0;DirectionRL = Sright; DirectionNextFR=Sback;
                break;
            case 3:
                DirectionFR = 0;DirectionRL = Sleft;DirectionNextFR=Sforward;
                break;
            }
        }
    }
}

void PI(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    CyDelay(200);
    PWM_1_WriteCompare(0);
    PWM_1_Stop();    
}
void PIPI(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    CyDelay(200);
    PWM_1_WriteCompare(0);
    CyDelay(200);
    PWM_1_WriteCompare(127);
    CyDelay(200);
    PWM_1_WriteCompare(0);
    PWM_1_Stop();    
}
void PIII(void){
    PWM_1_Start();
    PWM_1_WriteCompare(127);
    CyDelay(400);
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
