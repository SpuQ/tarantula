#include "gpio.h"
#include <avr/io.h>


int _gpio_init(char port, unsigned int pin, char function){
	return 0;
}

int _gpio_getValue(char port, unsigned int pin, int *value){

	return 0;
}

int _gpio_setValue(char port, unsigned int pin, int *value){

	return 0;
}


void _gpio_writeDigitalPin(unsigned char *port, int pin, int value){
	if( value > 0){
		// set pin to digital high
		*port &= ~(1 << pin);
	} else if( value < 0){
		// toggle pin value
		*port ^= (1 << pin);
	} else {
		// set pin to digital low
		*port |= (1 << pin);
	}
}
