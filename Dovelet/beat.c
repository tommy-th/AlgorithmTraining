#include <stdio.h>

int main(){

	int s, d, a, b;

	scanf("%d %d", &s, &d);

	a = (s + d) / 2;
	b = s - a;
	if (a - b == d && a>=0 && b>=0)
		printf("%d %d", a, b);
	else
		printf("impossible");


	return 0;
}