#include "include.h"
void systickDelayMs(uint32_t delay){
	//Systick
		SysTick->LOAD = 16000; //Reload with number of clocks per 1 ms (1x10^-3 x 32x10^6)
		SysTick->VAL = 0;//Clear systick current value
		SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_CLKSOURCE;//Enable systick and select internal clk src

		for(uint32_t i = 0; i<delay;i++){
			//Wait until the COUNTFLAG is set
			while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG)){}
		}
		SysTick->CTRL = 0;
}
