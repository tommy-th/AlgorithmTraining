#include <stdio.h>

int roop[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
int D[5][1005][1005];
int stack[2][100000];
char map[1005][1005];
int M[1005][1005];
int C, R, result, idx[2];

void set_map(){
	int i, j, k, cnt = 0;

	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (map[i][j] == '#') M[i][j] = 0;
			else{
				for (k = 0; k < 4; k++){
					if (map[i + roop[k][0]][j + roop[k][1]] == '.')
						cnt++;
				}

				M[i][j] = cnt;
				if (cnt == 1){
					D[0][i][j] = 1;
					stack[0][idx[0]++] = i * 10000 + j;
				}
				cnt = 0;
			}
		}
	}
}

void search_load(int x, int y, int z, int data){
	int x1, y1, j, k = 1, cnt = 0;
	int tx = x, ty = y, len = data, on = 1;

	M[y][x] = 0;

	while (on){
		on = 0;
		for (j = 0; j < 4; j++){
			x1 = tx + roop[j][1]; y1 = ty + roop[j][0];

			if (M[y1][x1] >= 3){
				while (D[k][y1][x1]) k++;
				D[k][y1][x1] = len;

				for (k = 0; k < 4; k++){
					if (M[y1 + roop[k][0]][x1 + roop[k][1]]) 
						cnt++;
				}

				if (cnt == 1){
					D[0][y1][x1] = 1;
					stack[z][idx[z]++] = y1 * 10000 + x1;
				}

				return;
			}
			else if (M[y1][x1] == 1){
				if (len + D[0][y1][x1] - 1 > result)
					result = len + D[0][y1][x1] - 1;
				return;
			}
			else if (M[y1][x1]){
				on = 1;
				tx = x1;
				ty = y1;
				M[ty][tx] = 0;
				len++;
			}
		}
	}
}

void search_result(){
	int i, j, x, y, k = 0, max1, max2;

	while (idx[k]){
		for (i = 0; i < idx[k]; i++){
			x = stack[k][i] % 10000;
			y = stack[k][i] / 10000;
			search_load(x, y, (k + 1) % 2, D[0][y][x]);
		}
		idx[k] = 0;
		k = (k + 1) % 2;
		for (i = 0; i < idx[k]; i++){
			x = stack[k][i] % 10000;
			y = stack[k][i] / 10000;
			M[y][x] = 1;

			max1 = max2 = 0;
			for (j = 1; j <= 4; j++){
				if (D[j][y][x] > max1){
					max2 = max1;
					max1 = D[j][y][x];
				}
				else if (D[j][y][x] > max2) max2 = D[j][y][x];
			}
			if (max1 + max2 > result) result = max1 + max2;
			D[0][y][x] += max1;
		}
	}
}

int main(){

	int i, j;
	char chr;
	scanf("%d %d", &C, &R);

	for (i = 1; i <= R; i++){
		scanf("%s", &map[i][1]);
	}

	set_map();
	search_result();

	printf("Maximum rope length is %d.\n", result);

	return 0;
}