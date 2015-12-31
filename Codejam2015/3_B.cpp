#include <iostream>
#include <cmath>
using namespace std;

int S[1005], A[1005], D[105][3];
int T, N, K;

int main(){
	
	FILE *fin = freopen("B-large-practice.in", "r", stdin);
	FILE *fout = freopen("B-large-practice.out", "w", stdout);
	
	int cur, res, midx, max;
	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> K;

		memset(A, 0, sizeof(A));
		memset(D, 0, sizeof(D));
		for (int i = 1; i <= N - K + 1; i++) cin >> S[i];

		for (int i = K + 1; i <= N; i++){
			A[i] = S[i - K + 1] - S[i - K];
			if (i > K * 2) A[i] += A[i - K];
		}
		max = 0; midx = 1;
		for (int i = K + 1; i <= N; i++){
			cur = i % K;
			if (cur == 0) cur = K;
			if (A[i] < D[cur][1]) D[cur][1] = A[i];
			if (A[i] > D[cur][2]) D[cur][2] = A[i];
			if (abs(D[cur][2] - D[cur][1]) > max){
				max = abs(D[cur][2] - D[cur][1]);
				midx = cur;
			}
		}
		res = S[1] % K;
		int pos = 0, nev = 0, num = 0;

		for (int i = 1; i <= K; i++){
			if (D[i][2] > D[midx][2]){
				D[i][0] = D[midx][2] - D[i][2];
				res += D[i][2] - D[midx][2];
			}
			else if (D[i][1] < D[midx][1]){
				D[i][0] = D[midx][1] - D[i][1];
				res += D[i][1] - D[midx][1];
			}
			if (D[i][0] + D[i][2] < D[midx][2]) pos += D[midx][2] - D[i][0] - D[i][2];
			if (D[i][0] + D[i][1] > D[midx][1]) nev += D[i][0] + D[i][1] - D[midx][1];
			if (abs(D[i][2] - D[i][1]) == max) num++;
		}
		if (res > 0) { res += nev; pos += nev; }
		else if (res < 0){ res -= pos; nev += pos; }
		res %= K;
		if (res > pos) max++;	
		else if (res < 0 && abs(res) > nev) max++;

		cout << "Case #" << t << ": " << max << endl;
		fprintf(stderr, "Case #%d: %d\n", t, max);
	}

	return 0;
}