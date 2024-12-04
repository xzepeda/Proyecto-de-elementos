/*I2C.H 
        Created on: Dec 03, 2024
        Authors: Ximena Zepeda and Claudio Morales
*/


#ifndef INC_I2C_H_
#define INC_12C_H_

#include <stdint.h>

//REGISTROS DE RELOJ
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608)) //Reloj del puerto
#define SYSCTL_RCGCI2C_R        (*((volatile uint32_t *)0x400FE620)) //Reloj de I2C
#define SYSCTL_PRGPIO_R        (*((volatile uint32_t *)0x400FEA08)) //Bandera de "Peripherial Ready"

//REGISTROS DEL PUERTO B
//PB2 es SCL
#define GPIO_PORTB_DATA_R   (*((volatile uint32_t *)0x400593FC)) //Para los datos del puerto
#define GPIO_PORTB_DIR_R    (*((volatile uint32_t *)0x40059400)) //Para seleccionar funci�n
#define GPIO_PORTB_AFSEL_R  (*((volatile uint32_t *)0x40059420)) //Para seleccionar funci�n alterna
#define GPIO_PORTB_ODR_R    (*((volatile uint32_t *)0x4005950C)) //Para activar el Open Drain
#define GPIO_PORTB_DEN_R    (*((volatile uint32_t *)0x4005951C)) //Para activar funci�n digital
#define GPIO_PORTB_PCTL_R   (*((volatile uint32_t *)0x4005952C)) //Para el control del puerto

//REGISTROS DEL M�UDLO I2C
#define I2C0_MSA_R              (*((volatile uint32_t *)0x40020000)) //I2C Master Slave Adress
#define I2C0_MCS_R              (*((volatile uint32_t *)0x40020004)) //I2C Master Control Status
#define I2C0_MDR_R              (*((volatile uint32_t *)0x40020008)) //I2C Master Data Register
#define I2C0_MTPR_R             (*((volatile uint32_t *)0x4002000C)) //I2C Master Time Period
#define I2C0_MCR_R              (*((volatile uint32_t *)0x40020020)) //I2C Master Congirutation Register

/*
El registro I2C Master Control/Status (I2C_MCS_R) tiene:
-Modo READ-ONLY DATUS: los 7 bits menos significativos son:
    7:Clock Time Out Error  6:BUS BUSY      5:IDLE
    4:Arbitration Lost      3:DataAck       2:AdrAck
    1:Error                 0:CONTROLLER BUSY

-Modo WRITE-ONLY CONTROL_ Los 6 bits menos significativos son:
    6:BURST    5:QuickCommand  4:High Speed Enable
    3:ACK      2:STOP          1:START
    0:RUN
*/
#define I2C_MCS_ACK 0x00000008 //Transmmitter Acknowledge Enable
#define I2C_MCS_DATACK 0x00000008 // Data Acknowledge Enable
#define I2C_MCS_ADRACK 0x00000004 // Acknowledge Address
#define I2C_MCS_STOP 0x00000004 // Generate STOP
#define I2C_MCS_START 0x00000002 // Generate START
#define I2C_MCS_ERROR 0x00000002 // Error
#define I2C_MCS_RUN 0x00000001 // I2C Master Enable

void I2C_INIT(void);
uint8_t  I2C_READ(uint8_t adrrslave, uint8_t registro);
void I2C_WRITE(uint8_t adrrslave, uint8_t data, uint8_t registro);

#endif /*INC_I2C_H_*/