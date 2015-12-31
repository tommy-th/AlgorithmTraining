#include <stdio.h>

int T, N, Q;
int cow[50001];
int result[200001];
int main(){

	int i, j, k, A, B, min = 100000, max = 0;

	T = 1;
	for (i = 0; i < T; i++){
		scanf("%d %d", &N, &Q);
		for (j = 1; j <= N; j++){
			scanf("%d", &cow[j]);
		}
		for (j = 0; j < Q; j++){
			scanf("%d %d", &A, &B);
			for (k = A; k <= B; k++){
				if (cow[k] < min) min = cow[k];
				if (cow[k] > max) max = cow[k];
			}
			result[j] = max - min;
			max = 0;
			min = 1000000;
		}
		for (j = 0; j < Q; j++){
			printf("%d\n", result[j]);
		}
	}
	return 0;
}