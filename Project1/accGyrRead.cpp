#include "accGyrRead.h"
#include <wiringPiI2C.h>
#include <stdint.h>
#include <iostream>
#include <unistd.h>
#define MPU6050_GYRO_XOUT_H        0x43   // R
#define MPU6050_GYRO_XOUT_L        0x44
#define MPU6050_GYRO_YOUT_H        0x45   // R
#define MPU6050_GYRO_YOUT_L        0x46
#define MPU6050_GYRO_ZOUT_H        0x47   // R
#define MPU6050_GYRO_ZOUT_L        0x48

#define MPU6050_ACC_XOUT_H			 0x3B 
#define MPU6050_ACC_XOUT_L			0x3C
#define MPU6050_ACC_YOUT_H			0x3D
#define MPU6050_ACC_YOUT_L			0x3E
#define MPU6050_ACC_ZOUT_H			0x3F
#define MPU6050_ACC_ZOUT_L			0x40

#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_I2C_ADDRESS        0x68   // I2C
int fd;
float zeroGyrX=0,zeroGyrY=0,zeroGyrZ=0,zeroAccX=0,zeroAccY=0,zeroAccZ=0;



accGyrRead::~accGyrRead()
{
}



int16_t readWord(int addr){
int16_t read =  (wiringPiI2CReadReg8(fd, addr)<<8|wiringPiI2CReadReg8(fd, addr+1));
if(read>=0x8000){
	read=-(65536-read);
	
}
return read;
}

float  accGyrRead::getXRot()
{
	
	return (readWord(MPU6050_GYRO_XOUT_H)-zeroGyrX)/131.0;
}
float  accGyrRead::getYRot()
{
	
	return  (readWord(MPU6050_GYRO_YOUT_H)-zeroGyrY)/131.0;
}

float accGyrRead::getZRot()
{
	
	return (readWord(MPU6050_GYRO_ZOUT_H)-zeroGyrZ)/131.0;
}

float  accGyrRead::getXAcc()
{
	return readWord(MPU6050_ACC_XOUT_H)/16384.0;
}

float accGyrRead::getYAcc()
{
	return readWord(MPU6050_ACC_YOUT_H)/16384.0;
}

float  accGyrRead::getZAcc()
{
	return readWord(MPU6050_ACC_ZOUT_H)/16384.0;
}
int accGyrRead::gyroCalibration(){
	for(int i = 0; i < 200;i++){
		zeroGyrX+=readWord(MPU6050_GYRO_XOUT_H);
		zeroGyrY+=readWord(MPU6050_GYRO_YOUT_H);
		zeroGyrZ+=readWord(MPU6050_GYRO_ZOUT_H);
		usleep(100);
	}
	zeroGyrX/=200;
	zeroGyrY/=200;
	zeroGyrZ/=200;
return 1;
}

accGyrRead::accGyrRead()
{
	fd = wiringPiI2CSetup(MPU6050_I2C_ADDRESS);
	if (fd == -1)
		return;

	wiringPiI2CReadReg8(fd, MPU6050_PWR_MGMT_1);
	wiringPiI2CWriteReg16(fd, MPU6050_PWR_MGMT_1, 0);
	wiringPiI2CWriteReg8(fd,0x1A,3);
	//wiringPiI2CWriteReg8(fd,0x1B,0b11100000); //test gyro
	wiringPiI2CWriteReg8(fd,0x1B,0b00000000); //test off set scale +-250
	wiringPiI2CWriteReg8(fd,0x1C,0b00000000);//test acc off set scale to +-2g
	printf("starting gyro calibration\n");
	gyroCalibration();
	printf("done gyro calibration.\n %f zero x \n %f zero y \n %f zero z \n", zeroGyrX,zeroGyrY,zeroGyrZ);
	
}

