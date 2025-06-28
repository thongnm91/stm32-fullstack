#include "include.h"

void pc13_exti_init(void){
	//Disable global interrupts
	__disable_irq();

	//Enable clock access for GPIOC
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	//Set PC13 as input
	GPIOC->MODER &= ~GPIO_MODER_MODER13;

	//Enable clock access to SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//Select PORTC for EXTI13
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

	//Unmask EXTI13
	EXTI->IMR |= EXTI_IMR_IM13;

	//Select falling edge trigger
	EXTI->FTSR |= EXTI_FTSR_FT13;

	//Enable EXTI13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Enable global interrupts
	__enable_irq();
}

/* In main() I have to create ISR function for interrupt:

static void exti_callback(void){
	char buff[50]={0};
	sprintf(buff, "BNT pressed\n\r");
	uart2_write_string(buff);
}
void EXTI15_10_IRQHandler(void){
	//Check if PC13
	if(EXTI->PR & EXTI_PR_PIF13){
		//Clear PR flag
		EXTI->PR |= EXTI_PR_PIF13;
		//To do
		exti_callback();
	}
}
*/
