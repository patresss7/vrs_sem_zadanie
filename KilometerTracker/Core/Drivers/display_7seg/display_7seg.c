/*
 * display_7seg.c
 *
 *  Created on: Jan 4, 2024
 *      Author: adami
 */

#include "display_7seg.h"

uint8_t digit = 0;
uint8_t thousands, hundreds, tens, ones;

void extractDigits(uint16_t number) {
    ones = number % 10;
    tens = (number / 10) % 10;
    hundreds = (number / 100) % 10;
    thousands = (number / 1000) % 10;
}

void setDigit()
{
	if(digit == 0)
	{
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1,1,PIN_ENABLE_DIGIT_1_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_10,0,PIN_ENABLE_DIGIT_10_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_100,0,PIN_ENABLE_DIGIT_100_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1000,0,PIN_ENABLE_DIGIT_1000_MASK);
	}
	else if(digit == 1)
	{
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1,0,PIN_ENABLE_DIGIT_1_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_10,1,PIN_ENABLE_DIGIT_10_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_100,0,PIN_ENABLE_DIGIT_100_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1000,0,PIN_ENABLE_DIGIT_1000_MASK);
	}
	else if(digit == 2)
	{
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1,0,PIN_ENABLE_DIGIT_1_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_10,0,PIN_ENABLE_DIGIT_10_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_100,1,PIN_ENABLE_DIGIT_100_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1000,0,PIN_ENABLE_DIGIT_1000_MASK);
	}
	else if(digit == 3)
	{
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1,0,PIN_ENABLE_DIGIT_1_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_10,0,PIN_ENABLE_DIGIT_10_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_100,0,PIN_ENABLE_DIGIT_100_MASK);
		GPIO_set_pin_with_mask(PIN_ENABLE_DIGIT_1000,1,PIN_ENABLE_DIGIT_1000_MASK);
	}
}

void writeNumber(uint8_t digitValue)
{
	// Define segment patterns for each digit with active-low logic
	const uint16_t segmentPatterns[] = {
		// Patterns for digits 0 to 9
		0x003F, // 0
		0x0006, // 1
		0x005B, // 2
		0x004F, // 3
		0x0066, // 4
		0x006D, // 5
		0x007D, // 6
		0x0007, // 7
		0x007F, // 8
		0x006F  // 9
	};

	uint16_t pattern = 0; // Default pattern for unsupported digits

	// Check if digitValue is within the valid range (0 to 9)
	if (digitValue >= 0 && digitValue <= 9)
	{
		pattern = segmentPatterns[digitValue];
	}

	// Set segment pins based on the inverted pattern
	GPIO_set_pin_with_mask(PIN_SEGMENT_A, !(pattern & (1 << 0)), PIN_SEGMENT_A_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_B, !(pattern & (1 << 1)), PIN_SEGMENT_B_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_C, !(pattern & (1 << 2)), PIN_SEGMENT_C_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_D, !(pattern & (1 << 3)), PIN_SEGMENT_D_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_E, !(pattern & (1 << 4)), PIN_SEGMENT_E_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_F, !(pattern & (1 << 5)), PIN_SEGMENT_F_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_G, !(pattern & (1 << 6)), PIN_SEGMENT_G_MASK);
	GPIO_set_pin_with_mask(PIN_SEGMENT_DOT, !(pattern & (1 << 7)), PIN_SEGMENT_DOT_MASK);

}



void writeDigit()
{
	if(digit == 0)
	{
		writeNumber(hundreds);
	}
	else if(digit == 1)
	{
		writeNumber(ones);
	}
	else if(digit == 2)
	{
		writeNumber(tens);
	}
	else if(digit == 3)
	{
		writeNumber(thousands);
	}
}

void handle_display(uint16_t number)
{
	setDigit();

	extractDigits(number);

	writeDigit();

	digit++;
	if(digit > 3)
		digit = 0;
}

