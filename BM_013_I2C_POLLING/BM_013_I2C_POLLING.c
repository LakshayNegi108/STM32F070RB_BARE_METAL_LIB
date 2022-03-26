#include <BML_DRIVER.h>
#include "main.h"

#define SLAVE_ADDR 0x68    /* 1101 000.    DS3231 */
#define SCL_PORT	PORTB
#define SCL_PIN		8

#define SDA_PORT	PORTB
#define SDA_PIN		9

int bcdToDec(uint8_t val) {
	return (int) (((val / 16) * 10) + (val % 16));
}

int main(void)
{
    uint8_t data[7];
    uart_print_config();
    ticks_timer();
    gpio_config(SCL_PORT, SCL_PIN, ALT_MODE, HIGH_SPEED, EN_PU, OD);
    gpio_config(SDA_PORT, SDA_PIN, ALT_MODE, HIGH_SPEED, EN_PU, OD);

    gpio_altfn(SCL_PORT, SCL_PIN, I2C1_SCL_PB8);
    gpio_altfn(SDA_PORT, SDA_PIN, I2C1_SDA_PB9);

    I2C_CONFIG i2c1;
    i2c1.i2c = I2C1;
    i2c1.TIMING = 0x10420F13;

    I2C_INIT(i2c1.i2c, i2c1.TIMING);

    /*                          00    01    02    03    04    05    06 */
       uint8_t timeDateToSet[15] = {0x55, 0x58, 0x10, 0x03, 0x26, 0x09, 0x17, 0};
                                   /* 2017 September 26, Tuesday, 10:58:55 */
//       I2C_MultiWrite(I2C1, SLAVE_ADDR, 0, 7, timeDateToSet);

    while (1) {
    	I2C_MultiRead(i2c1.i2c, SLAVE_ADDR, 0x00, 7, &data);
    	if(ticks_val() > 500){
    		APP_DEBUG("%d:%d:%d ,%d, %d, %d, %d\n\r", bcdToDec(data[2]), bcdToDec(data[1]), bcdToDec(data[0]), bcdToDec(data[3]), bcdToDec(data[4]), bcdToDec(data[5]), bcdToDec(data[6]));
    		ticks_reset();
    	}
    }
}
