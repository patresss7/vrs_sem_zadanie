/*
 * button_module.h
 *
 *  Created on: Jan 5, 2024
 *      Author: smuciak
 */

#ifndef DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_
#define DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_

#include "gpio.h" 
typedef enum {
    NONE = 0,
    RISE = 1,
    FALL = 2
} EDGE_TYPE;

#define PIN_BUTTON 			LL_GPIO_PIN_0
#define PIN_BUTTON_MASK		'b' 
#define SHORT_PRESS_SAMPLES 5
#define LONG_PRESS_SAMPLES	500

#define BUTTON_STATE_INACTIVE 	0
#define BUTTON_STATE_PRESS		1
#define BUTTON_STATE_LONG_PRESS	2

#include "stdint.h"

uint8_t readButton();

#endif /* DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_ */
