#include <stdio.h>

int people[201];
long long D[201][201][201];

long long case_num(int candy, int num, int max){
	int i, k1, k2;
	long long sum = 0;
	double limit = (double)(candy - (double)candy / num);

	if (candy <= 1 || num == 1)
		return 1;
	if (candy <= max) 
		i = 0;
	else 
		i = candy - max;
	for (; i <= (int)limit; i++){
		k1 = num-1;
		k2 = candy - i;
		if (k1 >= candy) k1 = 0;
		if (k2 >= candy) k2 = 0;
		if (D[i][k1][k2] == 0) D[i][k1][k2] = case_num(i, num - 1, candy - i);
		sum += D[i][k1][k2];
	}
	return sum;
}

int main(){

	int n, k;
	scanf("%d %d", &n, &k);

	printf("%lld", case_num(n-k, k, n-k));

	return 0;
}