#include "MKL25Z4.h"

//_________________________UART_________________________//

void uartInit(){
    UART0 -> BDH = 0;
    UART0 -> BDL = 26;
    UART0 -> c1 = 0x00;
    UART0 -> c2 = 0;
    UART0 -> c3 = 0;
    UART0 -> C4 = 15;
    SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
    SIM -> SCGC4 |= SIM_SCGC4_UART0_MASK;
    PORTA -> PCR[1] = PORT_PCR_MUX(2);
    PORTA -> PCR[2] = PORT_PCR_MUX(2);
}

void uartWriteChar(char data){
    while(!(UART0 -> S1 & UART0 -> S1_TDRE_MASK))
    UART0 -> D = data;
}

char uartReadChar(){
    while(!(UART0 -> S1 & UART0 -> S1_RDRF_MASK))
    return UART0 -> D;
}


//_________________________I2C_________________________//

void i2cInit(int modo){
    SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;
    PORTA -> PCR[8] = PORT_PCR_MUX(5);
    PORTA -> PCR[9] = PORT_PCR_MUX(5);
    I2C0 -> C1 = I2C_C1_IICEN_MASK;
    if(modo == 0){
        I2C0 -> C1 = I2C_C1_TX_MASK;
    }else{
        I2C0 -> C1 = I2C_C1_MST_MASK;
    }
    I2C0 -> F = I2C_F_ICR(0X14);
    I2C0 -> C1 = I2C_C1_TXAK_MASK;
}

void i2cWriteChar(char data){
    while(I2C0 -> S & I2C0 -> I2C_S_IICIF_MASK)
    I2C0 -> D = data;
}

char i2cReadChar(){
    while(I2C0 -> S & I2C0 -> I2C_S_IICIF_MASK)
    return I2C0 -> D;
}


//_________________________I2C_________________________//

void spiInit(){
    SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTA -> PCR[1] = PORT_PCR_MUX(2);
    PORTA -> PCR[2] = PORT_PCR_MUX(2);
    PORTA -> PCR[3] = PORT_PCR_MUX(2);
    SPI0 -> C1 = SPI_C1(0X50);
    SPI0 -> BR = SPI_BR(0X00);
}

void spiWriteChar(char){
    while(SPI0 -> S & SPI_S_SPTEF_MASK)
    SPI0 -> D = data;
}

char spiReadChar(){
    while(SPI0 -> S & SPI_S_SPRF_MASK)
    return SPI0 -> D;
}