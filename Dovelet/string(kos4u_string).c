#include <stdio.h>
#define MAX 1000000009
#define LMT 400000005

int F[LMT];

long long int fibo(int n){

	long long int result, t1, t2;

	if (n <= 0) return 0;
	else if (n == 1) return 1;
	else if (n == 2) return 1;

	if (n < LMT){
		if (F[n])
			return F[n];
	}

	if (n % 2 == 0){
		t1 = fibo(n / 2);
		t2 = fibo(n / 2 + 1);
		result = (2 * t2 - t1) % MAX;
		if (result < 0) result += MAX;
		result *= t1;
		result %= MAX;
	}
	else{
		t1 = fibo(n / 2);
		t2 = fibo(n / 2 + 1);
		result = (t2*t2) % MAX;
		result += (t1*t1) % MAX;
		result %= MAX;
	}

	if (n < LMT){
		F[n] = result;
	}

	return result;
}

long long int case_nums(int n){

	long long int result, t1, t2;

	if (n <= 0) return 0;
	else if (n == 1) return 2;
	else if (n == 2) return 4;

	t1 = (fibo(n - 2) * 2) % MAX;
	t2 = (fibo(n - 1) * 2) % MAX;
	result = (t2 + t2) % MAX;
	result += t1;
	result %= MAX;
	return result;
}

int main(){

	int n;

	scanf("%d", &n);
	printf("%d\n", case_nums(n));

	return 0;
}