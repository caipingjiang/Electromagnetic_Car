#include "zf_common_headfile.h"
#include "my_adc.h"
void my_adc_init()
{
	adc_init(ADC_CHANNEL1, ADC_8BIT);
	adc_init(ADC_CHANNEL2, ADC_8BIT);
	adc_init(ADC_CHANNEL3, ADC_8BIT); 
	adc_init(ADC_CHANNEL4,ADC_8BIT);  
}
