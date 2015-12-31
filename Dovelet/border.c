#include <stdio.h>

int L, N, D;
int tower[1000005];
int cost[1000005];
int T[1000005];
int C[1000005];

int sub_cost(int n){
	int min, idx = n - 1, cidx = n - 1;

	if (tower[n] - tower[idx] > 2 * D) return -1;

	min = T[idx];
	while (tower[n] - tower[idx] <= 2 * D){
		if (min > T[idx]){
			min = T[idx];
			cidx = idx;
		}
		idx--;
		if (idx < 0)
			break;
	}
	C[n] = C[cidx] + 1;
	return cost[n] + min;
}

void set_table(){

	int i, idx = N, min, num;

	if (L <= 2 * D) {
		printf("0 0\n");
		return;
	}

	for (i = 1; i <= N; i++){
		T[i] = sub_cost(i);
		if (T[i] == -1) {
			printf("0\n");
			return;
		}
	}

	min = T[N]; num = C[N];
	while (L - tower[idx] <= 2 * D){
		if (min > T[idx]){
			min = T[idx];
			num = C[idx];
		}
		idx--;
	}

	printf("%d %d\n", min, num);
}

int main(){

	int i, x, c;

	scanf("%d %d %d", &L, &N, &D);

	for (i = 1; i <= N; i++){
		scanf("%d %d", &x, &c);
		tower[i] = x;
		cost[i] = c;
	}
	set_table();

	return 0;
}