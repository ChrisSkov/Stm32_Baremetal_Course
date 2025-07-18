/*
 * adc.h
 *
 *  Created on: May 21, 2025
 *      Author: Chris
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);
void pa1_adc_interrupt_init(void);


#define SR_EOC			(1U<<1) // end of conversion

#endif /* ADC_H_ */
