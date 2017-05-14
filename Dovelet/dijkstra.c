#include <stdio.h>
#define MAX 100005

typedef struct _NODE{
	int distance;
	int parent;
	int visited;
}NODE;

int N, M, S;
NODE node[1005];
int D[1005][1005];

void init(){
	int i;
	for (i = 1; i <= N; i++){
		node[i].distance = MAX;
		node[i].parent = 0;
		node[i].visited = 0;
	}
	node[S].distance = 0;
	node[S].parent = S; 
}

void search(){
	int i, j, min = MAX, n = 0;

	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			if (node[j].distance < min && node[j].visited == 0){
				min = node[j].distance;
				n = j;
			}
		}

		node[n].visited = 1;

		for (j = 1; j <= N; j++){
			if (D[n][j] && node[n].distance + D[n][j] < node[j].distance){
				node[j].distance = node[n].distance + D[n][j];
				node[j].parent = n;
			}
		}
		min = MAX;
	}
}

void print(int n){
	int arr[2000];
	int i, idx = 0, temp = n;

	while (node[temp].parent != S){
		arr[idx++] = node[temp].parent;
		temp = node[temp].parent;
	}

	if (n != S) printf("%d ", S);
	for (i = idx - 1; i >= 0; i--)
		printf("%d ", arr[i]); 
	printf("%d\n", n);
}

int main(){

	int i, a, b, c;

	scanf("%d %d %d", &N, &M, &S);

	for (i = 0; i < M; i++){
		scanf("%d %d %d", &a, &b, &c);
		D[a][b] = c;
	}
	init();
	search();
	for (i = 1; i <= N; i++){
		print(i);
	}

	return 0;
}