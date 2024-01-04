/*
 * display_7seg.h
 *
 *  Created on: Jan 4, 2024
 *      Author: adami
 */
#ifndef DRIVERS_DISPLAY_7SEG_DISPLAY_7SEG_H_
#define DRIVERS_DISPLAY_7SEG_DISPLAY_7SEG_H_

#include "gpio.h"


#define PIN_ENABLE_DIGIT_1 			LL_GPIO_PIN_13
#define PIN_ENABLE_DIGIT_1_MASK		'b'

#define PIN_ENABLE_DIGIT_10 		LL_GPIO_PIN_14
#define PIN_ENABLE_DIGIT_10_MASK	'b'

#define PIN_ENABLE_DIGIT_100 		LL_GPIO_PIN_10
#define PIN_ENABLE_DIGIT_100_MASK	'a'

#define PIN_ENABLE_DIGIT_1000 		LL_GPIO_PIN_3
#define PIN_ENABLE_DIGIT_1000_MASK	'b'



#define PIN_SEGMENT_A				LL_GPIO_PIN_5
#define PIN_SEGMENT_A_MASK			'b'

#define PIN_SEGMENT_B				LL_GPIO_PIN_4
#define PIN_SEGMENT_B_MASK			'b'

#define PIN_SEGMENT_G				LL_GPIO_PIN_10
#define PIN_SEGMENT_G_MASK			'b'

#define PIN_SEGMENT_D				LL_GPIO_PIN_8
#define PIN_SEGMENT_D_MASK			'a'

#define PIN_SEGMENT_E				LL_GPIO_PIN_9
#define PIN_SEGMENT_E_MASK			'a'

#define PIN_SEGMENT_F				LL_GPIO_PIN_7
#define PIN_SEGMENT_F_MASK			'c'

#define PIN_SEGMENT_C				LL_GPIO_PIN_6
#define PIN_SEGMENT_C_MASK			'b'

#define PIN_SEGMENT_DOT				LL_GPIO_PIN_15
#define PIN_SEGMENT_DOT_MASK		'b'

void handle_display(uint16_t number);


#endif /* DRIVERS_DISPLAY_7SEG_DISPLAY_7SEG_H_ */
