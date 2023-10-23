
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

// scroll lock - RUS/LAT
// lALT or rALT - GRAPH
// lWIN or rWIN - SELECT
// Pause - STOP

//0x46 - printscreen
//0x54 - right '/'
// xRUSxLAT
#define SHIFT_FLAG	0x80
#define TABLE_SZIE 	0x70
#define MSX_SHIFT	0x06
#define MSX_CTRL	0x16
#define MSX_GRAPH	0x26
#define MSX_SELECT	0x67
const uint16_t scancodes[TABLE_SZIE]={
//    ' '     ' '     ' '     ' '     'Фa'    'Иb'    'Сc'    'Вd'		// key on PC
//	  0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,		// scancode on PC
	0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x6233, 0x7222, 0x0345, 0x1314,		// key on yamaha

//    'Уe'    'Аf'    'Пg'    'Рh'    'Шi'    'Оj'    'Лk'    'Дl'		// key on PC
//    0x08,   0x09,   0x0A,   0x0B,   0x0C,   0x0D,   0x0E,   0x0F		// scancode on PC
	0x2315, 0x3362, 0x4325, 0x5351, 0x6372, 0x7364, 0x0474, 0x1404,		// key on yamaha

//    'Ьm'    'Тn'    'Щo'    'Зp'    'Йq'    'Кr'    'Ыs'    'Еt'     
//	  0x10,   0x11,   0x12,   0x13,   0x14,   0x15,   0x16,   0x17,
	0x2435, 0x3465, 0x4473, 0x5443, 0x6475, 0x7453, 0x0503, 0x1534,

//	  'Гu'    'Мv'    'Цw'    'Чx'    'Нy'    'Яz'     '!1'    '"2'
// 	  0x18,   0x19,   0x1A,   0x1B,   0x1C,   0x1D,   0x1E,	  0x1F
	0x2523, 0x3571, 0x4513, 0x5524, 0x6505, 0x7554, 0x2020, 0x3230,		// key on yamaha

//    '#3'    '$4'	'%5'    '^6'   	'&7'   	 '*8'   '(9'   	')0'
//	  0x20,  0x21,	 0x22,   0x23, 	0x24,  	 0x25,  0x26,  	 0x27,   
	0x4040, 0x5050, 0x6060, 0xC170, 0x7001, 0x6111, 0x1100, 0x0021,

//    enter   esc     bsps    tab     space   '_-'    		'+='    '{['
//	  0x28,   0x29,   0x2A,   0x2B,   0x2C,   0x2D,   		0x2E,   0x2F
	0x0077, 0x0027, 0x0057, 0x0037, 0x0008, 0x3141|0x8000, 0x1031, 0x6363|0x8000,		// key on yamaha

//    '}]'    		'\|'     ' '     ':;'    '"''    '~`'    '<,'    			'>.'
//	  0x30,   		0x31,   0x32,   0x33,   0x34,   0x35,   0x36,  				0x37,
	0x4444|0x8000, 0x5502, 0x00FF, 0xE190, 0x3001, 0xD5D5, 0x4242|SHIFT_FLAG, 0x1212|SHIFT_FLAG,

//    '?/'   CAPS    F1      F2      F3      F4      F5      F6
//   0x38,   0x39,   0x3A,   0x3B,   0x3C,   0x3D,   0x3E,   0x3F
	0x00FF, 0x0036, 0x0056, 0x0066, 0x0076, 0x0007, 0x0017, 0x0056,		// key on yamaha

//    F7      F8      F9      F10     F11     F12     prns    scrol   pause   insrt   home    pgup    delet   end     pgdn    arRGT
//	  0x40,   0x41,   0x42,   0x43,   0x44,   0x45,   0x46,   0x47,   0x48,   0x49,   0x4A,   0x4B,   0x4C,   0x4D,   0x4E,   0x4F
	0x0066, 0x0076, 0x0007, 0x0017, 0x00FF, 0x00FF, 0x00FF, 0x0046, 0x0047, 0x0028, 0x0018, 0x00FF, 0x0038, 0x00FF, 0x00FF, 0x0078,		// key on yamaha

//    arLFT   arDN    arUP    numlk   'r/'    'r*'    'r-'    'r+'    rEntr   'r1'    'r2'    'r3'    'r4'    'r5'    'r6'    'r7'
//	  0x50,   0x51,   0x52,   0x53,   0x54,   0x55,   0x56,   0x57,   0x58,   0x59,   0x5A,   0x5B,   0x5C,   0x5D,   0x5E,   0x5F
	0x0048, 0x0068, 0x0058, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF,		// key on yamaha

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

uint16_t __xdata scans[8];
uint8_t  __xdata numlock;	// 0 - off
uint8_t  __xdata capslock;	// 0 - off
uint8_t  __xdata ruslat;	// 0 - lat

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
		//for( p = 0; p < SW_PAUSE / 2; p++ );

		if( addr & 0x80 ) SW_DAT_HIGH;
		else SW_DAT_LOW;
		NOP();//for( p = 0; p < SW_PAUSE / 2; p++ );

		SW_CLK_HIGH;
		//for( p = 0; p < SW_PAUSE; p++ );
		
		addr = addr << 1;
	}
	SW_CLK_LOW;
	//for( p = 0; p < SW_PAUSE / 2; p++ );

	if( value ) SW_DAT_HIGH;
	else SW_DAT_LOW;
	NOP();//for( p = 0; p < SW_PAUSE; p++ );

	SW_STROB_HIGH;
	NOP();//for( p = 0; p < SW_PAUSE; p++ );
	SW_STROB_LOW;
}

