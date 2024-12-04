/*MPU6050.H 
        Created on: Dec 03, 2024
        Authors: Ximena Zepeda and Claudio Morales
*/


#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <stdint.h>
//registros del sensor MPU6050
#define MPU6050_ADDRESS       0x68 // Direcci�n I2C del MPU6050
#define PWR_MGMT_1            0x6B // Registro de gesti�n de energ�a
#define CONFIG                0x1A // Registro de configuraci�n
#define GYRO_CONFIG           0x1B // Registro de configuraci�n del giroscopio
#define WHO_I_AM              0x75 // no le entendi
#define ACCEL_CONFIG          0x1C // Registro de configuraci�n del aceler�metro
#define ACCEL_XOUT_H          0x3B // Primer registro de lectura de datos (aceler�metro)
#define ACCEL_XOUT_L          0x3C
#define ACCEL_YOUT_H          0x3D // Registro para aceleraci�n en Y (MSB)
#define ACCEL_YOUT_L          0x3E // Registro para aceleraci�n en Y (LSB)
#define ACCEL_ZOUT_H          0x3F // Registro para aceleraci�n en Z (MSB)
#define ACCEL_ZOUT_L          0x40 // Registro para aceleraci�n en Z (LSB)

#define GYRO_XOUT_H           0x43 // Primer registro de lectura de datos (giroscopio)
#define GYRO_XOUT_L           0x44
#define GYRO_YOUT_H           0x45 // Registro para giroscopio en Y (MSB)
#define GYRO_YOUT_L           0x46 // Registro para giroscopio en Y (LSB)
#define GYRO_ZOUT_H           0x47 // Registro para giroscopio en Z (MSB)
#define GYRO_ZOUT_L           0x48 // Registro para giroscopio en Z (LSB)

float GYRO_COOKED[3];
float ACCEL_COOKED[3];

void mpu_init(void);
void mpu_read(float * GYRO_COOKED, float * ACCEL_COOKED);


#endif /* INC_MPU6050_H_ */