#include "accGyrRead.h"
#include <iostream>
#include <unistd.h>
int main(int argc,char **argv)
{
	accGyrRead *acc = new accGyrRead;
	while(1){
		std::system("clear");
	printf("%f acc x \n",acc->getXAcc());
	//usleep(300000);
	printf("%f acc y\n" ,acc->getYAcc());
	//usleep(300000);
	printf("%f acc z\n",acc->getZAcc());
	//usleep(300000);
	printf("%f rot x\n",acc->getXRot());
	//usleep(300000);
	printf("%f rot y\n",acc->getYRot());
	//usleep(300000);
	printf("%f rot z\n",acc->getZRot());
	usleep(160000);
}
	return 0;
}
