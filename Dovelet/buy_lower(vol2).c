#include <stdio.h>
#include <memory.h>

int N;
int stack[10000];
int stock[5005];
int D[5005][2];

void check(int n){
	int i, max = 0, count = 1;

	for (i = n-1; i > 0; i--){
		if (stock[i] > stock[n]){
			if (D[i][0] > max){
				max = D[i][0];
				count = D[i][1];
				memset(stack, 0, sizeof(stack));
				stack[stock[i]] = 1;
			}
			else if (max == D[i][0] && stack[stock[i]] == 0){
				stack[stock[i]] = 1;
				count += D[i][1];
			}
		}
	}
	D[n][0] = max + 1;
	D[n][1] = count;
}

int main(){

	int i;

	scanf("%d", &N);

	for (i = 1; i <= N; i++){
		scanf("%d", &stock[i]);
		check(i);
	}
	check(N + 1);
	printf("%d %d\n", D[N + 1][0] - 1, D[N + 1][1]);
	return 0;
}