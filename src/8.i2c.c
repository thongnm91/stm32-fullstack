#include "include.h"

void i2c1_init(void){
	//Enable clock access to i2c1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	//Set PB8 , PB9 mode alternate function
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER8_1;
	GPIOB->MODER |= GPIO_MODER_MODER9_1;

	//Set PB8, PB9 output type to open drain
	/*Reason why output open-drain!
	 * 1. I2C protocol uses shared lines (SCL and SDA) among multiple devices.
	 * 2. Both Master and Slave devices can drive SCL and SDA lines at a same time.
	 * 	It will be conflict or damaged the pin if one device drive HIGH while another pulls LOW.
	 * 3. To avoid, when driving the line low, the device pulls it down to GND
	 * 	When not transmitting, the line is left floating (high impedance).
	 * 	The HIGH is maintained by using pull-up resistors, not by actively driving the line HIGH.
	 * */
	GPIOB->OTYPER |= GPIO_OTYPER_OT_8;
	GPIOB->OTYPER |= GPIO_OTYPER_OT_9;

	//Enable Pullup for PB8 and PB9
	/*Reason why use pull-up!
	 * 1. Without pull-ups, when no device pulls the line low, the SDA/SCL line would float
	 * and resulting in noise or data transmission errors.
	 * */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR9_0;

	/*Reason why software reset is needed
	 * In real-world i2c can get stuck cause Slave devices hold communication too long
	 * Force reset I2C used to get back idle state.
	 * */
	//Enter software reset
	I2C1->CR1 |= I2C_CR1_SWRST;
	//Come out of reset mode
	I2C1->CR1 &= ~I2C_CR1_SWRST;

	/*Setup SCL clock output for I2C*/

	/*//Set CR2 (FREQ)
	 * clock frequency 32Mhz FREQ = APB1 (PCLK1)
	 * If PCLK1 = 32 MHz thì FREQ = 32.
	page 685/911 STM32L152_reference_manual.pdf
	 * */
	I2C1->CR2 = I2C_CR2_FREQ_5;

	/*//Set I2C to standard mode, and calculate 100kHz clock
	 * What formula?
	 	 CCR = PCLK1 / (2×fSCL)
	 	 _fSCL is expected frequence 100kHz
	 *Example: 32,000,000/(2x100,000)=160
	 *Read page 692/911 datasheet.
	 * */
	I2C1->CCR = 160;

	/*Set max rise time TRISE
	 * What formula?
	 * TRISE = (PCLK1/1,000,000) + 1
	 * 	_ 1,000,000 using to ensure rise time is not over 1us as I2C standard at Sm mode
	 * Example: TRISE = (32,000,000 / 1,000,000) + 1 = 33
	 * */
	I2C1->TRISE = 33;

	/*Enable I2C1 module*/
	I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_read(char saddr, char maddr, char* data){
	/*Wait bus I2C free*/
	while (I2C1->SR2 & I2C_SR2_BUSY){}

	/*Transmit START*/
	I2C1->CR1 |= I2C_CR1_START;

	/*Wait start event to be set*/
	while (!(I2C1->SR1 & I2C_SR1_SB)){}

	/*Transmit slave's address with bit WRITE*/
	I2C1->DR = saddr << 1;

	/*Wait address event to be set*/
	while (!(I2C1->SR1 & I2C_SR1_ADDR)){}

	/*Clear addr flag*/
	volatile uint32_t temp;
	temp = I2C1->SR2;

	/*Transmit memory address*/
	I2C1->DR = maddr;

	/*Wait transmit to be empty*/
	while (!(I2C1->SR1 & I2C_SR1_TXE)){}

	/*Transmit restart*/
	I2C1->CR1 |= I2C_CR1_START;

	/*Wait start event to be set*/
	while (!(I2C1->SR1 & I2C_SR1_SB)){}

	/*Transmit slave's address with bit READ*/
	I2C1->DR = (saddr << 1) | 1;

	/*Wait address event to be set*/
	while (!(I2C1->SR1 & I2C_SR1_ADDR)){}

	/*Disable ACK*/
	I2C1->CR1 &= ~I2C_CR1_ACK;

	/*Clear addr flag*/
	temp = I2C1->SR2;

	/*Transmit stop after data received*/
	I2C1->CR1 |= I2C_CR1_STOP;

	/*Wait RXNE event to be set*/
	while (!(I2C1->SR1 & I2C_SR1_RXNE)){}

	/*Read data from DR*/
	*data++ = I2C1->DR;
}
