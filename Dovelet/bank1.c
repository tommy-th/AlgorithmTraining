#include <stdio.h>

int main(){

	int num[101], t1[101], t2[101], t3[101];
	int M, i, cur = 0;
	double sum = 0;

	t1[0] = t2[0] = t3[0] = 0;

	scanf("%d", &M);

	for (i = 1; i <= M; i++){
		scanf("%d %d %d", &num[i], &t1[i], &t2[i]);
		cur = t1[i - 1] + t2[i - 1] + t3[i - 1];
		if (cur > t1[i])
			t3[i] = cur - t1[i];
		else
			t3[i] = 0;
		sum += t3[i];
	}

	printf("%.1lf\n", sum / M);
}