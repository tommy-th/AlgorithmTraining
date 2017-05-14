#include <stdio.h>

int W, H;
int map[105][105];
int D[105][105][210];
int dir[2][4] = {
		{ 0, -1, 0, -1 },
		{ 0, -1, -1, 0 }
};

void step(int n){
	int i, x, y, c = 0;

	if (n > W){
		x = W;
		y = 1 + n - W;
	}
	else{
		x = n; y = 1;
	}
	while (x >= 1 && y <= H){
		if (map[y][x]){
			while (x - c >= 1 && y + c <= H){
				if (map[y + c][x - c]){
					if (D[y - 1][x][c] > D[y][x][c]) D[y][x][c] = D[y - 1][x][c];
					if (D[y - 1][x][c + 1] > D[y][x][c]) D[y][x][c] = D[y - 1][x][c + 1];
					if (D[y][x - 1][c] > D[y][x][c]) D[y][x][c] = D[y][x - 1][c];
					if (D[y][x - 1][c - 1] > D[y][x][c]) D[y][x][c] = D[y][x - 1][c - 1];
					if (map[y + c][x - c] == 1 && c != 0) D[y][x][c]++;
				}
				if (map[y][x] == 1) D[y][x][c]++;
				c++;
			}
		}
		x--; y++; c = 0;
	}
}

void set_table(){
	int i;

	for (i = 1; i <= W + H - 1; i++)
		step(i);
}

int main(){

	char input[105];
	int i, j;

	scanf("%d %d", &W, &H);
	for (i = 1; i <= H; i++){
		scanf("%s", &input);
		for (j = 0; j < W; j++){
			if (input[j] == '*') map[i][j + 1] = 1;
			else if (input[j] == '.') map[i][j + 1] = 2;
			else map[i][j + 1] = 0;
		}
	}
	set_table();
	printf("%d\n", D[H][W][0]);

	return 0;
}