#include <stdint.h>
#include <string.h>
#include "x86_asm_inline.h"

#define DLAB_BIT		0x80

#define COM1            0x3f8

#define TX_REG              0    /*  Transmit register (WRITE) */
#define RX_REG              0    /*  Receive register  (READ)  */
#define IE_REG              1    /*  Interrupt Enable          */
#define II_REG              2    /*  Interrupt ID              */
#define FC_REG              2    /*  FIFO control              */
#define LC_REG              3    /*  Line control              */
#define MC_REG              4    /*  Modem control             */
#define LS_REG              5    /*  Line Status               */
#define MS_REG              6    /*  Modem Status              */

#define DLL_REG             0    /*  Divisor Latch Low byte */
#define DLH_REG             1    /*  Divisor latch High byte */

#define BASE_BAUD_RATE 115200

/* Add uart initialization routine  */
void init_serial(int speed)
{
    uint16_t baud_rate = BASE_BAUD_RATE / speed;

    /* Disable all interrupts for COM1 */
    outb(0x00, COM1 + IE_REG);

    /* Setting baud rate */
    outb(DLAB_BIT, COM1 + LC_REG);
    outb(baud_rate & 0x00FF, COM1 + DLL_REG);
    outb((baud_rate & 0xFF00) >> 8, COM1 + DLH_REG);

    /* 8 bits, no parity, one stop bit AND unset DLAB */
    outb(0x03, COM1 + LC_REG);

    /* Enable FIFO (0),  clear them (1,2), setup 14 byte (maximum) length */
    outb(0xC7, COM1 + FC_REG);

    outb(0x07, COM1 + IE_REG);
    /* Set Aux.Out.2 to enable interrupts, set RTS/DSR */
    /*outb(0x0B, COM1 + MC_REG);*/
}

int is_transmit_empty()
{
    /* Check Empty Transmitter Holding Register bit */
    return inb(COM1 + LS_REG) & 0x20;
}

void write_serial_sync(uint8_t c)
{
    while (is_transmit_empty() == 0);

    outb(c, COM1 + TX_REG);
}

int serial_received()
{
    /* Check Data Ready bit */
    return inb(COM1 + LS_REG) & 1;
}

char read_serial_sync()
{
    while (serial_received() == 0);

    return inb(COM1 + RX_REG);
}

int write_buf(uint8_t *buf, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        write_serial_sync(buf[i]);
    }
    return i;
}

int write_string(char *buf)
{
    return write_buf((uint8_t *)buf, strlen(buf));
}
