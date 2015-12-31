#include <iostream>
using namespace std;
#define MAX 105

int map[MAX][MAX];
int N, T ,R, C, result;

int check(int y, int x){
	int on = 0, ret = 0;

	for (int i = 1; i < y; i++){
		if (map[i][x]){
			if (map[y][x] == 1) on = 1;
			ret++;
		}
	}
	for (int i = y + 1; i <= R; i++){
		if (map[i][x]){
			if (map[y][x] == 3) on = 1;
			ret++;
		}
	}
	for (int j = 1; j < x; j++){
		if (map[y][j]){
			if (map[y][x] == 4) on = 1;
			ret++;
		}
	}
	for (int j = x + 1; j <= C; j++){
		if (map[y][j]){
			if (map[y][x] == 2) on = 1;
			ret++;
		}
	}
	if (on) return 0;
	else if (ret) return 1;
	else return -1000000;
}

int main(){

	char input[MAX];
	
	FILE *fin = freopen("A-large-practice.in", "r", stdin);
	FILE *fout = freopen("A-large-practice.out", "w", stdout);
	

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> R >> C;
		result = 0;
		for (int i = 1; i <= R; i++){
			cin >> &input[1];
			for (int j = 1; j <= C; j++){
				if (input[j] == '^') map[i][j] = 1;
				else if (input[j] == '>') map[i][j] = 2;
				else if (input[j] == 'v') map[i][j] = 3;
				else if (input[j] == '<') map[i][j] = 4;
				else map[i][j] = 0;
			}
		}
		for (int i = 1; i <= R; i++){
			for (int j = 1; j <= C; j++){
				if (map[i][j]) result += check(i, j);
				if (result < 0) break;
			}
			if (result < 0) break;
		}
		cout << "Case #" << t << ": ";
		if (result >= 0) cout << result << endl;
		else cout << "IMPOSSIBLE" << endl;
	}


	return 0;
}