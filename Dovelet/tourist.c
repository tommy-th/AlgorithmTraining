/*
	문제: Dovelet 21단계 tourist
	날짜: 2014-04-22
	실행시간: 0.28s
*/

#include <stdio.h>

int w, h;
int s[105][105];
int D[210][105][105];
int dir[2][4] = {
	{ 0, -1, 0, -1 },
	{ 0, -1, -1, 0 }
};

// 동적계획법
void D_set(){

	int x1, x2, y1, y2, i, j, step;
	step = w + h - 2;

	for (i = 1; i < step + 1; i++){
		x1 = i + 1;
		if (x1>w){ x1 = w; }
		y1 = i - x1 + 2;

		while (x1 > 0 && y1 <= h){

			if (s[y1][x1] != -1){
				x2 = x1;
				y2 = y1;

				while (x2 > 0 && y2 <= h){
					// 최대값 구하기
					if (s[y2][x2] != -1){
						for (j = 0; j < 4; j++){
							if (D[i - 1][x1 + dir[0][j]][x2 + dir[1][j]]>D[i][x1][x2])
								D[i][x1][x2] = D[i - 1][x1 + dir[0][j]][x2 + dir[1][j]];
						}
						if (s[y1][x1] == 1)
							D[i][x1][x2]++;
						if (s[y2][x2] == 1 && x1 != x2)
							D[i][x1][x2]++;
					}
					x2--; y2++;
				}
			}
			x1--; y1++;
		}
	}

}

int main(){

	char ct[103];
	int i, j;

	scanf("%d %d", &w, &h);

	//입력부
	for (i = 1; i < h + 1; i++){
		scanf("%s", &ct[1]);
		for (j = 1; j < w + 1; j++){
			if (ct[j] == '*')
				s[i][j] = 1;
			else if (ct[j] == '#')
				s[i][j] = -1;
		}
	}
	if (s[1][1] == 1)
		D[0][1][1] = 1;

	D_set();

	printf("%d", D[w + h - 2][w][w]);

}