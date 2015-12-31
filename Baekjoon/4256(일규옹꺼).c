#include<stdio.h>
#define Max_n 1000

int T, N, K, M;

int Pre[Max_n], In[Max_n], Post[Max_n];

void recall(int st, int ed)
{
	int i, mid;

	K++;

	for (i = st; i <= ed; i++){
		if (In[i] == Pre[K]){
			mid = i;
			break;
		}
	}

	if (st <= mid - 1) recall(st, mid - 1);
	if (mid + 1 <= ed) recall(mid + 1, ed);

	Post[M++] = In[mid];
}

int main()
{
	int i, j;

	scanf("%d", &T);

	for (i = 0; i<T; i++){
		scanf("%d", &N);
		for (j = 0; j<N; j++){
			scanf("%d", &Pre[j]);
		}
		for (j = 0; j<N; j++){
			scanf("%d", &In[j]);
		}
		K = -1;
		M = 0;
		recall(0, N - 1);
		for (j = 0; j<N; j++){
			printf("%d ", Post[j]);
		}
		printf("\n");
	}
	return 0;
}