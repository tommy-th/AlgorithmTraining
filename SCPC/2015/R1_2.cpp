#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int nextDir[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } };
int changeDir[3][4] = { {}, { 1, 0, 3, 2 }, { 3, 2, 1, 0 } };
int map[1005][1005], H[1005][1005];
int T, N, result;

int onField(int y, int x){
	if (x > N || x < 1 || y > N || y < 1) return 0;
	return 1;
}

void shootLazer(){
	int x, y, dir = 3;

	x = y = 1;
	while (onField(y, x)){
		if (map[y][x]){
			if (H[y][x] == 0){
				H[y][x] = 1;
				result++;
			}
			dir = changeDir[map[y][x]][dir];
		}
		y += nextDir[dir][0];
		x += nextDir[dir][1];
	}
}

int main(){
	char input[1005];

	cin >> T;
	for (int t = 1; t <= T; t++){
		result = 0;
		memset(H, 0, sizeof(H));
		cin >> N;
		for (int i = 1; i <= N; i++){
			cin >> &input[1];
			for (int j = 1; j <= N; j++) map[i][j] = input[j] - 48;
		}
		shootLazer();
		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}