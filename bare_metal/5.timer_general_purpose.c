/*
 * TIMER indicate time of input or output.
 * Why timer is needed because without timer we cannot measure for example how much bit, how long does it take, when will it stop,...
 * They are used to measuring the pulse length (PWM)
 * There are many timer TIM2->TIM11 connect to difference bus (APB1 or APB2)
 * Each timer have 1->4 channels
 *
 *  			(Prescaler) * (Period)
 * 	Update event =	_______________________
 * 			System clock (32MHz HSI)
 *
 * */

#include "include.h"

void tim2_1hz_init(void){

	//Enable clock access tim2, 16 or 32bit
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//Set prescale value
	TIM2->PSC = 32000; // 32.000 x 1.000 = 32.000.000 x 1s

	//Set auto-reload value
	TIM2->ARR = 2000;

	//Clear counter
	TIM2->CNT = 0;

	//Enable timer
	TIM2->CR1 = TIM_CR1_CEN;
}
