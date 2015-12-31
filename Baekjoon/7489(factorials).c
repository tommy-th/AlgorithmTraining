#include <stdio.h>

int F[1001];

int facto_remain(int n){
	int result;
	if (F[n]) return F[n];
	if (n <= 1) return 1;
	result = facto_remain(n - 1);
	F[n] = result * n;
	while (F[n] % 10 == 0){
		F[n] /= 10;
	}
	F[n] = F[n] % 100000;
	return F[n];
}

int main(){
	int i, t, k;

	scanf("%d", &t);

	for (i = 0; i < t; i++){
		scanf("%d", &k);
		printf("%d\n",facto_remain(k) % 10);
	}

	return 0;
}