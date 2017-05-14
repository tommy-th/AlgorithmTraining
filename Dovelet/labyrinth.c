#include <stdio.h>

char map[1002][1002];
char edgeMap[1002][1002];
int MAX;
int C, R;

int find_edge(int y, int x){
	int cnt = 0;
	if (map[y][x] == '#') return -1;
	if (map[y - 1][x] == '.') cnt++;
	if (map[y + 1][x] == '.') cnt++;
	if (map[y][x + 1] == '.') cnt++;
	if (map[y][x - 1] == '.') cnt++;
	if (cnt < 2) return 1;
	else return 0;
}

void search_edge(){
	int i, j;
	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (find_edge(i, j) == 1)
				edgeMap[i][j] = 1;
		}
	}
}

void search_map(int y, int x, int cnt, int direct){
	if (cnt > MAX)MAX = cnt;
	if (map[y - 1][x] == '.' && direct != 1) search_map(y - 1, x, cnt + 1, 2);
	if (map[y + 1][x] == '.' && direct != 2) search_map(y + 1, x, cnt + 1, 1);
	if (map[y][x + 1] == '.' && direct != 3) search_map(y, x + 1, cnt + 1, 4);
	if (map[y][x - 1] == '.' && direct != 4) search_map(y, x - 1, cnt + 1, 3);
}

int main(){
	int i, j;

	scanf("%d %d", &C, &R);

	for (i = 1; i <= R; i++){
		scanf("%s", &map[i][1]);	
	}

	search_edge();

	for (i = 1; i <= R; i++){
		for (j = 1; j <= C; j++){
			if (edgeMap[i][j]==1)
				search_map(i, j, 1, 0);
		}
	}

	printf("Maximum rope length is %d.\n", MAX - 1);

	return 0;
}