
#include "OKY3552.h"
#include "usart.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

static struct position last_detected_position;

#define START_MESSAGE_CHARACTER 	'$'
#define START_GNGGA_MESSAGE_STRING	"GNGGA"

uint8_t start_sign_found = 0;
uint8_t gngga_message_string_progress = 0;
uint8_t gngga_message_found = 0;
uint8_t first_comma_found = 0;
uint8_t second_comma_found = 0;
uint8_t third_comma_found = 0;
uint8_t fourth_comma_found = 0;
uint8_t lat_progress = 0;
uint8_t lon_progress = 0;
uint8_t buffer[512];

float latitude = 0.0;
float longitude = 0.0;

uint8_t started = 0;
uint8_t write_index = 0;

uint16_t temp_parse_progress = 0;

struct position get_device_position(void) {

	for (int i = 0; i < 512 - 5; ++i) {  // Ensure buffer has at least 512 elements
		if (buffer[i] == START_GNGGA_MESSAGE_STRING[0] && buffer[i+1] == START_GNGGA_MESSAGE_STRING[1] &&
			buffer[i+2] == START_GNGGA_MESSAGE_STRING[2] && buffer[i+3] == START_GNGGA_MESSAGE_STRING[3] &&
			buffer[i+4] == START_GNGGA_MESSAGE_STRING[4]) {

			// Parse latitude from the buffer
			last_detected_position.LAT = (buffer[i+17] - '0') * 1000 +
										 (buffer[i+18] - '0') * 100 +
										 (buffer[i+19] - '0') * 10 +
										 (buffer[i+20] - '0') +
										 (float)(buffer[i+22] - '0') * 0.1 +
										 (float)(buffer[i+23] - '0') * 0.01 +
										 (float)(buffer[i+24] - '0') * 0.001 +
										 (float)(buffer[i+25] - '0') * 0.0001;

			// Parse longitude from the buffer
			last_detected_position.LON = (buffer[i+29] - '0') * 10000 +
										 (buffer[i+30] - '0') * 1000 +
										 (buffer[i+31] - '0') * 100 +
										 (buffer[i+32] - '0') * 10 +
										 (buffer[i+33] - '0') +
										 (float)(buffer[i+35] - '0') * 0.1 +
										 (float)(buffer[i+36] - '0') * 0.01 +
										 (float)(buffer[i+37] - '0') * 0.001 +
										 (float)(buffer[i+38] - '0') * 0.0001;

			// Parse fix quality from the buffer
			last_detected_position.fix = buffer[i+42] - '0';

			// Assuming other position members need to be set as well

			// Break out of the loop after finding the GNGGA message
			break;
		}
	}


    return last_detected_position;
}

void parse_uart_character(uint8_t character)
{
	if(started == 0 && character == '$')
	{
		started = 1;
	}
	else if(started == 1 && character == '$')
	{
		started = 0;
		write_index = 0;
	}
	else
	{
		buffer[write_index++] = character;
	}
}
//
//void parse_uart_character_2(uint8_t character) {
//
//    if (character == START_MESSAGE_CHARACTER) {
//        start_sign_found = 1;
//        gngga_message_string_progress = 0; // Reset progress if start sign is found
//    } else if (start_sign_found && character == START_GNGGA_MESSAGE_STRING[gngga_message_string_progress]) {
//        gngga_message_string_progress++;
//        if (gngga_message_string_progress == sizeof(START_GNGGA_MESSAGE_STRING) - 1) {
//            // Message found
//            gngga_message_string_progress = 0;
//            start_sign_found = 0;
//            gngga_message_found = 1;
//        }
//    } else {
//        // Reset progress if condition is not met
//        start_sign_found = 0;
//        gngga_message_string_progress = 0;
//    }
//
//    if (gngga_message_found) {
//		if (character == ',' && !first_comma_found) {
//			first_comma_found = 1;
//		} else if (character == ',' && first_comma_found) {
//			second_comma_found = 1;
//		}
//
//		if (second_comma_found) {
//			if (lat_progress < LAT_SIZE) {
//				latitude[lat_progress++] = character;
//			}
//		}
//
//		if (lat_progress >= LAT_SIZE && character == ',' && !third_comma_found) {
//			third_comma_found = 1;
//		} else if (character == ',' && third_comma_found) {
//			fourth_comma_found = 1;
//		}
//
//		if (fourth_comma_found) {
//			if (lon_progress < LON_SIZE) {
//				longitude[lon_progress++] = character;
//			}
//		}
//
//		if (lon_progress >= LON_SIZE) {
//			// Process latitude and longitude
//			float lat = atof((char*)latitude);
//			float lon = atof((char*)longitude);
//
//			temp_parse_progress = (uint16_t)(lon);
//
//			// Handle lat and lon as needed, e.g., update last_detected_position
//			last_detected_position.LAT = lat;
//			last_detected_position.LON = lon;
//
//			// Reset variables for the next message
//			lat_progress = 0;
//			lon_progress = 0;
//			start_sign_found = 0;
//			gngga_message_string_progress = 0;
//			gngga_message_found = 0;
//			first_comma_found = 0;
//			second_comma_found = 0;
//			third_comma_found = 0;
//			fourth_comma_found = 0;
//		}
//	}
//
//}
