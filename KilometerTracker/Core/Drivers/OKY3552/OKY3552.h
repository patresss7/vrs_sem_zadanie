#ifndef DRIVERS_OKY3552_OKY3552_H_
#define DRIVERS_OKY3552_OKY3552_H_

#define LAT_SIZE					9
#define LON_SIZE					10

#include "stdint.h"

extern uint8_t buffer[512];

struct position {
    float LAT;
    uint8_t LAT_hemisphere;
    float LON;
    uint8_t LON_hemisphere;
    uint8_t fix;
};

extern uint16_t temp_parse_progress;

struct position get_device_position(void);
void parse_uart_character(uint8_t character);

#endif /* DRIVERS_OKY3552_OKY3552_H_ */