void SETorOFFNumLock( void ){

	PXUSB_SETUP_REQ pSetupReq = ((PXUSB_SETUP_REQ)TxBuffer);
	pSetupReq->bRequestType 	= 0x21;
	pSetupReq->bRequest 		= 0x09;				// set report
	pSetupReq->wValueL 			= 0x00;				// 0x00 mean the report ID is 0
	pSetupReq->wValueH 			= 0x02;				// 0x02 indicated the report is OUTPUT
	pSetupReq->wIndexL 			= 0x00;				// Interface
	pSetupReq->wIndexH 			= 0x00;
	pSetupReq->wLengthL 		= 0x01;				// Report Length
    pSetupReq->wLengthH 		= 0x00;

//	this type of special request indicates that the host has an OUT transaction and the host outputs one byte of data
//	this byte of data is as follows:
//	numlock		(1<<0)
//	capslock	(1<<1)

	// Data Report
	TxBuffer[ 8 ] = (numlock << 0) | (capslock << 1) | (ruslat << 2);
    hostCtrlTransfer(TxBuffer, 0, 0);   

}



void sendHidPollMSG(unsigned char msgtype, unsigned short length, unsigned char type, unsigned char device, unsigned char endpoint, unsigned char __xdata *msgbuffer,unsigned char idVendorL,unsigned char idVendorH,unsigned char idProductL,unsigned char idProductH){
    unsigned short i;
	uint8_t index;
	uint16_t key;
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
		// array overflow.
		// i have wireless kbd with 13 bytes packet
		if( length > 8 ){
			length = 8;			
			for( i = 0; i < 8; i++) msgbuffer[ i ] = msgbuffer[ i + 1 ];
		} 

//if( msgbuffer[ 2 ] == 0x53 ){ //Num Lock
//	putchar(0x0d);putchar(0x0A);
//	for( i = 0; i < 8; i++)	hex2bin(scans[i]);
//	putchar(0x0d);putchar(0x0A);
//}

		//-------------------------------
		if( msgbuffer[ 2 ] == 0x47 ){	// Scroll Lock			
			if( ruslat ){ LED1_OFF; ruslat = 0;	}else{ LED1_ON; ruslat = 1;	}
			SETorOFFNumLock();
		}
		if( msgbuffer[ 2 ] == 0x53 ){	// Num Lock
			if( numlock ){ numlock = 0;	}else{ numlock = 1;	}
			SETorOFFNumLock();
		}
		if( msgbuffer[ 2 ] == 0x39 ){	// Caps Lock
			if( capslock ){ capslock = 0;	}else{ capslock = 1; }
			SETorOFFNumLock();
		}
		//-------------------------------
		if( msgbuffer[ 0 ] & LEFT_SHIFT || msgbuffer[ 0 ] & RIGHT_SHIFT ){									// shift key pressed
			if( ! (scans[ 0 ] & LEFT_SHIFT) ){																// already pressed
				SWload( MSX_SHIFT, 1 );
				scans[ 0 ] |= LEFT_SHIFT;																	// store shift flag
			}
		}else{																								// shift key release
			if( scans[ 0 ] & LEFT_SHIFT ){																	// shift key was pressed
				SWload( MSX_SHIFT, 0 );
				scans[ 0 ] &= ~LEFT_SHIFT;																	// clear shift flag
			}
		}

		if( msgbuffer[ 0 ] & LEFT_ALT || msgbuffer[ 0 ] & RIGHT_ALT ){
			if( ! (scans[ 0 ] & LEFT_ALT) ){ SWload( MSX_GRAPH, 1 );	scans[ 0 ] |= LEFT_ALT; }
		}else{
			if( scans[ 0 ] & LEFT_ALT){ SWload( MSX_GRAPH, 0 );	scans[ 0 ] &= ~LEFT_ALT; }
		}

		if( msgbuffer[ 0 ] & LEFT_CTRL || msgbuffer[ 0 ] & RIGHT_CTRL ){
			if( ! (scans[ 0 ] & LEFT_CTRL) ){ SWload( MSX_CTRL, 1 );	scans[ 0 ] |= LEFT_CTRL; }
		}else{
			if( scans[ 0 ] & LEFT_CTRL ){ SWload( MSX_CTRL, 0 );	scans[ 0 ] &= ~LEFT_CTRL; }
		}

		if( msgbuffer[ 0 ] & LEFT_WIN || msgbuffer[ 0 ] & RIGHT_WIN ){
			if( ! (scans[ 0 ] & LEFT_WIN) ){ SWload( MSX_SELECT, 1 );	scans[ 0 ] |= LEFT_WIN; }
		}else{
			if( scans[ 0 ] & LEFT_WIN ){ SWload( MSX_SELECT, 0 );	scans[ 0 ] &= ~LEFT_WIN; }
		}
		//-------------------------------
		for( i = 2; i < length; i++ ){
			index = msgbuffer[ i ];
			if( index < TABLE_SZIE ){
				if( index == 0 ){
					if( scans[i] != 0 ){
						if( scans[i] & SHIFT_FLAG ){
							SWload( MSX_SHIFT, 0 );
						}
						SWload( scans[i] & 0x7F, 0 );
						scans[i] = 0;
					}
				}else{
					key = scancodes[index];
					if( key != 0xFF ){
						if( key != scans[i] ){				// check for key already pressed

							//digits	-------------------------------------------------------------------------
							if( index >= 0x1E && index <= 0x27 ){
								if(  msgbuffer[ 0 ] & LEFT_SHIFT || msgbuffer[ 0 ] & RIGHT_SHIFT ){	// shift key pressed
									key = key >> 8;
									if( ! (key & SHIFT_FLAG) ){
										SWload( MSX_SHIFT, 0 );		// release Shift on MSX
									}
									SWload( (key & 0x7F), 1 );
								}else{
									SWload( MSX_SHIFT, 1 );		// press Shift on MSX
									key |= SHIFT_FLAG;
									SWload( (key & 0x7F), 1 );
								}
							}else
							// letters	-------------------------------------------------------------------------
							if( index >= 0x04 && index <= 0x1D ){
								if( ruslat ){
									key = key >> 8;
								}
								SWload( (key & 0x7F), 1 );
							}else
							// signs	-------------------------------------------------------------------------
							if( index >= 0x2D && index <= 0x37 ){
								if( ruslat ){
									switch( index ){
										case 0x2F: key = 0x51; break;	// [{Х
										case 0x30: key = 0x41; break;	// ]}Ъ
										case 0x33: key = 0x71; break;	// ;:Ж
										case 0x34: key = 0x02; break;	// '"Э
										case 0x36: key = 0x22; break;	// ,<Б
										case 0x37: key = 0x32; break;	// .>Ю
									}
									SWload( key, 1 );
								}else{
									if(  msgbuffer[ 0 ] & LEFT_SHIFT || msgbuffer[ 0 ] & RIGHT_SHIFT ){	// shift key pressed
										key = key >> 8;
										if( ! (key & SHIFT_FLAG) ){
											SWload( MSX_SHIFT, 0 );		// release Shift on MSX
										}
										SWload( (key & 0x7F), 1 );
									}else{
										if( key & SHIFT_FLAG ){
											SWload( MSX_SHIFT, 1 );		// press Shift on MSX
										}
										SWload( (key & 0x7F), 1 );
									}
								}
							}else{//	-------------------------------------------------------------------------
								SWload( (key & 0x7F), 1 );
							}
							scans[i] = key;
						}
					}
				}
			}
		}
	}
/*
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

	putchar(0x0d);putchar(0x0A);
*/
}