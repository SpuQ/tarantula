#ifndef QSTACK_H
#define QSTACK_H

/*
 * 	qstack.h -		A priority stack implementation for the Qcumber mechanism
 * 	Origin:	13/11/2014
 * 	Author: Tom Santens
 * 			tom@pagoni.org
 * 	Source: github.com/SpuQ
 */

typedef struct{
	int priority;
	char* service;
	char* argument;
	char* message;
} _QPACKET;

/**
 * 	_Qstack_init() initializes the given array of QPACKETs as a stack.
 * 	Returns 0 on success.
 */
extern int _Qstack_init(_QPACKET* stack);

/**
 *	_Qstack_put() puts the packet onto the given stack.
 *	returns 0 when success, and a negative value when an error occurred.
 */
extern int _Qstack_put(_QPACKET* stack, _QPACKET packet);

/**
 *	_Qstack_get() gets the packet with the highest priority from the stack.
 *	When positive or 0, the return value represents the number of elements left on the stack. When
 *	negative, something went wrong.
 */
extern int _Qstack_get(_QPACKET* stack, _QPACKET packet);

/**
 * 	_Qstack_package() makes a _QPACKET of the given arguments
 */
extern int _Qstack_package(_QPACKET *packet, char* service, char* argument, char* message, int *priority);

/**
 * 	_Qstack_package() unpacks the _QPACKET in its elements
 */
extern int _Qstack_unpackage(_QPACKET *packet, char* service, char* argument, char* message, int *priority);


#endif /* !QSTACK_H */
