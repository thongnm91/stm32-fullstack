#include <stdio.h>
#include <stddef.h>
#include "stm32l1xx.h"

#include "include.h"

int main(void)
{
	SetSysClk();
	uart2_tx_init();
	i2c1_init();
	I2C1_burstWrite();

  while (1)
  {

	  systickDelayMs(3000);
  }
  return 0;
}
