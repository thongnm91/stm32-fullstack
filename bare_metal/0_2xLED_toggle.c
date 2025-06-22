/*
Led LD2 blink PA5 (D13)
Atollic: File/New/(C/C++ project)/C Manged build/Executable Embedded C project/
STM32L1 Boards NUCLEO-L152RE/next/next/next/finish

Some lines has comments and those comments are from STM32L152_reference_manual.pdf
*/

/* Includes */
#include "stm32l1xx.h"
#include "nucleo152start.h"

/* Private typedef */
/* Private define  */
#define HSI_VALUE    ((uint32_t)16000000)

/* Private macro */
/* Private variables */
/* Private function prototypes */
void delay_Ms(int delay);

/* Private functions */
void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

  /* Configure the system clock to 32 MHz and update SystemCoreClock */
  SetSysClock();
  SystemCoreClockUpdate();

  /* TODO - Add your application code here */

  RCC->AHBENR|=1; //GPIOA ABH bus clock ON. p154
  //GPIOA->MODER|=0x400; //GPIOA pin 5 to output. 
  GPIOA->MODER|=0x1400; //GPIOA pin 6,5 mode output p184

  /* Infinite loop */
  while (1)
  {
	  GPIOA->ODR=0b1000000; //0010 0000 set pin 5 and 6. p186
	  delay_Ms(500);
	  GPIOA->ODR=0b0100000; //0000 0000 clear pin 5 and 6. p186
	  delay_Ms(500);
  }
  return 0;
}

