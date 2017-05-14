#include <stdio.h>

int D[5005][1000];
int stack[5005][1000];
int hash[5005][1000];
int Dm[5005][1000];
int N, stock[5005];
int len=1;

void set_table(){
	
	int i, j, idx;

	for (i = 1; i <= N; i++){
		for (j = 1; j <= i; j++){
			if ((stock[i] < D[i - 1][j - 1] || j == 1) && stock[i] > D[i - 1][j]){
				D[i][j] = stock[i];
				idx = ++stack[j][0];
				stack[j][idx] = stock[i];
				hash[j][idx] = i; 
			}
			else
				D[i][j] = D[i - 1][j];

			if (D[i][j] == 0) {
				if (j - 1 > len) len = j - 1;
				break;
			}
		}
	}
}

int search(int n, int idx){
	int i, result = 0;
	if (n == 1)	return 1;

	for (i = 1; i <= stack[n - 1][0]; i++){
		if (hash[n - 1][i] < hash[n][idx]){
			if (stack[n - 1][i] > stack[n][idx]){
				if (Dm[n - 1][i] == 0) Dm[n - 1][i] = search(n - 1, i);
				result += Dm[n - 1][i];
			}
		}
		else break;
	}
	return result;
}

int main(){

	int i, result;

	scanf("%d", &N);

	for (i = 1; i <= N; i++) scanf("%d", &stock[i]);
	set_table();
	hash[len + 1][0] = N + 1;
	result = search(len + 1, 0);
	printf("%d %d\n", len, result);

	return 0;
}