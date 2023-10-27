#ifndef PROTOCOM_H
#define PROTOCOM_H

void uartInitChar();
void uartWriteChar(char);
char uartRead();

void i2cInit(int);
void i2cWriteChar(char);
char i2cReadChar();

void spiInit();
void spiWriteChar(char);
char spiReadChar();

#endif