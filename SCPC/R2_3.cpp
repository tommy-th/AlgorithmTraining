#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL long long
#define MOD 1000000007
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int T, N, M, K;
int map[105][105], water[105][105], D[105][105][15];
int loop[2][2] = { { 1, 0 }, { 0, 1 } };

void step(){
	int dif, a, b, next;

	D[0][0][water[0][0]] = 0;

	for (int i = 0; i <= N; i++){
		for (int j = 0; j <= M; j++){
			for (int k = 0; k <= K; k++){
				if (D[i][j][k] < 0) continue;
				for (int idx = 0; idx <= 1; idx++){
					a = i + loop[idx][0];
					b = j + loop[idx][1];

					dif = MAX(map[i][j], map[a][b]) - MIN(map[i][j], map[a][b]);

					next = k + water[a][b];
					if (next > K) next = K;

					if (D[i][j][k] + dif < D[a][b][next] || D[a][b][next] < 0)
						D[a][b][next] = D[i][j][k] + dif;
				}
			}
		}
	}

}

int main(){

	int input;
	cin >> T;

	for (int t = 1; t <= T; t++){
		cin >> M >> N >> K;

		for (int i = 0; i <= N; i++){
			for (int j = 0; j <= M; j++){
				for (int k = 0; k <= K; k++){
					D[i][j][k] = -1;
				}
			}
		}

		for (int i = 0; i <= N; i++){
			for (int j = 0; j <= M; j++){
				cin >> input;
				if (input < 0){
					map[i][j] = -1 * input;
					water[i][j] = 1;
				}
				else{
					map[i][j] = input;
					water[i][j] = 0;
				}
			}
		}
		step();

		printf("Case #%d\n", t);
		cout << D[N][M][K] << endl;
	}

	return 0;
}