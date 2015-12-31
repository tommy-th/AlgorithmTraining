#include <stdio.h>

int D[60];

int nums(int n){
	int i;
	if (n <= 1) return 1;
	if (n == 2) return 2;
	if (D[n] == 0){
		for (i = 0; i < n; i++){
			D[n] += nums(n - i - 1) * nums(i);
		}
	}
	return D[n];
}
int main(){

	int i, n;

	scanf("%d", &n);

	printf("%d\n", nums(n));

	return 0;
}