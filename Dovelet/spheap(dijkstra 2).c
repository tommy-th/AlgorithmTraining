#include <stdio.h>

int N, M;
int hash[205][205];
int map[205][205];
int min_fee[205][205];
int ix, iy, px, py;

typedef struct __HEAP{
	int x;
	int y;
	int charge;
}HEAP;

HEAP heap[50000];
int h_idx = 1;

void insert_heap(int y, int x, int data){
	HEAP temp;
	int idx = h_idx;
	h_idx++;
	heap[idx].x = x;
	heap[idx].y = y;
	heap[idx].charge = data;

	while (idx != 1 && heap[idx].charge < heap[idx / 2].charge){
		temp = heap[idx / 2];
		heap[idx / 2] = heap[idx];
		heap[idx] = temp;
		idx /= 2;
	}
}

HEAP extract_heap(){
	int ridx, idx = --h_idx;
	HEAP temp, result = heap[1];
	heap[1] = heap[idx];
	idx = 1;


	while ((idx * 2 <= h_idx && heap[idx].charge > heap[idx * 2].charge) || (idx * 2 + 1 <= h_idx && heap[idx].charge > heap[idx * 2 + 1].charge)){
		if (heap[idx * 2].charge < heap[idx * 2 + 1].charge || idx * 2 + 1 >= h_idx) ridx = idx * 2;
		else ridx = idx * 2 + 1;
		temp = heap[ridx];
		heap[ridx] = heap[idx];
		heap[idx] = temp;
		idx = ridx;
	}
	return result;
}

// 다익스트라로 구현
void find_min(){
	HEAP temp;
	int p, i, j, x, y;

	hash[iy][ix] = 1;
	insert_heap(iy, ix, map[iy][ix]);
	min_fee[iy][ix] = map[iy][ix];
	for (p = 1; p <= N*M; p++){

		//for (i = 1; i <= N; i++){											// 전체 탐색 시 시간초과 -> 힙으로 구현해야 됨
		//	for (j = 1; j <= M; j++){
		//		if (hash[i][j] == 1 && min_fee[i][j] < min){
		//			min = min_fee[i][j];
		//			x = j, y = i;
		//		}
		//	}
		//}

		//힙으로 구현 부분
		temp = extract_heap();
		x = temp.x;
		y = temp.y;

		hash[y][x] = 2;
		if (map[y - 1][x] && hash[y - 1][x] == 0){
			min_fee[y - 1][x] = map[y - 1][x] + min_fee[y][x];
			hash[y - 1][x] = 1;
			insert_heap(y - 1, x, min_fee[y - 1][x]);
		}
		if (map[y + 1][x] && hash[y + 1][x] == 0){
			min_fee[y + 1][x] = map[y + 1][x] + min_fee[y][x];
			hash[y + 1][x] = 1;
			insert_heap(y + 1, x, min_fee[y + 1][x]);
		}
		if (map[y][x + 1] && hash[y][x + 1] == 0){
			min_fee[y][x + 1] = map[y][x + 1] + min_fee[y][x];
			hash[y][x + 1] = 1;
			insert_heap(y, x + 1, min_fee[y][x + 1]); 
		}
		if (map[y][x - 1] && hash[y][x - 1] == 0){
			min_fee[y][x - 1] = map[y][x - 1] + min_fee[y][x];
			hash[y][x - 1] = 1;
			insert_heap(y, x - 1, min_fee[y][x - 1]);
		}
	}
}


int main(){

	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++){
		for (j = 1; j <= M; j++){
			scanf("%d", &map[i][j]);
		}
	}
	scanf("%d %d %d %d", &iy, &ix, &py, &px);
	find_min();
	printf("%d\n", min_fee[py][px]);

	return 0;
}


// 재귀로 풀었을 때 시간초과
/*
void search_min(int y, int x, int charge){
	if (map[y][x] == 0) return;
	if (map[y][x] + charge > min_fee[y][x] && min_fee[y][x]) return;
	min_fee[y][x] = map[y][x] + charge;

	search_min(y - 1, x, min_fee[y][x]);
	search_min(y, x - 1, min_fee[y][x]);
	search_min(y, x + 1, min_fee[y][x]);
	search_min(y + 1, x, min_fee[y][x]);
}
*/