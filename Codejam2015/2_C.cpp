#include <iostream>
#include <vector>
using namespace std;
#define MAX 4005

char words[MAX][15];
int W[MAX][MAX], H[MAX], P[MAX];
int X[205][15], xidx[205];
int N, T, widx;

bool search_node(int n){
	if (H[n]) return false;
	H[n] = 1;

	if (P[n] != -1){
		if (search_node(P[n])){
			P[n] = -1;
			return true;
		}
	}

	for (int i = 1; i <= W[n][0]; i++){
		int b = W[n][i];
		if (W[n][1] == 1) return true;
		if (P[b] == n) continue;
		if (search_node(P[b] == -1 ? b : P[b])){
			P[b] = n;
			return true;
		}
	}

	return false;
}

int search(){
	int cnt = 0;

	memset(P, -1, sizeof(P));
	memset(H, 0, sizeof(H));
	while (search_node(0)){
		memset(H, 0, sizeof(H));
		cnt++;
	}
	return cnt;
}

int main(){
	int cidx, pidx, j;
	char input[10005], temp[15];
	
	FILE *fin = freopen("C-large-practice.in", "r", stdin);
	FILE *fout = freopen("C-large-practice.out", "w", stdout);
	
	cin >> T;
	for (int t = 1; t <= T; t++){
		widx = 2;
		memset(W, 0, sizeof(W));
		memset(X, 0, sizeof(X));
		memset(xidx, 0, sizeof(xidx));

		cin >> N; gets(input);
		for (int i = 1; i <= N; i++){
			if (i >= 3) xidx[i - 2] = 1;
			gets(input);
			pidx = cidx = 0;
			while (1){
				if (input[cidx] == ' ' || input[cidx] == '\0'){ 
					temp[pidx] = '\0'; 
					pidx = 0;
					for (j = 1; j <= widx; j++){
						if (strcmp(words[j], temp) == 0 || j == widx){
							strcpy(words[j], temp);
							if (j == widx) widx++; 
							break;
						}
					}
					if (i == 1){
						W[0][0]++;
						W[0][W[0][0]] = j;
					}
					else if (i == 2){
						W[j][0]++;
						W[j][W[j][0]] = 1;
					}
					else {
						X[i - 2][xidx[i - 2]++] = j;
						for (int k = 1; k < xidx[i - 2]; k++){
							if (X[i - 2][k] != j){
								int tidx = 1;
								while (W[j][tidx] != X[i - 2][k]){
									if (W[j][tidx] == 0){
										W[j][tidx] = X[i - 2][k];
										W[j][0]++;
										break;
									}
									tidx++;
								}
								tidx = 1;
								while (W[X[i - 2][k]][tidx] != j){
									if (W[X[i - 2][k]][tidx] == 0){
										W[X[i - 2][k]][tidx] = j;
										W[X[i - 2][k]][0]++;
										break;
									}
									tidx++;
								}
							}
						}
					}
					if (input[cidx] == '\0') break;
				}
				else temp[pidx++] = input[cidx];
				cidx++;
			}
		}
		fprintf(stderr, "Case #%d DONE\n", t);
		cout << "Case #" << t << ": " << search() << endl;
	}

	return 0;
}