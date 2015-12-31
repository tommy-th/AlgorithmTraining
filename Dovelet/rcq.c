#include <stdio.h>

int N;
int D[100005][205];
int T[205];

int main(){

	int i, j, a, b, q, data, count = 0;

	scanf("%d", &N);
	for (i = 1; i <= N; i++){
		scanf("%d", &data);
		for (j = 0; j <= 200; j++)
			D[i][j] = D[i - 1][j];
		D[i][data+100]++;
	}

	scanf("%d", &q);

	for (i = 1; i <= q; i++){
		scanf("%d %d", &a, &b);
		for (j = 0; j <= 200; j++)
			T[j] = D[b][j] - D[a - 1][j];

		count = 0; j = 0;
		while (count < (b - a) / 2 + 1)
			count += T[j++];
		
		printf("%d\n", j-101);

	}

	return 0;
}