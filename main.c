#include <inttypes.h>

#include <avr/interrupt.h>
#include "global.h"
#include "uart.h"
#include "sm_driver.h"
#include "speed_cntr.h"
#include "i2c.h"
#include "encoder.h"

//! Global status flags
struct GLOBAL_FLAGS status = {FALSE, FALSE, 0};

void Init(void)
{
	// Init of IO pins
	sm_driver_Init_IO();
	// Init of uart
	InitUART();

	// Set stepper motor driver output
	sm_driver_StepOutput(0);

	// Init of Timer/Counter1
	speed_cntr_Init_Timer1();

	sei();
}



uint8_t characters[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000,
                        0b10011001, 0b10010010, 0b10000010, 0b11111000,
                        0b10000000, 0b10010000};

void send_2dec(uint8_t value) {
	send_i2c(64, characters[value%10]);
	send_i2c(66, characters[(value/10)%10]);
}

int main (void) {
	uint8_t counter  = 0;
	int16_t last_pos = 0;
	int16_t new_pos  = 0;

	Init();

	uart_SendString("\n\rStart\n\r");

	do {
		send_2dec(counter/2);
		counter += read_encoder();
		if (255 == counter) counter += 200;
		else if (200 == counter) counter -= 200;

		if ((status.running != TRUE) && !(PINB & _BV(PB0))) {
			new_pos = (int16_t) counter/2  * 20;
			uart_SendString("new position: ");
			uart_SendInt(new_pos);
			uart_SendString(" steps: ");
			uart_SendInt(new_pos - last_pos);
			uart_SendString("\n\r");
			speed_cntr_Move(new_pos - last_pos, 800, 800, 628);
			last_pos = new_pos;
		}

	} while (1);
	

	return 0;
}
