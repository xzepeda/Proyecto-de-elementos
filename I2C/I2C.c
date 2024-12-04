/*I2C.C 
        Created on: Dec 03, 2024
        Authors: Ximena Zepeda and Claudio Morales
*/

#include "I2C.h"
#include<stdint.h>
#include<stdbool.h>



void I2C_INIT(void){
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCI2C_R |= 0x01;
    while((SYSCTL_PRGPIO_R&0x02)==0);

    GPIO_PORTB_AFSEL_R |= 0x0C;
    GPIO_PORTB_ODR_R  |= 0x08;
    GPIO_PORTB_DIR_R |= 0x0C;
    GPIO_PORTB_DEN_R |= 0x0C;
    GPIO_PORTB_PCTL_R  |= 0x2200;
    I2C0_MCR_R |= 0x10;
    I2C0_MTPR_R |= 0x07;
}

void I2C_WRITE(uint8_t adrrslave, uint8_t data, uint8_t registro){
    I2C0_MSA_R= (adrrslave <<1) & 0xFE;
    I2C0_MDR_R = registro;
    //while ((I2C0_MCS_R&0x40)!=0);
    //I2C0_MCS_R=(I2C0_MCS_R | 0x07)&0xEF;
    I2C0_MCS_R=0x03; //correccion
    while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    //if((I2C_MCS_ERROR&I2C0_MCS_R)!=0)
    int i=0;
    for(i=0; i<300; i++);
    I2C0_MDR_R = data;
    //while ((I2C0_MCS_R&0x40)!=0);
    //I2C0_MCS_R=(I2C0_MCS_R | 0x07)&0xEF;
    I2C0_MCS_R=0x01;
    while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    for(i=0; i<300; i++);
}

uint8_t I2C_READ(uint8_t adrrslave, uint8_t registro){
    I2C0_MSA_R = (adrrslave <<1) + 1;
    I2C0_MDR_R = registro;
    //while ((I2C0_MCS_R&0x40)!=0);
    //I2C0_MCS_R=(I2C0_MCS_R | 0x07)&0xEF;
    I2C0_MCS_R=0x03;
    while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    int i=0;
    for(i=0; i<300; i++);
    //while ((I2C0_MCS_R&0x40)!=0);
    //I2C0_MCS_R=(I2C0_MCS_R | 0x07)&0xE7;
    I2C0_MCS_R=0x01;
    while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    for(i=0; i<300; i++);
    uint8_t output= I2C0_MDR_R;
    return output;
}

