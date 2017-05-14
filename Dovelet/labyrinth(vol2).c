#include <stdio.h>

int roop[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
char map[1005][1005];
int M[1005][1005];
int C, R, result;

void set_map();
int search_load(int x, int y);
int search_point(int x, int y, int idx);
void search_result();

int search_load(int x, int y){
	int j, tx = x, ty = y, len = 1, on = 1;

	M[y][x] = 0;

	while (on){
		on = 0;
		for (j = 0; j < 4; j++){
			if (M[ty + roop[j][0]][tx + roop[j][1]] == 3){
				len += search_point(tx + roop[j][1], ty + roop[j][0], 0);
				break;
			}
			else if (M[ty + roop[j][0]][tx + roop[j][1]]){
				tx = tx + roop[j][1];
				ty = ty + roop[j][0];
				M[ty][tx] = 0;
				on = 1;
				len++;
			}
		}
	}
	return len;
}

int search_point(int x, int y, int idx){
	int len[4] = { 0, 0, 0, 0 };
	int i = 0, j, max1 = 0, max2 = 0;

	M[y][x] = 0;

	for (j = 0; j < 4; j++){
		if (M[y + roop[j][0]][x + roop[j][1]])
			len[i++] = search_load(x + roop[j][1], y + roop[j][0]);
	}

	for (j = 0; j < i; j++){
		if (len[j] > max1){
			max2 = max1;
			max1 = len[j];
		}
		else if (len[j] > max2) max2 = len[j];
	}

	if (idx) return max1 + max2;
	else return max1 + 1;
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

void search_result(){
	int i, j, temp;

	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (M[i][j] == 3){
				temp = search_point(j, i, 1);
				if (temp > result) result = temp;
			}
		}
	}
	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (M[i][j] == 1){
				temp = search_load(j, i);
				if (temp - 1 > result) result = temp - 1;
			}
		}
	}
}

void set_map(){
	int i, j, k, cnt = 0;

	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (map[i][j] == '#') M[i][j] = 0;
			else{
				for (k = 0; k < 4; k++)
					if (map[i + roop[k][0]][j + roop[k][1]] == '.') cnt++;

				if (cnt == 1) M[i][j] = 1;
				else if (cnt == 2) M[i][j] = 2;
				else M[i][j] = 3;
				cnt = 0;
			}
		}
	}
}