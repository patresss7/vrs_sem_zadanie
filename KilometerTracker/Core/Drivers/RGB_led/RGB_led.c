#include "RGB_led.h"

void set_RGB_led(uint8_t R, uint8_t G, uint8_t B)
{
	GPIO_set_pin_with_mask(RGB_R_PIN, R, 'a');
	GPIO_set_pin_with_mask(RGB_G_PIN, G, 'a');
	GPIO_set_pin_with_mask(RGB_B_PIN, B, 'a');
}

