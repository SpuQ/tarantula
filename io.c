#include "io.h"
#include <avr/io.h>

int _io_setPinDirection(char port, int pinnr, char direction){
	unsigned char *ddr;

	switch(port){
		case 'A':	ddr=&DDRA;
			break;
		case 'B':	ddr=&DDRB;
			break;
		case 'D':	ddr=&DDRD;
			break;
		case 'F':	ddr=&DDRF;
			break;
		default: return -1;
			break;
	}

	switch(direction){
	case 'i':	_io_clrBit(ddr, pinnr);
		break;
	case 'o':	_io_setBit(ddr, pinnr);
		break;
	default: return -1;
		break;
	}

	return 0;
}

int _io_getPinValue(char port, int pinnr, unsigned int* value){
	unsigned char *ioport;

	switch(port){
		case 'A':	ioport=&PINA;
			break;
		case 'B':	ioport=&PINB;
			break;
		case 'D':	ioport=&PIND;
			break;
		case 'F':	ioport=&PINF;
			break;
		default: return -1;
			break;
	}

	*value = _io_getBit(ioport, pinnr);

	return 0;
}

int _io_setPinValue(char port, int pinnr, unsigned int* value){
	unsigned char *ioport;

	switch(port){
		case 'A':	ioport=&DDRA;
			break;
		case 'B':	ioport=&DDRB;
			break;
		case 'D':	ioport=&DDRD;
			break;
		case 'F':	ioport=&DDRF;
			break;
		default: return -1;
			break;
	}

	switch(*value){
		case 0: _io_clrBit(ioport, pinnr);
			break;
		default: _io_setBit(ioport, pinnr);
			break;
	}

	return 0;
}

/**
 * bit-in-byte manipulations (not in API)
 */
void _io_setBit(unsigned char* byte, int bitnr){
	*byte &= ~(1 << bitnr);
}

void _io_clrBit(unsigned char* byte, int bitnr){
	*byte |= (1 << bitnr);
}

void _io_tglBit(unsigned char* byte, int bitnr){
	*byte ^= (1 << bitnr);
}

_io_getBit(unsigned char* byte, int bitnr){
	return *byte&bitnr;		// TODO - add correct implementation
}

void _io_init(void){
	DDRE=0x1F;

	_io_LED1(0);
	_io_LED2(0);
	_io_LED3(0);
}

void _io_LED1(value){
	switch(value){
		case 0: (PORTE |= (1 << PE2)); // led off
				break;
		case 1:	(PORTE &= ~(1 << PE2));  // led on
				break;
		case 2: (PORTE ^= (1<<PE2));	//toggle
				break;
	}
}

void _io_LED2(value){
	switch(value){
		case 0: (PORTE |= (1 << PE3)); // led off
				break;
		case 1:	(PORTE &= ~(1 << PE3));  // led on
				break;
		case 2: (PORTE ^= (1<<PE3));	//toggle
				break;
	}
}
void _io_LED3(value){
	switch(value){
		case 0: (PORTE |= (1 << PE4)); // led off
				break;
		case 1:	(PORTE &= ~(1 << PE4));  // led on
				break;
		case 2: (PORTE ^= (1<<PE4));	//toggle
				break;
	}
}

int _io_buttons(int *button1, int *button2){
	int changes=0;
	unsigned int tempbut;

		tempbut=*button1;
		if(!(PINE & _BV(PE5)))
		{

			*button1=0xFF;

		}
		else {
			*button1=0x00;
		}
		if(tempbut!=*button1){
				changes++;
		}

		tempbut=*button2;
		if(!(PINE & _BV(PE6)))
		{
			*button2=0xFF;
		}
		else {
			*button2=0x00;
		}
		if(tempbut!=*button2){
				changes++;
		}


	return changes;
}

void _io_heartbeat(void){
	static double i=0;
	i++;

	if(i>=0xFFF){
		i=0;
	}
	else if(i>0x52F){
		_io_LED1(0);
	}
	else if(i>0x4FF){
		_io_LED1(1);
	}
	else if(i>0x02F){
		_io_LED1(0);
	}
	else if(i>=0x000){
		_io_LED1(1);
	}
}
