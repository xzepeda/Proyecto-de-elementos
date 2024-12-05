/*I2C.C 
        Created on: Dec 03, 2024
        Authors: Ximena Zepeda and Claudio Morales
*/

#include "I2C.h"
#include<stdint.h>
#include<stdbool.h>



void I2C_INIT(void){
    SYSCTL_RCGCI2C_R |= 0x01;
    while((SYSCTL_RCGCI2C_R&0x01)==0);

    SYSCTL_RCGCGPIO_R |= 0x02;
    while((SYSCTL_PRGPIO_R&0x02)==0);

    GPIO_PORTB_AFSEL_R |= 0x0C;
    GPIO_PORTB_ODR_R  |= 0x08;
    GPIO_PORTB_DEN_R |= 0x0C;
    GPIO_PORTB_DIR_R |= 0x0C;


    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0x0000F000) | (2 << 12);      /*  PortB[3] => GPIO controlled by the function I2C0SDA */
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0x00000F00) | (2 << 8);       /*  PortB[2] => GPIO controlled by the function I2C0SCL */

    I2C0_MCR_R |= 0x10;
    I2C0_MTPR_R |= 0x07;
}

void I2C_WRITE(uint8_t adrrslave, uint8_t data, uint8_t registro){
    while (I2C0_MCS_R & 0x01);                     // Esperar a que el I2C esté inactivo
    I2C0_MSA_R= (adrrslave <<1) & 0xFE;
    I2C0_MDR_R = registro;
    I2C0_MCS_R= I2C_MCS_START | I2C_MCS_RUN; //START y RUN
    while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    //Master Busy?
    while ((I2C0_MRIS_R & 0x01) == 0);  //I2C_0 => Esperar a la bandera RIS (Master Raw Interrupt Status)
    I2C0_MICR_R |= 0x01;                //I2C_0 => Master Interrupt Clear

    I2C0_MDR_R = data;
    I2C0_MCS_R= 0x04 | 0x01; //STOP y RUN
    //Master Busy?
    while ((I2C0_MRIS_R & 0x01) == 0);   //I2C_0 => Esperar a la bandera RIS (Master Raw Interrupt Status)
    I2C0_MICR_R |= 0x01;                 //I2C_0 => Master Interrupt Clear
}

uint8_t I2C_READ(uint8_t adrrslave, uint8_t registro){
    while (I2C0_MCS_R & 0x01);           // Esperar a que el I2C esté inactivo
    I2C0_MSA_R = (adrrslave <<1) & 0xFE; // + 1;
    I2C0_MDR_R = registro;
    I2C0_MCS_R= I2C_MCS_START | I2C_MCS_RUN; //START y RUN
    //Master Busy?
    while ((I2C0_MRIS_R & 0x01) == 0);  //I2C_0 => Esperar a la bandera RIS (Master Raw Interrupt Status)
    I2C0_MICR_R |= 0x01;                //I2C_0 => Master Interrupt Clear

    I2C0_MSA_R = (adrrslave << 1) | 0x01;                    // Dirección del esclavo, bit de lectura
    I2C0_MCS_R = I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP; // START, RUN y STOP
    //Master Busy?
    while ((I2C0_MRIS_R & 0x01) == 0);  //I2C_0 => Esperar a la bandera RIS (Master Raw Interrupt Status)
    I2C0_MICR_R |= 0x01;                //I2C_0 => Master Interrupt Clear

    // while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    // int i=0;
    // for(i=0; i<300; i++);
    // //while ((I2C0_MCS_R&0x40)!=0);
    // //I2C0_MCS_R=(I2C0_MCS_R | 0x07)&0xE7;
    // I2C0_MCS_R=0x01;
    // while((I2C_MCS_RUN&I2C0_MCS_R)!=0);
    // for(i=0; i<300; i++);
    uint8_t output = I2C0_MDR_R;
    return output;
}

