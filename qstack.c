#include "qstack.h"
#include <string.h>

int _Qstack_init(_QPACKET* stack){
	return 0;
}

int _Qstack_put(_QPACKET* stack, _QPACKET packet){
	return 0;
}

int _Qstack_get(_QPACKET* stack, _QPACKET packet){
	return 0;
}

int _Qstack_package(_QPACKET* packet, char* service, char* argument, char* message, int *priority){
	strcpy((*packet).service, service);
	strcpy((*packet).argument, argument);
	strcpy((*packet).message, message);
	(*packet).priority = *priority;
	return 0;							//	always success, because 'strcpy()' does not generate errors
}

int _Qstack_unpackage(_QPACKET* packet, char* service, char* argument, char* message, int *priority){
	strcpy((*packet).service, service);
	strcpy((*packet).argument, argument);
	strcpy((*packet).message, message);
	(*packet).priority = *priority;
	return 0;							//	always success, because 'strcpy()' does not generate errors
}
