/*
 * button_module.c
 *
 *  Created on: Jan 5, 2024
 *      Author: smuciak
 */
#include "button_module.h"

uint8_t readButton()
{
	return GPIO_is_pin_set(PIN_BUTTON, PIN_BUTTON_MASK);
}

