#include <stdio.h>

int D[2][30001][4];
int n;
int cow[30001];
int cow2[30001];

void search(int idx, int* temp, int k){
	int i, u;
	if (idx > n) return;
	for (i = 1; i <= 3; i++) D[k][idx][i] = D[k][idx-1][i];
	if (temp[idx] > 1){
		D[k][idx][1] += 1;
	}
	if (temp[idx] > 2){
		D[k][idx][2] += 1;
	}
	if (temp[idx] < 2){
		u = D[k][idx - 1][2] + 1;
		if (D[k][idx][1] < u) u = D[k][idx][1];
		D[k][idx][2] = u;
	}
	if (temp[idx] < 3){
		u = D[k][idx-1][3] + 1;
		if (D[k][idx][2] < u) u = D[k][idx][2];
		if (D[k][idx][1] < u) u = D[k][idx][1];
		D[k][idx][3] = u;
	}

	search(idx + 1, temp, k); 
}

int main(){

	int i, j, result = 30000;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)	
		scanf("%d", &cow[i]);

	j = n;
	for (i = 1; i <= n; i++,j--){
		cow2[j] = cow[i];
	}

	search(1, cow, 0); 
	search(1, cow2, 1);
	
	for (i = 0; i <= 1; i++){
		for (j = 1; j <= 3; j++){
			if (D[i][n][j] < result)
				result = D[i][n][j];
		}
	}
	printf("%d\n", result);

	return 0;
}