#include <stdio.h>

int main(){

	int i;
	int c1,c2,c3, c4;
	int a1, a2, b1, b2;

	scanf("%d %d %d %d", &a1, &a2, &b1, &b2);

	c3 = c4 = a2 * b2;

	c1 = a1*b2;
	c2 = b1*a2; 

	c3 = c3 - c1 - c2;

	if (c3 == 0)
		printf("0\n");
	else{
		for (i = 2; i <= c3; i++){
			while(c3 % i == 0 && c4 % i == 0){
				c3 /= i;
				c4 /= i;
			}
		}
		printf("%d/%d\n", c3, c4); 
	}
	return 0;
}