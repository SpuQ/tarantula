#include "qcumber.h"
#include "qstack.h"
#include <string.h>

#define QINPUTBUFFERSIZE	300		// TODO calculate inputbuffersize
#define QOUTPUTBUFFERSIZE	300		// TODO calculate outputbuffersize

typedef struct{
	char service[QSERVICE_NAMELENGTH];
	int* function(char*);
} _QSERVICE;

/*	global variables	*/
volatile _QPACKET _Qc_inputStack[QINPUTSTACKSIZE];			// input stack
volatile _QPACKET _Qc_outputStack[QOUTPUTSTACKSIZE];		// output stack
volatile _QSERVICE _Qc_services[QSERVICES];					// list of services

/*	function prototypes for non-API functions */
int _Qc_getService(char* serviceName, int** function);
int _Qc_distilateQpacket(char* buffer, _QPACKET* packet);
int _Qc_packetToString(_QPACKET* packet, char* str);


// TODO service mechanism
int _Qc_addService(unsigned char* serviceName, int* serviceFunction(unsigned char* )){
	static int services = 0;

	if(services >= QSERVICES) return -1;			// check whether we can add another service

	// add new service to list of available services

	return services;
}

int _Qc_message(char *message, int priority){
	_QPACKET packet;
	_Qstack_package(&packet, "/0", "/0", message, &priority);	// make a packet from the arguments
	return _Qstack_put(_Qc_outputStack, packet);				// put packet on the output stack
}

int _Qc_execute(void){
	int* serviceFunction(char *);
	int instructionsHandled=0;
	_QPACKET packet;

	while(_Qstack_get(_Qc_inputStack, packet)>=0){	// check input stack for instructions, if none we're done
		strcpy(packet.message, "\0");				// ignore messages on input stack
		instructionsHandled++;						// count the handled instructions

		// lookup service name in services table and get function.
		if(_Qc_getService(packet.service, serviceFunction)==0){
			// execute service function. If not successful, attach message to packet that indicates problems
			if(!serviceFunction(packet.argument)){
				strcpy(packet.message, "ERROR");
			}
		}
		else{	// if the service was not found, report
			strcpy(packet.argument, "\0");
			strcpy(packet.message, "Unknown service");
		}
		// put packet on output stack. if that didn't work, stop executing and report error.
		if(_Qstack_put(_Qc_outputStack, packet)<0) return -1;
	}

	return instructionsHandled;
}

int _Qc_putByte(unsigned char* byte){
	static int packetflag=0;
	static int counter=0;
	static char inputbuffer[QINPUTBUFFERSIZE+1];
	_QPACKET packet;
	unsigned char temp = *byte;		// buffer the byte, it's probably from a variable that's modified on interrupt

	if(temp == (unsigned char)QPACKET_STARTBYTE){					// if we detect the start of a packet
		packetflag = 1;				// inform system there has been a packet start
		counter = 0;				// reset the input buffer
	}
	else if(temp==(unsigned char)QPACKET_STOPBYTE && packetflag>0){	// if we reached the end of a packet
		// get packet out of the buffer
		if(_Qc_distilateQpacket(inputbuffer, &packet)>=0){
			// throw the packet on the inputstack
			if(_Qstack_put(_Qc_inputStack, packet)<0){
				// attach message of failure and copy packet to output stack
				_Qstack_package(&packet, packet.service, packet.argument, "failed", packet.priority);
				_Qstack_put(_Qc_inputStack, packet);	// and if this would be unsuccessful, the system is quite fucked...
			}
		}
		packetflag = 0;					// reset the input buffer mechanism
		counter = 0;
		inputbuffer[counter]='\0';
	}
	// if there has been a packetstart, and the current input is not the packet stop, append input to buffer
	else if(packetflag>0){
		if(counter<=QINPUTBUFFERSIZE){	//
			inputbuffer[counter]=temp;
			inputbuffer[counter+1]='\0';
			counter ++;
		}
		else{
			_Qc_message("packet rejected", QPRIORITY_DEFAULT);
			counter = 0;					// reset the input buffer mechanism
			packetflag = 0;
			inputbuffer[counter] = '\0';
		}
	}
	else{
		// TODO remove this once tested
		_Qc_message("input thrown away", QPRIORITY_DEFAULT);
	}

}

int _Qc_getByte(unsigned char* byte){
	static int counter=0;
	static int size=0;
	static unsigned char buffer[QOUTPUTBUFFERSIZE+1];
	_QPACKET packet;

	if(counter>=size){
		if(_Qstack_get(_Qc_outputStack, packet)<0) return -1; // get a new packet from the output stack, notify when none left
		size=_Qc_packetToString(&packet, buffer);
		counter=0;
	}

	*byte = buffer[counter];
	counter++;

	return (size-counter);
}

int _Qc_loopback(unsigned char* service, unsigned char* argument, int priority){
	_QPACKET packet;
	_Qstack_package(&packet, service, argument, "/0", &priority);	// make a packet from the arguments
	return _Qstack_put(_Qc_inputStack, packet);						// put packet onto the input stack
}

int _Qc_instruct(unsigned char* service, unsigned char* argument, int priority){
	_QPACKET packet;
	_Qstack_package(&packet, service, argument, "/0", &priority);	// make a packet from the arguments
	return _Qstack_put(_Qc_outputStack, packet);					// put packet onto the output stack
}

int _Qc_init(void){
	// initialize input stack
	// initialize output stack
	return 0;
}

/*
 * =============================================================================================================
 * 	functions not presented in the API
 * =============================================================================================================
 */

/**
 * 	_Qc_getService() searches the service-list for the service name, and copies a pointer to the corresponding
 * 	service function into the argument's function
 *
 */
// TODO get service
int _Qc_getService(char* serviceName, int** function){
	return 0;
}

/**
 * 	_Qc_distilateQpacket() removes the tags and extracts the values from the buffer
 */
// TODO distilator
int _Qc_distilateQpacket(char* buffer, _QPACKET* packet){

	return 0;
}

/**
 *	_Qc_packetToString() makes a formatted string from a _QPACKET
 *	returns the number of bytes in the str array
 */
// TODO
int _Qc_packetToString(_QPACKET* packet, char* str){

	return strlen(str);
}

