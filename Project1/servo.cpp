#include "servo.h"
#include <wiringPi.h>
#include <pigpio.h>
#include <softPwm.h>
#include <iostream>
servo::servo(int pin, int min, int max){
	
	int range = 1000;
	gpioSetMode(pin,PI_OUTPUT);
	pinMode(pin,OUTPUT);
	digitalWrite(pin,LOW);
	
	this->pin = pin;
	this->min = min;
	this->max = max;
}

void servo::setServoPosition(int deg){
	float pulse = (float(deg)/(180.0/(max-min))+min)*100;
	printf("%f %i\n",pulse,deg);
	gpioServo(pin,pulse);
}
