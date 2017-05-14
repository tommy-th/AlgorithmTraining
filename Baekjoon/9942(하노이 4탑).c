#include <stdio.h>

long long int H[1010];

long long int hanoi(int n){
	if (n <= 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 3;
	if (H[n]) return H[n];
	H[n] = hanoi(n - 2) * 2 + 3;
	return H[n];
}

int main(){
	int n, i = 1;

	while (scanf("%d", &n) != EOF){
		printf("Case %d: %lld\n", i++, hanoi(n));
	}

	return 0;
}