
#ifndef DRIVERS_RGB_LED_RGB_LED_H_
#define DRIVERS_RGB_LED_RGB_LED_H_

#include "gpio.h"
#include "stdint.h"

#define RGB_R_PIN LL_GPIO_PIN_0
#define RGB_G_PIN LL_GPIO_PIN_1
#define RGB_B_PIN LL_GPIO_PIN_4

void set_RGB_led(uint8_t R, uint8_t G, uint8_t B);

#endif /* DRIVERS_RGB_LED_RGB_LED_H_ */
