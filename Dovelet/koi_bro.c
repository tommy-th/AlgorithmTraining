#include <stdio.h>

int N;
int all;
int half, idx;
int rice[21][22];
int part[21][22];
int D[21][22][40000];
int history[22];
int result;

void path(int y, int x, int sum){
	if (x != 1 && D[y][x - 1][sum - part[y][x]] == 1){
		history[idx--] = N - y + 1;
		path(y, x - 1, sum - part[y][x]);
	}
	else if (y != N && D[y + 1][x][sum - rice[y][x]] == 1){
		path(y + 1, x, sum - rice[y][x]);
	}
}

void divide(int y, int x, int sum){
	D[y][x][sum] = 1;
	if (y != 1 && D[y - 1][x][sum + rice[y - 1][x]] == 0){
		divide(y - 1, x, sum + rice[y - 1][x]);
	}
	if (x != N + 1 && D[y][x + 1][sum + part[y][x + 1]] == 0){
		divide(y, x + 1, sum + part[y][x + 1]);
	}
}

int main(){

	int i, j;

	scanf("%d", &N);
	for (i = 1; i < N + 1; i++){
		for (j = 1; j < N + 1; j++){
			scanf("%d", &rice[i][j]);
			all += rice[i][j];
		}
	}

	result = all;
	idx = N;

	for (i = 1; i < N + 1; i++){
		part[N][i] = rice[N][i];
		for (j = 1; j < N; j++){
			part[N - j][i] = part[N - j + 1][i] + rice[N - j][i];
		}
	}

	for (i = 1; i < N + 1; i++)
		divide(N, i, rice[N][i]);

	for (i = (all + result) / 2; i >(all - result) / 2; i--){
		if (D[1][N + 1][i] == 1){
			half = i;
			if (2 * i - all>0){
				result = 2 * i - all;
			}
			else{
				result = all - 2 * i;
			}
		}
	}

	printf("%d\n", result);

	path(1, N + 1, half);

	for (i = 1; i < N + 1; i++){
		printf("%d ", history[i]);
	}

	return 0;
}