#pragma once
class servo{
public:
servo(int pin, int max, int min);
~servo();
void setServoPosition(int deg);
int getServoPosition();
private:
int degrees;
int min,max,pin;
};
