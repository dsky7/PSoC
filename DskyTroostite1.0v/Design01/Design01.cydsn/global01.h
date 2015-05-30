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
/*PCA9685*/
#define		pca_add			0x40
#define		MODE1			0X00
#define		MODE2			0X01
#define		LED0_ON_L		0X06
#define		LED0_ON_H		0X07
#define		LED0_OFF_L		0X08
#define		LED0_OFF_H		0X09
#define		PRE_SCALE		0XFE

#define		LED_ST			0X06

/*MOTER*/
#define 	SPEED 			0X04
#define 	ACC     		0X05
#define 	DEC     		0X06
#define 	MAX_SPEED   	0X07
#define 	FN_SLP_ACC  	0X0F
#define 	FN_SLP_DEC  	0X10
#define 	OCD_TH      	0X13
#define 	STALL_TH    	0X14
#define     FS_SPD          0X15
#define 	STEP_MODE   	0X16
#define 	KVAL_HOLD		0X09
#define     KVAL_RUN        0X0A
#define     KVAL_ACC        0X0B
#define     KVAL_DEC        0X0C
#define     INT_SPEED       0X0D
#define     ST_SLP          0X0E
#define     FN_SLP_ACC      0X0F
#define     FN_SLP_DEC      0X10

#define     STEP_MODE       0X16

#define     GATECFG1        0X18
#define     GATECFG2        0X19

#define     CONFIG          0X1A

#define     GET_STATUS      0XD0


#define 	RUN_F       	80
#define 	RUN_R       	81
#define 	MOV_F       	64
#define 	MOV_R       	65
#define 	GO_ABS_F		104
#define 	GO_ABS_R		105

/*PS3*/
#define     B_UP            0X01
#define     B_DOWN          0X02
#define     B_RIGHT         0X04
#define     B_LEFT          0X08

#define     B_TRI           0X10
#define     B_XMA           0X20
#define     B_CIR           0X40
#define     B_SQU           0X01           //2BIT目

#define     B_L1            2               //2BIT目
#define     B_L2            4               //2BIT目
#define     B_R1            8               //2BIT目
#define     B_R2            16              //2BIT目

#define     B_ST            0X03              //1BIT目
#define     B_SE            0X0C              //1BIT目



