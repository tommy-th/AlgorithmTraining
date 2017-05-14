#include <stdio.h> 

int matrix[100][100];
int visit[100];
int n;

void dfs(int i)
{
	int j;

	visit[i] = 1; // i 번 정점은 방문 되었음 
	printf("%d ", i);

	for (j = 1; j <= n; j++)
	if (matrix[i][j] == 1 && visit[j] == 0) {  // 정점 i 에서 j 로의 길이 있고 j 번 정점이 방문되지 않았으면  
		dfs(j); // 재귀호출 
	}
}

int main()
{
	int ver1, ver2;
	int start;

	scanf("%d %d", &n, &start);

	while (scanf("%d %d", &ver1, &ver2) != EOF){
		matrix[ver1][ver2] = matrix[ver2][ver1] = 1;
	}

	dfs(start);

	return 0;
}