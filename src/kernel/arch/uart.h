#ifndef UART_H
#define UART_H

void init_serial(int speed);
void write_serial_sync(uint8_t c);
int write_buf(uint8_t *buf, int len);
int write_string(char *buf);

#endif
