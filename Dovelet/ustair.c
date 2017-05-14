#include <stdio.h>

int N;
int stair[301];
int D[301][3];

void upup(int n, int step, int pre){
	
	if (D[n][step] == 0 || D[n][step] < pre + stair[n])
		D[n][step] = pre + stair[n];
	else return;

	if (n < N){
		if (step < 2) 
			upup(n + 1, 2, D[n][step]);
		upup(n + 2, 1, D[n][step]);
	}
}

int main(){

	int i, result;
	
	scanf("%d", &N);
	
	for (i = 1; i <= N; i++){
		scanf("%d", &stair[i]);
	}

	upup(1, 1, 0);
	upup(2, 1, 0);

	if (D[N][1] > D[N][2])
		result = D[N][1];
	else
		result = D[N][2];

	printf("%d\n", result);

	return 0;
}