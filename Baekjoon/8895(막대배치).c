#include <stdio.h>

long long int F[21];
long long int S[21][21];

long long int facto(int n){
	if (F[n]) return F[n];
	if (n <= 1) return 1;
	F[n] = n * facto(n - 1);
	return F[n];
}

long long int combi(int n, int r){
	long long int result;
	if (r > n || n < 1) return 0;
	result = (facto(n) / facto(n - r)) / facto(r);
	return result;
}

long long int sideview(int n, int r){
	int i;
	long long int result = 0;
	
	if (S[n][r]) return S[n][r];
	if (r < 1) return 1;
	if (r == 1) return facto(n - 1);

	for (i = r - 1; i <= n - 1; i++){
		result += combi(n - 1, i) * facto(n - i - 1) * sideview(i, r - 1);
	}
	S[n][r] = result;
	return S[n][r];
}

long long int allresult(int n, int l, int r){
	int i;
	long long int result = 0;
	if (n == 1 && l * r == 1) return 1;
	if (l * r < 2) return 0;
	if (l == 1){
		return sideview(n - 1, r - 1);
	}
	if (r == 1){
		return sideview(n - 1, l - 1);
	}
	for (i = l - 1; i <= n - r; i++){
		result += combi(n - 1, i)*sideview(i, l - 1)*sideview(n - 1 - i, r - 1);
	}
	return result;
}

int main(){

	int i, t;
	int n, l, r;

	scanf("%d", &t);

	for (i = 0; i < t; i++){
		scanf("%d %d %d", &n, &l, &r);
		printf("%lld\n", allresult(n, l, r));
	}

	return 0;
}