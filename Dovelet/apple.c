#include <stdio.h>

int main(){

	int u1,u2,red, blue, in=1,idx=0,i;

	int  sum[1000];

	scanf("%d %d", &red, &blue);

	u1 = red; u2 = blue;

	while(u1!=u2){
		if(u1>u2)
			u1 = u1 - u2;
		else
			u2 = u2 - u1;
	}

	while(in<=u1){
		if(u1%in==0){
			sum[idx]=in;
			idx++;
		}
		in++;
	}

	for(i=0;i<idx;i++){
		printf("%d %d %d\n", sum[i], red/sum[i], blue/sum[i]);
	}
}
