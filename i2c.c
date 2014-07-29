#include <util/twi.h>

void send_i2c(uint8_t slave, uint8_t data) {
  // I2C
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);                        //TWSTA = TWI START Condition Bit

  while  (!(TWCR & (1<<TWINT)));	// Warten bis fertig

  TWDR = slave;
  TWCR = (1<<TWINT) | (1<<TWEN);

  while  (!(TWCR & (1<<TWINT)));	// Warten bis fertig

  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);

  while  (!(TWCR & (1<<TWINT)));	// Warten bis fertig

  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
