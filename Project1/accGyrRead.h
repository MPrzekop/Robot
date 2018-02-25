#pragma once
class accGyrRead
{
public:
	accGyrRead();
	~accGyrRead();
	float getXRot();
	float  getYRot();
	float getZRot();
	float  getXAcc();
	float getYAcc();
	float getZAcc();
	int gyroCalibration();
};

