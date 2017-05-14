#include <iostream>
using namespace std;

#define MAX 1000000007

int R, C, T;
long long int D[110][15][5];

void set(int n){

	if (n > R) return;

	for (int i = 1; i <= 5; i++){
		D[n + 2][i][3] += D[n][i][2];
		D[n + 1][i][2] += D[n][i][3];
	}

	// 1 = 1, 2 = 6, 3 = 4, 4 = 3 , 5 = 12
	if (C % 6 == 0){
		D[n + 2][2][2] += D[n][1][3];
		D[n + 2][2][2] += D[n][2][3] * 6;
		D[n + 2][5][2] += D[n][3][3] * 2;
		D[n + 2][2][2] += D[n][4][3] * 3;
	}
	if (C % 4 == 0){
		D[n + 3][3][2] += D[n][1][3];
		D[n + 3][5][2] += D[n][2][3] * 2;
		D[n + 3][3][2] += D[n][3][3] * 4;
		D[n + 3][5][2] += D[n][4][3];
	}
	if (C % 3 == 0){
		D[n + 2][4][2] += D[n][1][3];
		D[n + 2][2][2] += D[n][2][3] * 3;
		D[n + 2][5][2] += D[n][3][3];
		D[n + 2][4][2] += D[n][4][3] * 3;
	}
	if (C % 12 == 0){
		D[n + 2][5][2] += D[n][5][3] * 6;
		D[n + 3][5][2] += D[n][5][3] * 4;
		D[n + 2][5][2] += D[n][5][3] * 3;
	}

	for (int i = 1; i <= 5; i++){
		D[n + 2][i][2] %= MAX;
		D[n + 3][i][2] %= MAX;
	}
	
	set(n + 1);
}

int main(){
	
	FILE *fin = freopen("D-large-practice.in", "r", stdin);
	FILE *fout = freopen("D-large-practice.out", "w", stdout);
	
	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> R >> C;
		memset(D, 0, sizeof(D));
		D[0][1][2] = D[0][1][3] = 1;
		set(0);	
		for (int i = 1; i <= 5; i++){
			D[R][0][0] += D[R][i][2];
			D[R][0][0] += D[R][i][3];
			D[R][0][0] %= MAX;
		}
		cout << "Case #" << t << ": " << D[R][0][0] << endl;
		fprintf(stderr, "Case #%d %d\n", t, D[R][0][0]);
	}

	return 0;
}