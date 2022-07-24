		/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include	"hw_types.h"
#include	"soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME													1000000
#define TOGGLE          										(0x01u)

//modulo de clock do gpio1
#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			(0x00040000u)

//nome do pino - gpio1_28(p9, 12) - modulo de controle
#define CM_conf_gpmc_ben1      	 								0x0878

//modulo de controle gpio1_21 - usr0
#define CM_conf_gpmc_a5         								0x0854
//modulo de controle gpio1_22 - usr1
#define CM_conf_gpmc_a6         								0x0858
//modulo de controle gpio1_23 - usr2
#define CM_conf_gpmc_a7											0x85C
//modulo de controle gpio1_24 - usr3
#define CM_conf_gpmc_a8											0x860

#define GPIO_OE                 								0x134
#define GPIO_CLEARDATAOUT       								0x190
#define GPIO_SETDATAOUT         								0x194


unsigned int flagBlink;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void ledInit();
static void ledToggle();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(void){

	flagBlink=0;	//init flag
  	
	/* Configure the green LED control pin. */
  	ledInit();
  
  	while (1){
    	/* Change the state of the green LED. */
    	ledToggle();
		delay();
		ledToggle();
		delay();
	}

	return(0);
} /* ----------  end of function main  ---------- */



//contador sem sinal para manipular leds 
unsigned int count = 0;

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
	count ++;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */
void ledInit( ){
	
	unsigned int val_temp; 	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ben1) |= 7;

	//configurando novos modulos de controle
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;

 
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);

	//configurando pinos para saida
	val_temp &= ~(1<<21 | 1<<22 | 1<<23 | 1<<24 | 1<<28);
	HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
		
}/* -----  end of function ledInit  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:  
 * =====================================================================================
 */
void ledToggle( ){
		
	flagBlink ^= TOGGLE;

	if(count <= 3){
		//usr0, usr2 e externo
		if(flagBlink){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<21) | (1<<23) | (1<<28);
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (1<<21) | (1<<23) | (1<<28);
		}
	}else if(count <= 7){
		//usr1, usr3 e externo
		if(flagBlink){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<22) | (1<<24) | (1<<28);
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (1<<22) | (1<<24) | (1<<28);
		}
	}else if(count <= 10){
		//usr1,  externo
		if(flagBlink){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<22) | (1<<28);
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (1<<22) | (1<<28);
		}
	}else if(count <= 20){
		//usr0, usr1, usr2, usr3, led externo	
		if(flagBlink){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<21) | (1<<22) | (1<<23) | (1<<24) | (1<<28);
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (1<<21) | (1<<22) | (1<<23) | (1<<24) | (1<<28);
		}
	}else{
		count = 0;
	}
}/* -----  end of function ledToggle  ----- */
