/*
 * Sensor KY-013,KY-028 Analog temperature
 * Vin 3.3V
 * Sensor Vout : Max 3.3V, Min 0V
 * Sensor Temperature range: -40 -> 125 oC
 * ADC 12bit = 0->4096
 * Decrease 0.017V = Increase 1 oC
 * */
 
 /*
 Steps to convert ADC
1. What ADC bit? 12bit,10bit,8bit,...
2. ADC supply requirements: Max 3.3V or bigger?
3. Sensor Range Max, Min: 
	Voltage out: Max 3.3V, Min 0V
	Temperature range: Max 125C, Min -40C
4. Use a reliable temperature measuring device to check if the temperature and voltage out correspond. Because cheap sensors often give different values ​​than described in the datasheet. If the value is different from the description in the datasheet, I use potensio resistor to adjust the voltage out correctly.
 */
 
float calCelcius(uint32_t adc_raw){
	float vol = adc_raw*(3.3/4096); //Convert current voltage
	float temp = 125-(vol/0.017); //Because 1.7V = 25C => 0.017V per Celcius
	return temp;
}
