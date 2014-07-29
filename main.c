#include <inttypes.h>

#include "i2c.h"

uint8_t characters[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000,
                        0b10011001, 0b10010010, 0b10000010, 0b11111000,
                        0b10000000, 0b10010000};

void send_2dec(uint8_t value) {
	send_i2c(64, characters[value%10]);
	send_i2c(66, characters[(value/10)%10]);
}

int main (void) {

	send_2dec(123);

	return 0;
}
