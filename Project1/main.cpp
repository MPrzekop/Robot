#include "accGyrRead.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <pigpio.h>
#include "servo.h"

#define RAD2DEG 57.2957795
float xRotation,yRotation,zRotation,xPosition,yPosition,zPosition;
	float xVel=0,yVel=0,zVel=0;
	
	void *program(void*){
		accGyrRead *acc = new accGyrRead;
	clock_t begin = clock();
	//usleep(10000000);
	while(1){
	xRotation += RAD2DEG*acc->getXRot()*(clock()-begin)/CLOCKS_PER_SEC;
	yRotation += RAD2DEG*acc->getYRot()*(clock()-begin)/CLOCKS_PER_SEC;
	zRotation += RAD2DEG*acc->getZRot()*(clock()-begin)/CLOCKS_PER_SEC;
	xVel += acc->getXAcc()*9.81*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	yVel += acc->getYAcc()*9.81*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	zVel += acc->getZAcc()*9.81*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	xPosition += xVel*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	yPosition += yVel*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	zPosition += zVel*float(float(clock()-begin)/float(CLOCKS_PER_SEC));
	begin = clock();
}
free(acc);
	}
	
int main(int argc,char **argv)
{
	pthread_t t1;
	pthread_create(&t1,NULL,program,NULL);
	if(gpioInitialise()<1){
		return -1;
		};
	int read;
	
	servo* servos= new servo[12];
	int* pins = { 21,20,16,12,7,8,25,24,23,18,15,14 };
	for (int i = 0; i < 12; i++) {
		servos[i] = new servo(pins[i], 5, 20);
	}
	while(1){		
		
	}
	for (int i = 0; i < 12; i++) {
		free(servos[i]);
	}
	return 0;
}
