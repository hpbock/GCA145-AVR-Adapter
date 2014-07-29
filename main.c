#include <inttypes.h>

#include "i2c.h"

uint8_t characters[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000,
                        0b10011001, 0b10010010, 0b10000010, 0b11111000,
                        0b10000000, 0b10010000};

int main (void) {

	send_i2c(64, characters[0]);
	send_i2c(66, characters[0]);

	return 0;
}
