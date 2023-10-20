typedef unsigned char *PUINT8;
typedef unsigned char __xdata *PUINT8X;
typedef const unsigned char __code *PUINT8C;
typedef unsigned char __xdata UINT8X;
typedef unsigned char  __data             UINT8D;

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "CH559.h"
#include "util.h"
#include "USBHost.h"
#include "uart.h"
#include "main.h"

SBIT(LED, 0x90, 6);

void main(){
    unsigned char s;
    uint16_t i;
    initClock();
//    initUART0(1000000, 1);
    initUART0(256000, 1);
	putchar('s');putchar('t');putchar('\r');putchar('\n');
    DEBUG_OUT("Startup\n");
    resetHubDevices(0);
    resetHubDevices(1);
    initUSB_Host();
    DEBUG_OUT("Ready\n");

    P1_DIR |= ( LED1 | LED2 | SW_RST | SW_STROB | SW_DAT );
    P1 &=  ~( LED1 | LED2 | SW_RST | SW_STROB | SW_DAT );
    P3_DIR |= ( SW_CLK );
    P3 &= ~( SW_CLK );

    SW_RST_HIGH;
    for(i = 0; i < 2000; i++);
    SW_RST_LOW;
    


//	putchar('r');putchar('d');putchar('\r');putchar('\n');
//	sendProtocolMSG(MSG_TYPE_STARTUP,0, 0x00, 0x00, 0x00, 0);
    while(1)
    {
//        if(!(P4_IN & (1 << 6)))
//            runBootloader();
//        processUart();
        s = checkRootHubConnections();
        pollHIDdevice();
    }
}