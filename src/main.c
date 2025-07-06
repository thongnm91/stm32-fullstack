#include <stdio.h>
#include <stddef.h>
#include "stm32l1xx.h"

#include "include.h"

int main(void)
{
	SetSysClk();
	uart2_tx_init();
	uint8_t am2302[4] = {0x00};

  while (1)
  {
	  //If request success then read humidity and temperature and send debugger
	  if(am2302Request(am2302)){
		  am2302ShowUart2(am2302);
	  }
	  systickDelayMs(3000);
  }
  return 0;
}
