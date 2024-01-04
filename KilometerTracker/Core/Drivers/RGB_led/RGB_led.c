#include "RGB_led.h"

void set_RGB_led(uint8_t R, uint8_t G, uint8_t B)
{
	GPIO_set_pin(RGB_R_PIN, R);
	GPIO_set_pin(RGB_G_PIN, G);
	GPIO_set_pin(RGB_B_PIN, B);
}
