#include <stdio.h>

int D[10001];
int begin, a, b, d, max, n, son;

void bern(){
	int i, temp;
	
	begin--; a--; b--; d--;
	if (begin < 0) begin = max;
	if (a < 0) a = max;
	if (b < 0) b = max;
	if (d < 0) d = max;

	D[d] = 0;
	son = (son + D[a] - D[b]) % 1000;
	if (son < 0) son += 1000;
	D[begin] = son;
}

int main(){

	int i, result = 0;

	scanf("%d %d %d %d", &a, &b, &d, &n);
	max = d;
	begin = 0;
	D[0] = 1;

	for (i = 0; i < n; i++)
		bern();

	for (i = 0; i <= max; i++)
		result += D[i];

	result %= 1000;

	printf("%d\n", result);

	return 0;
}