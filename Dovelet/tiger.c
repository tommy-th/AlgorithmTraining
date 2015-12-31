#include <stdio.h>

int fibo(int n){
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	else if (n <= 0)
		return 1;
	else
		return fibo(n - 1) + fibo(n - 2);
}

int main(){

	int i, j, d, k, k1, k2, count = 0, on=0;

	scanf("%d %d", &d, &k);

	k1 = fibo(d - 3);
	k2 = fibo(d - 2);

	for (i = 1; i < k; i++){
		for (j = 1; j <= i; j++){
			if (k1*j + k2*i == k){
				printf("%d\n%d\n", j, i);
				on = 1;
				break;
			}
		}
		if (on) break;
	}
}