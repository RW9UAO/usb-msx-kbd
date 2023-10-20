
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "CH559.h"
#include "util.h"
#include "uart.h"
#include "main.h"

uint8_t __xdata uartRxBuff[64];
uint8_t __xdata rxPos = 0;

const uint8_t hex2txt[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void hex2bin(unsigned char b){
	putchar(hex2txt[b >> 4]);
	putchar(hex2txt[b&0x0f]);
	putchar(0x20);
}

void processUart(){
    while(RI){
            RI=0;
            uartRxBuff[rxPos] = SBUF;
            if (uartRxBuff[rxPos]=='\n' || rxPos >= 64){
                for (uint8_t i = 0; i < rxPos; i ++ )
                    {
                        printf( "0x%02X ",uartRxBuff[i]);
                    }
                    printf("\n");
                if(uartRxBuff[0]=='k'){
                //if(uartRxBuff[1]==0x61)LED=0;
                //if(uartRxBuff[1]==0x73)LED=1;
                if(uartRxBuff[1]=='b')runBootloader();
                }
            rxPos=0;
            }else{
            rxPos++;
            }
        }
}

void sendProtocolMSG(unsigned char msgtype, unsigned short length, unsigned char type, unsigned char device, unsigned char endpoint, unsigned char __xdata *msgbuffer){
	return;/*
    unsigned short i;
    putchar(0xFE);	
	putchar(length);
	putchar((unsigned char)(length>>8));
	putchar(msgtype);
	putchar(type);
	putchar(device);
	putchar(endpoint);
	putchar(0);
	putchar(0);
	putchar(0);
	putchar(0);
	for (i = 0; i < length; i++)
	{
		putchar(msgbuffer[i]);
	}
	putchar('\n');*/
}

//0x46 - printscreen
//0x54 - right '/'
#define TABLE_SZIE 0x70
const uint8_t scancodes[TABLE_SZIE]={
//  ' '   ' '   ' '   ' '   'a'   'b'   'c'   'd'   'e'   'f'   'g'   'h'   'i'   'j'   'k'   'l'		// key on PC
//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F		// scancode on PC
	0xFF, 0xFF, 0xFF, 0xFF, 0x62, 0x72, 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73, 0x04, 0x14,		// key on yamaha

//  'm'   'n'   'o'   'p'   'q'   'r'   's'   't'   'u'   'v'   'w'   'x'   'y'   'z'   '1'   '2'
//	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
	0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x05, 0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75, 0x10, 0x20,		// key on yamaha

//  '3'   '4'   '5'   '6'   '7'   '8'   '9'   '0'   enter esc   bsps  tab   space '-'   '='   '['
//	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F
	0x30, 0x40, 0x50, 0x60, 0x70, 0x01, 0x11, 0x00, 0x77, 0x27, 0x57, 0x37, 0x08, 0x21, 0xFF, 0x12,		// key on yamaha

//  ']'   ' '   '\'   ';'   '''   '`'   ','   '.'   ' '   CAPS  F1    F2    F3    F4    F5    F6
//	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
	0x61, 0xFF, 0xFF, 0x22, 0xFF, 0xFF, 0xFF, 0x32, 0xFF, 0x36, 0x56, 0x66, 0x76, 0x07, 0x17, 0xFF,		// key on yamaha

//  F7    F8    F9    F10   F11   F12   prns  scrol pause insrt home  pgup  delet end   pgdn  arRGT
//	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x46, 0x47, 0x28, 0x18, 0xFF, 0x38, 0xFF, 0xFF, 0x48,		// key on yamaha

//  arLFT arDN  arUP  numlk 'r/'  'r*'  'r-'  'r+'  rEntr 'r1'  'r2'  'r3'  'r4'  'r5'  'r6'  'r7'
//	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F
	0x78, 0x68, 0x58, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// key on yamaha

//  'r8'  'r9'  'r0'  'r.'  ' '   menu  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF		// key on yamaha

//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF
//  ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '   ' '
//	0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

uint8_t __xdata scans[8];

// msgbuffer[0] - flags
#define LEFT_CTRL	0x01
#define LEFT_SHIFT	0x02
#define LEFT_ALT	0x04
#define LEFT_WIN	0x08
#define RIGHT_CTRL	0x10
#define RIGHT_SHIFT	0x20
#define RIGHT_ALT	0x40
#define RIGHT_WIN	0x80

#define SW_PAUSE	10
void SWload( unsigned char addr, unsigned char value ){
	uint8_t i, p;
	addr = addr << 1;
	for( i = 0; i < 7; i++ ){
		SW_CLK_LOW;
		for( p = 0; p < SW_PAUSE / 2; p++ );

		if( addr & 0x80 ) SW_DAT_HIGH;
		else SW_DAT_LOW;
		for( p = 0; p < SW_PAUSE / 2; p++ );

		SW_CLK_HIGH;
		for( p = 0; p < SW_PAUSE; p++ );
		
		addr = addr << 1;
	}
	SW_CLK_LOW;
	for( p = 0; p < SW_PAUSE / 2; p++ );

	if( value ) SW_DAT_HIGH;
	else SW_DAT_LOW;
	for( p = 0; p < SW_PAUSE; p++ );

	SW_STROB_HIGH;
	for( p = 0; p < SW_PAUSE; p++ );
	SW_STROB_LOW;
}

void SETorOFFNumLock( void ){
    //uint8_t len,s;

	PXUSB_SETUP_REQ pSetupReq = ((PXUSB_SETUP_REQ)TxBuffer);
	pSetupReq->bRequestType 	= 0x21;
	pSetupReq->bRequest 		= 0x09;				// set report
	pSetupReq->wValueL 			= 0x00;				// 0x00 mean the report ID is 0
	pSetupReq->wValueH 			= 0x02;				// 0x02 indicated the report is OUTPUT
	pSetupReq->wIndexL 			= 0x00;
	pSetupReq->wIndexH 			= 0x00;
	pSetupReq->wLengthL 		= 0x01;
    pSetupReq->wLengthH 		= 0x00;

//	this type of special request indicates that the host has an OUT transaction and the host outputs one byte of data
//	this byte of data is as follows:

    hostCtrlTransfer(TxBuffer, 0, 0);   
	//putchar('[');	hex2bin( s );	putchar(']');
}



void sendHidPollMSG(unsigned char msgtype, unsigned short length, unsigned char type, unsigned char device, unsigned char endpoint, unsigned char __xdata *msgbuffer,unsigned char idVendorL,unsigned char idVendorH,unsigned char idProductL,unsigned char idProductH){
    unsigned short i;
	uint8_t index, key;
/*    putchar(0xFE);	
	putchar(length);
	putchar((unsigned char)(length>>8));
	putchar(msgtype);
	putchar(type);
	putchar(device);
	putchar(endpoint);
	putchar(idVendorL);
	putchar(idVendorH);
	putchar(idProductL);
	putchar(idProductH);
	for (i = 0; i < length; i++)
	{
		putchar(msgbuffer[i]);
	}
*/


	// have a keyboard message
	if( type == Usage_KEYBOARD && device == 0x00 ){
		if( msgbuffer[ 2 ] == 0x2C ){ LED1_ON; SWload( 0x00, 1 );	// space y0 - x0
		}else{ LED1_OFF; SWload( 0x00, 0 );	}
		if( msgbuffer[ 2 ] == 0x28 ){ LED2_ON; SWload( 0x01, 1 );	// enter y0 - x1
		}else{ LED2_OFF; SWload( 0x01, 0 );	}

//		if( msgbuffer[ 2 ] == 0x53 )SETorOFFNumLock();

		if( length > 8) length = 8;			// array overflow
		for( i = 2; i < length; i++ ){
			index = msgbuffer[i];
			if( index < TABLE_SZIE ){
				if( index == 0 ){
					if( scans[i] != 0 ){
						SWload( scans[i], 0 );
						scans[i] = 0;
					}
				}else{
					key = scancodes[index];
					if( key != 0xFF ){
						if( key != scans[i] ){	// check for key already pressed
							SWload( key, 1 );
							scans[i] = key;
						}
					}
				}
			}
		}
	}

	hex2bin(length);
	hex2bin((unsigned char)(length>>8));
	putchar(0x20);
	hex2bin(msgtype);
	putchar(0x20);
	hex2bin(type);
	putchar(0x20);
	hex2bin(device);
	putchar(0x20);
	hex2bin(endpoint);
	//hex2bin(idVendorL);
	//hex2bin(idVendorH);
	//hex2bin(idProductL);
	//hex2bin(idProductH);
	putchar('>');
	for (i = 0; i < length; i++)	{
		hex2bin(msgbuffer[i]);
	}


	if( msgbuffer[ 2 ] == 0x53 )SETorOFFNumLock();
	//if( msgbuffer[ 2 ] == 0x53 ) setUsbConfig( 0x07);

	putchar(0x0d);putchar(0x0A);




}