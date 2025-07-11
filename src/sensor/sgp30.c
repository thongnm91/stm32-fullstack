#include "include.h"

/*CO2 Gas sensor SGP30. Address 0x58*/
#define DEVICE_ADDR (0x58)
#define sgp30_iaq_init (0x2003)

void sgp30_init(void){
	/*Read the device ID*/
	I2C1_Read(DEVICE_ADDR, sgp30_iaq_init);
}
