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
	while(1){		
		printf("papsdapd");
		for(int i = 0; i < 90;i++){		
		servo1->setServoPosition(i);
		servo2->setServoPosition(i);
		servo3->setServoPosition(i);
		//usleep(100000);
	}
	for(int i = 90; i >0;i--){
		servo1->setServoPosition(i);
		servo2->setServoPosition(i);
		servo3->setServoPosition(i);
		//usleep(100000);
	}
	}
	return 0;
}
