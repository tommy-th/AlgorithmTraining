#include <stdio.h>

int N, W;
int D[1001][31];
int line[1001];

int main(){

	int i, j, max = 0;

	scanf("%d %d", &N, &W);

	for (i = 1; i <= N; i++){
		scanf("%d", &line[i]);
		D[i][0] = D[i - 1][0];
		if (line[i] == 1) D[i][0]++;
	}

	for (i = 1; i <= N; i++){
		for (j = 1; j <= W; j++){
			D[i][j] = D[i - 1][j] > D[i - 1][j - 1] ? D[i - 1][j] : D[i - 1][j - 1];
			if ((j % 2 + 1) == line[i])
				D[i][j]++;
		}
	}
	for (i = 1; i <= W; i++) if (max < D[N][i]) max = D[N][i];
	printf("%d\n", max);
}





//int N, W;
//int D[1001][3]; 
//int line[1001];
//int part[32];
//int result;
//
//int find_max(int a, int b){
//	int i, sum1 = 0, sum2 = 0;
//
//	sum1 = D[b][1] - D[a - 1][1];
//	sum2 = D[b][2] - D[a - 1][2];
//
//	if (sum1 > sum2) return sum1;
//	else return sum2;
//}
//
//void search(){
//	int j, i = W, temp = 0;
//
//	while (part[i] == N - W + i - 1 && i != 0) i--;
//	if (i == 0) return;
//	part[i]++;
//	for (j = i + 1; j <= W; j++) part[j] = part[j - 1] + 1;
//
//	temp += D[part[1]][1];
//	for (j = 1; j < W; j++){
//		temp += find_max(part[j] + 1, part[j + 1]);
//	}
//	temp += find_max(part[W]+1, N);
//	
//	if (temp > result) result = temp;
//	search();
//	return;
//}
//
//
//int main(){
//
//	int i, j, k, t, counter;
//
//	scanf("%d", &t); 
//
//	for (i = 0; i < t; i++){
//		scanf("%d %d", &N, &W);
//		for (j = 1; j <= W; j++){
//			part[j] = 0;
//		}
//		for (j = 1; j <= N; j++){
//			scanf("%d", &line[j]);
//			if (line[j] == 1){
//				D[j][1] = D[j - 1][1] + 1;
//				D[j][2] = D[j - 1][2];
//			}
//			else{
//				D[j][1] = D[j - 1][1];
//				D[j][2] = D[j - 1][2] + 1;
//			}
//		}
//
//		search();
//		printf("%d\n", result);
//		result = 0;
//	}
//}