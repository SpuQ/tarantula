#ifndef QCUMBER_H
#define QCUMBER_H

/*
 * 	qcumber.h -		A mechanism that enables the programmer to call functions defined in his/her program beyond of the scope
 * 					of the program.
 *
 *
 * 	Qcumber packets as recognized and formulated in the i/o streams:
 * 	instruction/answer:
 * 	|STARTBYTE|PRIORITYTAG|<priority>|PRIORITYTAG|SERVICETAG| <service> |SERVICETAG|ARGUMENTTAG| <argument> |ARGUMENTTAG|STOPBYTE|
 *	system message:
 *	|STARTBYTE|PRIORITYTAG|<priority>|PRIORITYTAG|MESSAGETAG| <message> |MESSAGETAG| STOPBYTE  |
 *
 *
 *
 * 	Origin:	08/11/2014		last modified: 13/11/2014
 * 	Author: Tom Santens
 * 			tom@pagoni.org
 * 	Source: github.com/SpuQ
 */

#define QPACKET_STARTBYTE	'<'		// byte that indicates a packet start
#define QPACKET_STOPBYTE	'>'		// byte that indicates a packet stop
#define QPACKET_SERVICETAG	'#'		// byte that is put in front and after a service in the packet
#define QPACKET_ARGUMENTTAG	'*'		// byte that is put in front and after a service argument in the packet
#define QPACKET_MESSAGETAG	'%'		// byte that is put in front and after a system message
#define QPACKET_PRIORITYTAG	'-'		// byte that is put in front and after a priority indicator
#define QPRIORITY_DEFAULT	1		// default priority level

#define QSERVICE_NAMELENGTH	10		// limits the size of the service name
#define QSERVICE_ARGLENGTH	10		// limits the size of the argument
#define QSERVICE_MSGLENGTH	50		// limits the size of a system message

#define QINPUTSTACKSIZE		10		// limits the size of the input stack
#define QOUTPUTSTACKSIZE	10		// limits the size of the output stack

#define QSERVICES	20				// limits the amount of assignable services

/**
 * 	_Qc_addService() makes the function presented in the argument usable from another system via
 * 	the i/o stream. The service name is the identifier whereby this function is recognized by
 * 	the Qcumber mechanism.
 * 	Returns a negative value when no more services can be added, and when all good the total of added services
 */
extern int _Qc_addService(unsigned char* serviceName, int* serviceFunction(unsigned char* ));

/**
 * 	_Qc_message() delivers the argument as a system message to the host.
 * 	Note that the Qcumber mechanism uses this function internally to report anomalies using the QPRIORITY_DEFAULT.
 */
extern int _Qc_message(char *message, int priority);

/**
 *	_Qc_execute() checks for and executes received instructions.
 *	Returns the number of handled instructions. when a negative number is returned, something went wrong.
 */
extern int _Qc_execute(void);

/**
 *	_Qc_putByte() writes the byte to the Qcumber mechanism's input stream.
 *	Returns 0 when successfully presented, and a negative in case an error occurred.
 *	Note: designed to be called whenever a byte is received from the host.
 */
extern int _Qc_putByte(unsigned char* byte);

/**
 * 	_Qc_getByte() gets a byte from the Qcumber mechanism's output stream.
 * 	Returns the number of bytes left in the output buffer when positive. 0 indicates a complete packet
 * 	has been send. When a negative value is returned, there is really nothing left.
 * 	Note: this function is designed to be called in a loop until there are no bytes left to output
 */
extern int _Qc_getByte(unsigned char* byte);

/**
 * 	_Qc_loopback() puts the service and argument as a Qcumber packet on the input stack. This way
 * 	the device gives instructions to itself.
 * 	Returns 0 on success.
 */
extern int _Qc_loopback(unsigned char* service, unsigned char* argument, int priority);

/**
 * 	_Qc_instruct() puts the service and argument as a Qcumber packet on the output stack. Using this function
 * 	discards the device as slave for it instructs/informs the host without request.
 * 	Returns 0 on success.
 */
extern int _Qc_instruct(unsigned char* service, unsigned char* argument, int priority);

/**
 * 	_Qc_init() initializes the Qcumber mechanism.
 * 	Returns 0 on success.
 */
extern int _Qc_init(void);


#endif	/* !QCUMBER_H */
