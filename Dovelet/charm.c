#include <stdio.h>

int N, M;
int D[13000];

int main(){

	int i, j, wi, di, max = 0;

	scanf("%d %d", &N, &M);

	for (i = 1; i < N + 1; i++){
		scanf("%d %d", &wi, &di); 
		for (j = M-wi; j > 0; j--){
			if (D[j] + di > D[j + wi] && D[j]>0 ) D[j + wi] = D[j] + di; 
		}
		if (di > D[wi]) D[wi] = di;
	}
	for (i = 1; i < M + 1; i++) if (D[i] > max) max = D[i];

	printf("%d", max);

	return 0;
}