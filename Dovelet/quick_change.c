#include <stdio.h>

int main(){

	int cents, q, d, n, p;

	scanf("%d", &cents);

	q = cents / 25;
	cents -= q * 25;
	d = cents / 10;
	cents -= d * 10;
	n = cents / 5;
	cents -= 5 * n;
	p = cents;

	printf("%d QUARTER(S), %d DIME(S), %d NICKEL(S), %d PENNY(S)\n", q, d, n, p);

	return 0;
}