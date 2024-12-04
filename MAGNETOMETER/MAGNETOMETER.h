/*MAGNETOMETER.H
        Created on: Dec 03, 2024
        Authors: Ximena Zepeda and Claudio Morales
*/
#ifndef INC_MAGNETOMETER_H_
#define INC_MAGNETOMETER_H_
#include<stdint.h>
#include<stdbool.h>

#define CONF_REGISTER_A                     0x00    //Output rate
#define CONF_REGISTER_B                     0x01    //Device gain
#define MODE_REGISTER_READ_OR_WRITE         0x02    //Single-Measurement Mode
#define DATA_OUTPUT_X_MSB_REGISTER          0x03
#define DATA_OUTPUT_X_LSB_REGISTER          0x04
#define DATA_OUTPUT_Z_MSB_REGISTER          0x05
#define DATA_OUTPUT_Z_LSB_REGISTER          0x06
#define DATA_OUTPUT_Y_MSB_REGISTER          0x07
#define DATA_OUTPUT_Y_LSB_REGISTER          0x08
#define STATUS_REGISTER                     0x09
#define IDENTIFICATION_REGISTER_A           0x0A
#define IDENTIFICATION_REGISTER_B           0x0B
#define IDENTIFICATION_REGISTER_C           0x0C
#define MAGNETOMETER_I2C_ADDRESS            0x1E

void magnetometer_init(void);
void magnetometer_read(float * GYRO_COOKED, float * ACCEL_COOKED);

#endif /*INC_MAGNETOMETER_H*/
