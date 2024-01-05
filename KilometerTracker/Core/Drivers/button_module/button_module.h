/*
 * button_module.h
 *
 *  Created on: Jan 5, 2024
 *      Author: smuciak
 */

#ifndef DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_
#define DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_

#include "gpio.h"

#define PIN_BUTTON 			LL_GPIO_PIN_0
#define PIN_BUTTON_MASK		'b'

#include "stdint.h"

uint8_t readButton();

#endif /* DRIVERS_BUTTON_MODULE_BUTTON_MODULE_H_ */
