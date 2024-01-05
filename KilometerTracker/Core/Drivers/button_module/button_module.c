/*
 * button_module.c
 *
 *  Created on: Jan 5, 2024
 *      Author: smuciak
 */
#include "button_module.h" 
uint8_t pin_state = 0;
uint8_t pin_state_prev = 0;
uint8_t pin_state_prev_prev = 0;
uint8_t result = BUTTON_STATE_INACTIVE;
uint8_t long_pressed = 0;
uint16_t active_samples = 0;

uint8_t readButton()
{
	result = BUTTON_STATE_INACTIVE;
	pin_state = GPIO_is_pin_set(PIN_BUTTON, PIN_BUTTON_MASK);

	if(!long_pressed && !pin_state && !pin_state_prev && !pin_state_prev_prev)
	{
		active_samples++;
	}

	if(long_pressed && pin_state && pin_state_prev && pin_state_prev_prev)
	{
		long_pressed = 0;
	}

	if(active_samples > LONG_PRESS_SAMPLES)
	{
		result = BUTTON_STATE_LONG_PRESS;
		active_samples = 0;
		long_pressed = 1;
	}
	else if(active_samples > SHORT_PRESS_SAMPLES)
	{
		if(pin_state && pin_state_prev && pin_state_prev_prev)
		{
			result = BUTTON_STATE_PRESS;
			active_samples = 0;
		}
	}

	pin_state_prev_prev = pin_state_prev;
	pin_state_prev = pin_state;
	return result;
}