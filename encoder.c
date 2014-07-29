#include "encoder.h"

//			00  01  10  11
int8_t encoder_array[] = {
			 0, -1,  1,  0, // 00
			 1,  0,  0, -1, // 01
			-1,  0,  0,  1, // 10
			 0,  1, -1,  0, // 11
			};

int8_t read_encoder() {
	static uint8_t last_state = 0;
	int8_t retval = 0;

	DDRC &= ~(_BV(PC3) | _BV(PC2));

	uint8_t current_state = (PINC & 0b00001100) | last_state;

	retval = encoder_array[current_state];
	last_state = current_state >> 2;
	return retval;
}
