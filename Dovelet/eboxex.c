#include <stdio.h>

int main(){

	int n, k, t, f;
	scanf("%d %d %d %d", &n, &k, &t, &f);
	printf("%d\n", n + k*((f - n)/(k-1)));
}