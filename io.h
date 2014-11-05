#ifndef TARANTULA_IO_H
#define TARANTULA_IO_H

/*
 * 	tarantula/io.h - 	This module is a driver for the onboard I/O on Tarantula
 *
 * 	Origin:	30/06/2013, 	last update: 05/11/2014
 * 	Author: Tom Santens
 * 			tom@pagoni.org
 */


/**
 * 	_io_setPinDirection() sets the data direction of the requested pin on the given port.
 * 	valid ports are those on the Tarantula's edge: 'A','B','D','F'. Valid direction values are
 * 	'i' for digital input, and 'o' for digital output.
 *  this function returns error (-1) when port or direction is invalid.
 */
extern int _io_setPinDirection(char port, int pinnr, char direction);

/**
 * 	_io_setPinValue() writes the value to the requested pin.
 * 	Note that value is an unsigned integer. Therefore true is used for
 *  any value different form 0, and false for 0.
 *  this function returns error (-1) when port is invalid.
 */
extern int _io_setPinValue(char port, int pinnr, unsigned int* value);

/**
 * 	_io_getPinValue() puts the bit-value of the requested pin in value.
 * 	Note that value is an unsigned integer. Therefore true is represented
 * 	by any value different form 0, and false by 0.
 *  this function returns error (-1) when port is invalid.
 */
extern int _io_getPinValue(char port, int pinnr, unsigned int* value);

/**
 * 	_io_init() initializes the onboard io.
 */
extern void _io_init(void);

/**
 * 	_io_LED1(), _io_LED2() and _io_LED3() control the state of the LEDs according to these values:
 * 	0: LED off, 1: LED on, 2: toggle LED.
 */
extern void _io_LED1(int value);
extern void _io_LED2(int value);
extern void _io_LED3(int value);

/*
 *	_io_buttons() checks whether there has been a state-change on one or both buttons. The argument
 *	excepts pointers to variables containing the previous button states, and overwrites them with the
 *	new state. This function returns the number of changes.
 */
extern int _io_buttons(int *button1, int *button2);

/*
 * 	When called in a loop, _io_heartbeat() generates heartbeat-alike pulse on LED0. On the
 * 	hardware this LED is indicated by a heartbeat-waveform icon.
 */
extern void _io_heartbeat(void);

#endif	/* !TARANTULA_IO_H */
