#include<stdio.h>
#define Max_n 100

int N, M, Max;

int Map[Max_n + 1][Max_n + 1], V[Max_n + 1][Max_n + 1], D[Max_n * 2][Max_n + 1][Max_n + 1];

void recall(int step, int x1, int x2, int cnt)
{
	int dir[4][4] = {
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 0 },
		{ 1, 0, 0, 1 },
		{ 1, 0, 1, 0 }
	};
	int i, y1, y2, value;

	if (x1>x2) return;

	if (step == N + M - 2){
		if (Max<cnt) Max = cnt;
		return;
	}

	y1 = step - x1 + 2;
	y2 = step - x2 + 2;

	for (i = 0; i<4; i++){
		if (y1 + dir[i][0] <= N && x1 + dir[i][1] <= M && y2 + dir[i][2] <= N && x2 + dir[i][3] <= M){
			value = 0;
			if (Map[y1 + dir[i][0]][x1 + dir[i][1]] == 1 && V[y1 + dir[i][0]][x1 + dir[i][1]] == 0) value++;
			if (!(y1 + dir[i][0] == y2 + dir[i][2] && x1 + dir[i][1] == x2 + dir[i][3])
				&& Map[y2 + dir[i][2]][x2 + dir[i][3]] == 1 && V[y2 + dir[i][2]][x2 + dir[i][3]] == 0) value++;

			if (Map[y1 + dir[i][0]][x1 + dir[i][1]] != -1 && Map[y2 + dir[i][2]][x2 + dir[i][3]] != -1){
				if (D[step + 1][x1 + dir[i][1]][x2 + dir[i][3]]<cnt + value){
					D[step + 1][x1 + dir[i][1]][x2 + dir[i][3]] = cnt + value;
					V[y1 + dir[i][0]][x1 + dir[i][1]]++;
					V[y2 + dir[i][2]][x2 + dir[i][3]]++;
					recall(step + 1, x1 + dir[i][1], x2 + dir[i][3], cnt + value);
					V[y1 + dir[i][0]][x1 + dir[i][1]]--;
					V[y2 + dir[i][2]][x2 + dir[i][3]]--;
				}
			}
		}
	}
}

int main()
{
	char str[Max_n + 5];
	int i, j;

	scanf("%d%d", &M, &N);

	for (i = 1; i <= N; i++){
		scanf("%s", &str[1]);
		for (j = 1; j <= M; j++){
			if (str[j] == '*') Map[i][j] = 1;
			else if (str[j] == '#') Map[i][j] = -1;
		}
	}

	V[1][1] = 2;
	D[0][1][1] = 1;
	if (Map[1][1] == 1) D[0][1][1]++;
	recall(0, 1, 1, D[0][1][1]);
	printf("%d", Max - 1);

	return 0;
}