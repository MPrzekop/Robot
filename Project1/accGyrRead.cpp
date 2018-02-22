#include "accGyrRead.h"
#include <wiringPiI2C.h>

#define MPU6050_GYRO_XOUT_H        0x43   // R
#define MPU6050_GYRO_YOUT_H        0x45   // R
#define MPU6050_GYRO_ZOUT_H        0x47   // R

#define MPU6050_ACC_XOUT_H			 0x3B 
#define MPU6050_ACC_YOUT_H			0x3D
#define MPU6050_ACC_ZOUT_H			0x3F

#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_I2C_ADDRESS        0x68   // I2C
int fd;
accGyrRead::accGyrRead()
{
	fd = wiringPiI2CSetup(MPU6050_I2C_ADDRESS);
	if (fd == -1)
		return;

	wiringPiI2CReadReg8(fd, MPU6050_PWR_MGMT_1);
	wiringPiI2CWriteReg16(fd, MPU6050_PWR_MGMT_1, 0);
}


accGyrRead::~accGyrRead()
{
}

float accGyrRead::getXRot()
{
	return  wiringPiI2CReadReg8(fd, MPU6050_GYRO_XOUT_H);;
}

float accGyrRead::getYRot()
{
	return  wiringPiI2CReadReg8(fd, MPU6050_GYRO_YOUT_H);
}

float accGyrRead::getZRot()
{
	return wiringPiI2CReadReg8(fd, MPU6050_GYRO_ZOUT_H);
}

float accGyrRead::getXAcc()
{
	return wiringPiI2CReadReg8(fd, MPU6050_ACC_XOUT_H);
}

float accGyrRead::getYAcc()
{
	return wiringPiI2CReadReg8(fd, MPU6050_ACC_YOUT_H);
}

float accGyrRead::getZAcc()
{
	return wiringPiI2CReadReg8(fd, MPU6050_ACC_ZOUT_H);
}


