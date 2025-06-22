/*
Lumen = Lux * met square (m2)
An LED 200 lumen = 200 lux in 1 met square. 
*/
float calLux(uint32_t adc_raw){
	float vol = adc_raw*(3.3/4096); //Convert current voltage
	float lux = (3.3-vol)/0.00056; //0.00056V per 1 lux.
	return lux;
}
