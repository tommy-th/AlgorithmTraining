#include <iostream>
#include <memory>
using namespace std;

int R, C, N, S, X, Y, T, B, result;
int map[10005][10005], dir[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int main(){
	
	FILE *fin = freopen("B-large-practice.in", "r", stdin);
	FILE *fout = freopen("B-large-practice.out", "w", stdout);
	
	int t;

	cin >> t;
	for (int k = 1; k <= t; k++){
		cin >> R >> C >> N;

		memset(map, 0, sizeof(map));
		S = 0;
		B = R*C - N;
		while (N){
			T = 10;
			for (int i = 1; i <= R; i++){
				for (int j = 1; j <= C; j++){
					if (map[i][j] < T){
						T = map[i][j]; 
						X = j; Y = i;
					}
					if (T == 0) break;
				}
				if (T == 0) break;
			}
			S += T;
			map[Y][X] = 10;
			for (int i = 0; i < 4; i++){
				map[Y + dir[i][0]][X + dir[i][1]]++;
			}
			N--;
		}
		result = S;

		for (int i = 1; i <= R; i++){
			for (int j = 1; j <= C; j++){
				map[i][j] = 4;
				if (i == 1) map[i][j]--;
				if (j == 1) map[i][j]--;
				if (i == R) map[i][j]--;
				if (j == C) map[i][j]--;
			}
		}
		S = 2*R*C - R - C;
		while (B){
			T = 0;
			for (int i = 1; i <= R; i++){
				for (int j = 1; j <= C; j++){
					if (map[i][j] > T){
						T = map[i][j];
						X = j; Y = i;
					}
					if (T == 4) break;
				}
				if (T == 4) break;
			}
			S -= T;
			map[Y][X] = 0;
			for (int i = 0; i < 4; i++){
				if (map[Y + dir[i][0]][X + dir[i][1]]) map[Y + dir[i][0]][X + dir[i][1]]--;
			}
			B--;
		}

		if (result > S) result = S;
		cout << "Case #" << k << ": " << result << endl;
		fprintf(stderr, "Case #%d: %d\n", k, S);
	}

	return 0;
}