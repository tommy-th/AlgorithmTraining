#include <stdio.h>

int count;
int desease[101];
int D[101][101];
int N;

void infaction(int n){
	int i=0;
	desease[n] = 1;
	while (i <= N){
		i++;
		if (desease[i] == 0 && D[n][i] == 1){
			infaction(i);
			count++;
		}
	}
}

int main(){
	
	int i, j, a, b, num;

	scanf("%d", &N);
	scanf("%d", &num);

	for (i = 1; i < num + 1; i++){
		scanf("%d %d", &a, &b);
		D[a][b] = 1;
		D[b][a] = 1;
	}

	infaction(1);
	
	printf("%d\n", count);

	return 0;
}