#include <stdio.h>

int main(){

	int p[6], r[6];
	int i;

	for(i=0; i<6; i++){
		scanf("%d",&p[i]);
	}

	r[0] = 1 - p[0];
	r[1] = 1 - p[1];
	r[2] = 2 - p[2];
	r[3] = 2 - p[3];
	r[4] = 2 - p[4];
	r[5] = 8 - p[5];
	
	for(i=0; i<6; i++){
		printf("%d ",r[i]);
	}

}
