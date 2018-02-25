#include "accGyrRead.h"
#include <iostream>
#include <unistd.h>

#define RAD2DEG 57.2957795
int main(int argc,char **argv)
{
	float xRotation,yRotation,zRotation;
	accGyrRead *acc = new accGyrRead;
	clock_t begin = clock();
	//usleep(10000000);
	while(1){
		std::system("clear");
	printf("%f acc x \n",acc->getXAcc());
	printf("%f acc y\n" ,acc->getYAcc());
	printf("%f acc z\n",acc->getZAcc());
	printf("%f rot/s x\n",acc->getXRot());
	printf("%f rot/s y\n",acc->getYRot());
	printf("%f rot/s z\n",acc->getZRot());
	printf("%f rot x\n",xRotation);
	usleep(100000);
	xRotation += RAD2DEG*acc->getXRot()*(clock()-begin)/CLOCKS_PER_SEC;
	yRotation += RAD2DEG*acc->getYRot()*(clock()-begin)/CLOCKS_PER_SEC;
	zRotation += RAD2DEG*acc->getZRot()*(clock()-begin)/CLOCKS_PER_SEC;
	begin = clock();
}
	return 0;
}
