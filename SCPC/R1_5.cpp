#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int nodes[1005][1005], D[1005], P[1005], L[1005][1005], R[1005], H[1005];
int T, N, M, start;
int q[1005];

void searchNode(int n){
	int len, child;

	for (int i = 1; i <= nodes[n][0]; i++){
		child = nodes[n][i];
		len = L[child][n] + D[n];
		if ((len < D[child] || D[child] == 0) && child != start){
			if (H[child] == 0){
				H[child] = 1;
				q[0]++;
				q[q[0]] = child;
			}
			D[child] = len;
			P[child] = n;
		}
	}
}

void setNode(int n){
	int len, child;

	for (int i = 1; i <= nodes[n][0]; i++){
		child = nodes[n][i];
		len = L[child][n] + D[n];
		if (len == D[child] && child != start){
			if (H[child] == 0){
				H[child] = 1;
				q[0]++;
				q[q[0]] = child;
			}
			if (n != start) R[n] = 1;
		}
	}
}

void reset(){
	for (int i = 0; i <= N; i++) nodes[i][0] = 0;
	memset(R, 0, sizeof(R));
}

void print(){
	int result = 0;
	for (int i = 1; i <= N; i++){
		if (R[i] == 0) result++;
	}
	cout << result << " ";
	for (int i = 1; i <= N; i++){
		if (R[i] == 0) cout << i << " ";
	}
	cout << endl;
}

int main(){

	int list[1005];
	int len, a, b;

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> M;

		reset();
		for (int i = 1; i <= M; i++){
			cin >> a >> b >> len;
			L[a][b] = L[b][a] = len;
			nodes[a][0]++;
			nodes[b][0]++;
			nodes[a][nodes[a][0]] = b;
			nodes[b][nodes[b][0]] = a;
		}

		for (int i = 1; i <= N; i++){
			start = i;
			memset(D, 0, sizeof(D));
			memset(P, 0, sizeof(P));
			q[0] = 1;
			q[1] = i;
			while (q[0]){
				for (int j = 0; j <= q[0]; j++) list[j] = q[j];
				q[0] = 0;
				memset(H, 0, sizeof(H));
				for (int j = 1; j <= list[0]; j++){
					searchNode(list[j]);
				}
			}
			q[0] = 1;
			q[1] = i;
			while (q[0]){
				for (int j = 0; j <= q[0]; j++) list[j] = q[j];
				q[0] = 0;
				memset(H, 0, sizeof(H));
				for (int j = 1; j <= list[0]; j++){
					setNode(list[j]);
				}
			}
		}
		printf("Case #%d\n", t);
		print();
	}

	return 0;
}