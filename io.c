#include "io.h"
#include <avr/io.h>

void _io_setBit(unsigned char* byte, int bitnr);
void _io_clrBit(unsigned char* byte, int bitnr);
void _io_tglBit(unsigned char* byte, int bitnr);
unsigned char _io_getBit(unsigned char* byte, int bitnr);

int _io_setPinDirection(char port, int pinnr, char direction){
	void* ddr;
	_SFR_IO8(0x01) = 0;
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

	*value = (unsigned int)(_io_getBit(ioport, (unsigned int)pinnr));

	return 0;
}

int _io_setPinValue(char port, int pinnr, unsigned int* value){
	unsigned char *ioport;

	switch(port){
		case 'A':	ioport=&PORTA;
			break;
		case 'B':	ioport=&PORTB;
			break;
		case 'D':	ioport=&PORTD;
			break;
		case 'F':	ioport=&PORTF;
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
	*byte |= (1 << bitnr);
}

void _io_clrBit(unsigned char* byte, int bitnr){
	*byte &= ~(1 << bitnr);
}

void _io_tglBit(unsigned char* byte, int bitnr){
	*byte ^= (1 << bitnr);
}

unsigned char _io_getBit(unsigned char* byte, int bitnr){
	switch(bitnr){
		case 0: return (unsigned char)((*byte&0x01)>>bitnr);
			break;
		case 1: return (unsigned char)((*byte&0x02)>>bitnr);
			break;
		case 2: return (unsigned char)((*byte&0x04)>>bitnr);
			break;
		case 3: return (unsigned char)((*byte&0x08)>>bitnr);
			break;
		case 4: return (unsigned char)((*byte&0x10)>>bitnr);
			break;
		case 5: return (unsigned char)((*byte&0x20)>>bitnr);
			break;
		case 6: return (unsigned char)((*byte&0x40)>>bitnr);
			break;
		case 7: return (unsigned char)((*byte&0x80)>>bitnr);
			break;
	}

	return (unsigned char) 4;
}

void _io_init(void){
	DDRE=0x1F;

	_io_LED1(0);
	_io_LED2(0);
	_io_LED3(0);
}

void _io_LED1(int value){
	switch(value){
		case 0: (PORTE |= (1 << PE2)); // led off
				break;
		case 1:	(PORTE &= ~(1 << PE2));  // led on
				break;
		case 2: (PORTE ^= (1<<PE2));	//toggle
				break;
	}
}

void _io_LED2(int value){
	switch(value){
		case 0: (PORTE |= (1 << PE3));
				break;
		case 1:	(PORTE &= ~(1 << PE3));
				break;
		case 2: (PORTE ^= (1<<PE3));
				break;
	}
}

void _io_LED3(int value){
	switch(value){
		case 0: (PORTE |= (1 << PE4));
				break;
		case 1:	(PORTE &= ~(1 << PE4));
				break;
		case 2: (PORTE ^= (1<<PE4));
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
