#include <stdio.h>

int main(){

	int ux,uy,count=0;
	int s, x, y, dx, dy;

	scanf("%d %d %d %d %d", &s, &x, &y, &dx, &dy);

	ux = x/s%2;
	uy = y/s%2;

	while((ux==uy || x%s==0 || y%s==0)&& count<10000){
		x += dx;
		y += dy;
		ux = x/s%2;
		uy = y/s%2;
		count++;
	}

	if(count>=10000){
		printf("The flea cannot escape from black squares.\n");
	}
	else
		printf("After %d jumps the flea lands at (%d, %d).\n",count, x,y);

}
