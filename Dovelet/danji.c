#include <stdio.h>

static int N;
static int IDX;
static int sum[1000];
static int D[26][26];
static int map[26][26];

void quicksort(int* a, int low, int high){
	int i = low, j = high, h;
	int x = a[(low + high) / 2];
	do{
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j){
			h = a[i]; a[i] = a[j]; a[j] = h;
			i++; j--;
		}
	} while (i <= j);

	if (low < j) quicksort(a, low, j);
	if (i < high)quicksort(a, i, high);
}

int group(int y, int x){
	if (map[y - 1][x] == 1 && D[y - 1][x] == 0){
		sum[IDX]++;
		D[y - 1][x] = IDX;
		group(y - 1, x);
	}
	if (map[y][x - 1] == 1 && D[y][x - 1] == 0){
		sum[IDX]++;
		D[y][x - 1] = IDX;
		group(y, x - 1);
	}
	if (map[y][x + 1] == 1 && D[y][x + 1] == 0){
		sum[IDX]++;
		D[y][x + 1] = IDX;
		group(y, x + 1);
	}
	if (map[y + 1][x] == 1 && D[y + 1][x] == 0){
		sum[IDX]++;
		D[y + 1][x] = IDX;
		group(y + 1, x);
	}
}

int main(){
	int i,j;
	IDX = 1;
	scanf("%d", &N);

	for (i = 1; i < N + 1; i++){
		for (j = 1; j < N + 1; j++){
			scanf("%d", &map[i][j]);
		}
	}

	for (i = 1; i < N + 1; i++){
		for (j = 1; j < N + 1; j++){
			if (map[i][j]==1 && D[i][j]==0){
				D[i][j] = IDX;
				group(i, j);
				IDX++;
			}
		}
	}

	quicksort(sum, 1, IDX - 1);
	printf("%d\n", IDX - 1);

	for (i = 1; i < IDX; i++){
		printf("%d\n", sum[i] + 1);
	}

	return 0;
}