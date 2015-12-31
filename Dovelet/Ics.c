#include <stdio.h>

int x_len, y_len;
int X[1005], Y[1005];
int D[1005][1005];

void setdp(){

	int i, j;

	for (i = 1; i <= y_len; i++){
		for (j = 1; j <= x_len; j++){
			if (Y[i] == X[j]){
				D[i][j] = D[i - 1][j - 1] + 1;
			}
			else{
				if (D[i - 1][j] > D[i][j - 1]) D[i][j] = D[i - 1][j];
				else D[i][j] = D[i][j - 1];
			}
		}
	}
}

void print_result(){
	int k = 0, stack[1005];
	int i = y_len, j = x_len, c = D[y_len][x_len];

	printf("%d\n", D[y_len][x_len]);

	while (c){
		while (D[i][j] == D[i - 1][j - 1]){
			i--; j--;
		}
		while (D[i][j] == D[i - 1][j]) i--;
		while (X[j] != Y[i]) j--;
		stack[k++] = X[j];
		i--; j--; c--;
	}

	for (i = k - 1; i >= 0; i--){
		printf("%d ", stack[i]);
	}

	printf("\n");
}

int main(){

	int i;

	scanf("%d %d", &x_len, &y_len);

	for (i = 1; i <= x_len; i++){
		scanf("%d", &X[i]);
	}
	for (i = 1; i <= y_len; i++){
		scanf("%d", &Y[i]);
	}

	setdp();
	print_result();

	return 0;
}