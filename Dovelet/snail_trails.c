#include <stdio.h>

int N;
int M[125][125];
int result;

int direct[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

void search_load(int y, int x, int idx, int sum){
	int tx = x, ty = y;

	while (M[ty][tx] == 0){
		M[ty][tx] = 1;
		tx += direct[idx][0];
		ty += direct[idx][1];
		sum++;
	}
	if (sum > result) result = sum;
	if (M[ty][tx] == 1) {
		tx -= direct[idx][0];
		ty -= direct[idx][1];
	}
	else{
		tx -= direct[idx][0];
		ty -= direct[idx][1];
		if (idx < 2){
			if (M[ty + 1][tx] == 0) search_load(ty + 1, tx, 2, sum);
			if (M[ty - 1][tx] == 0) search_load(ty - 1, tx, 3, sum);
		}
		else{
			if (M[ty][tx + 1] == 0) search_load(ty, tx + 1, 0, sum);
			if (M[ty][tx - 1] == 0) search_load(ty, tx - 1, 1, sum);
		}
	}
	while (tx != x || ty != y){
		M[ty][tx] = 0;
		tx -= direct[idx][0];
		ty -= direct[idx][1];	
	}
	M[ty][tx] = 0;
}

int main(){

	char c;
	int b, i, j, x, y;

	scanf("%d %d", &N, &b); 

	for (i = 0; i <= N + 1; i++){
		M[i][0] = -1;
		M[i][N + 1] = -1;
	}

	for (j = 0; j <= N + 1; j++){
		M[0][j] = -1;
		M[N + 1][j] = -1;
	}

	for (i = 0; i < b; i++){
		scanf("%c%c%d",&c, &c, &y);
		x = c - 64;
		M[y][x] = -1;
	}

	search_load(1, 1, 0, 0);
	search_load(1, 1, 2, 0);

	printf("%d\n", result);
	
	return 0;
}