#ifndef TARANTULA_GPIO_H
#define TARANTULA_GPIO_H

/*
 * 	tarantula/gpio.h - 	A wrapper for some of the ATmega128's I/O functionalities on the available ports of
 * 						Digital AD Technics Expansion Board REV2.1 "Tarantula".
 *
 * 	Origin:	04/11/2014
 * 	Author: Tom Santens
 * 			tom@pagoni.org
 */

/**
 * 	the _gpio_init() function initializes the given port it's pin with the requested functionality e.g. 'a' for analog input,
 * 	'i' for digital input, 'o' for digital output and 'p' for PWM output.
 * 	returns 0 when successful.
 */
extern int _gpio_init(char port, unsigned int pin, char function);

/**
 * 	the _gpio_setValue() function gets the value from the requested pin's current functionality
 * 	returns 0 when successful
 */
extern int _gpio_getValue(char port, unsigned int pin, int *value);

/**
 * 	the _gpio_setValue() function sets the value of the requested pin's current functionality
 * 	returns 0 when successful
 */
extern int _gpio_setValue(char port, unsigned int pin, int *value);

#endif /* !TARANTULA_GPIO_H */
