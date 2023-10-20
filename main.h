#define SW_RST      (1<<4)      // P1.4
#define SW_STROB    (1<<5)      // P1.5
#define SW_DAT      (1<<6)      // P1.6
#define SW_CLK      (1<<2)      // P3.2,    movied from pin 6 - P5.7/RST

#define SW_RST_LOW      P1 &= ~SW_RST
#define SW_RST_HIGH     P1 |= SW_RST
#define SW_STROB_LOW    P1 &= ~SW_STROB
#define SW_STROB_HIGH   P1 |= SW_STROB
#define SW_DAT_LOW      P1 &= ~SW_DAT
#define SW_DAT_HIGH     P1 |= SW_DAT
#define SW_CLK_LOW      P3 &= ~SW_CLK
#define SW_CLK_HIGH     P3 |= SW_CLK

#define LED1    (1<<2)
#define LED2    (1<<7)

#define LED1_ON     P1 |= LED1;
#define LED1_OFF    P1 &= ~LED1;
#define LED2_ON     P1 |= LED2;
#define LED2_OFF    P1 &= ~LED2;

extern unsigned char __xdata TxBuffer[MAX_PACKET_SIZE];

unsigned char hostCtrlTransfer(unsigned char __xdata *DataBuf, unsigned short *RetLen, unsigned short maxLenght);
unsigned char setUsbConfig( unsigned char cfg );
void hex2bin(unsigned char b);
