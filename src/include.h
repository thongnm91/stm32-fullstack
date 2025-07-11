/*
 * include.h
 *
 *  Created on: 29.5.2025
 *      Author: thong
 */
#include <stdio.h>
#include <stddef.h>
#include "stm32l1xx.h"
#include <math.h>
#ifndef INCLUDE_H_
#include <stddef.h>
#include "stm32l1xx.h"
#define INCLUDE_H_

void SetSysClk(void);

uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart2_tx_init();
void uart2_write(unsigned char ch);
void uart2_write_string(char* ch);
char uart2_read();
void uart2_rx_interrupt_init(void);

void pa0_adc_init(void);
void adc_start_conver(void);
uint32_t adc_read(void);

void systickDelayMs(uint32_t delay);
void systickDelayUs(uint32_t delay);

float calCelcius(uint32_t adc_raw);
float calLux(uint32_t adc_raw);

void tim2_1hz_init(void);
void tim2_output_compare_init(void);
void tim3_input_capture_init(void);

void pc13_exti_init(void);

void gpioa_init(uint8_t pin, unsigned char mode, unsigned char status);

int am2302Request(uint8_t *array);
void am2302ShowUart2(uint8_t* am2302);

void I2C1_burstWrite(char saddr, char maddr, int n, char* data);
void I2C1_bursRead(char saddr, char maddr, int n, char *data);
void I2C1_read(char saddr, char maddr, char* data);
void i2c1_init(void);

#endif /* INCLUDE_H_ */
