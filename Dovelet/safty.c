#include <stdio.h>

int map[101][101];
int temp[101][101];
int N, max, result;

void find(int y, int x){
	if (temp[y][x] == 0) return;
	temp[y][x] = 0;
	if (temp[y - 1][x] == 1)find(y - 1, x);
	if (temp[y][x - 1] == 1)find(y, x - 1);
	if (temp[y][x + 1] == 1)find(y, x + 1);
	if (temp[y + 1][x] == 1)find(y + 1, x);
}

void copy(int height){
	int i, j;

	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			if (map[i][j] > height) temp[i][j] = 1;
			else temp[i][j] = 0;
		}
	}
}

int search(int height){
	int i, j, on = 1, count = 0;

	copy(height);
	while (on){
		on = 0;
		for (i = 1; i <= N; i++){
			for (j = 1; j <= N; j++){
				if (temp[i][j]){
					find(i, j);
					count++;
					on = 1;
				}
			}
		}
	}
	return count;
}

int main(){

	int i, j;

	scanf("%d", &N);
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			scanf("%d", &map[i][j]);
			if (map[i][j] > max) max = map[i][j];
		}
	}

	for (i = 0; i < max; i++){
		if (search(i)>result)result = search(i);
	}

	printf("%d\n", result);
	
	return 0;
}