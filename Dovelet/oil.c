#include <stdio.h>
#define max_arr_num 10000000

typedef struct __INFO{
	int value;
	int x;
	int y;
}INFO;

int gnd[1501][1501];
int subsum[1501][1501]; 
int K, N, M;
int result;
INFO sum_arr[max_arr_num+1];
int count;

void partial_sum(){
	int i, j, u;
	
	// 첫 부분합
	for (i = 1; i <= K; i++){
		for (j = 1; j <= K; j++){
			subsum[K][K] += gnd[i][j];
		}
	}
	// 윗 줄 부분합
	for (j = K + 1; j <= M; j++){
		subsum[K][j] = subsum[K][j - 1];
		for (u = 1;  u <= K; u++){
			subsum[K][j] -= gnd[u][j - K];
			subsum[K][j] += gnd[u][j];
		}
	}
	// 나머지 부분합
	for (i = K + 1; i <= M; i++){
		for (j = K; j <= N; j++){
			subsum[i][j] = subsum[i - 1][j];
			for (u = 1; u <= K; u++){
				subsum[i][j] -= gnd[i - K][j - K + u];
				subsum[i][j] += gnd[i][j - K + u]; 
			}
		}
	}
}

void sort_max(){
	int i, j, u, limit = count;
	int x, y, max = 0;
	if (limit > max_arr_num)limit = max_arr_num;
	
	for (u = 1; u <= limit; u++){
		for (i = K; i <= M; i++){
			for (j = K; j <= N; j++){
				if (subsum[i][j] > max){
					max = subsum[i][j];
					x = j; y = i;
				}
			}
		}
		sum_arr[u].value = max;
		sum_arr[u].x = x;
		sum_arr[u].y = y;
		subsum[y][x] = 0;
		max = 0;
	}
}

int match(int id1, int id2){
	int on = 1;
	if (sum_arr[id1].x < sum_arr[id2].x + K && sum_arr[id1].x > sum_arr[id2].x - K){
		if (sum_arr[id1].y < sum_arr[id2].y + K && sum_arr[id1].y > sum_arr[id2].y - K){
			on = 0;
		}
	}
	return on;
}

void find_max(){
	int i, j, u, temp = 0, limit = count;
	if (limit > max_arr_num) limit = max_arr_num;

	for (i = 1; i <= limit; i++){
		for (j = i+1; j <= limit; j++){
			for (u = j+1; u <= limit; u++){
				if (match(i, j) && match(j, u) && match(i, u)){
					temp = sum_arr[i].value + sum_arr[j].value + sum_arr[u].value;
					if (temp>result) result = temp; 
				}
			}
		}
	}
}


int main(){

	int i, j;

	scanf("%d %d %d", &M, &N, &K);

	for (i = 1; i <= M; i++){
		for (j = 1; j <= N; j++){
			scanf("%d", &gnd[i][j]); 
		}
	}
	count = (M - K)*(N - K);
	partial_sum();
	sort_max();
	find_max();
	printf("%d\n", result);

	return 0;
}