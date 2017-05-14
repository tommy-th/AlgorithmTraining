#include <stdio.h>

int D[3][100001];
int nums;

void setmax(){
	int i;

	for (i = 2; i <= nums; i++){
		if (D[1][i - 1] > D[1][i - 2]) D[2][i] += D[1][i - 1];
		else D[2][i] += D[1][i - 2];

		if (D[2][i - 1] > D[2][i - 2]) D[1][i] += D[2][i - 1];
		else  D[1][i] += D[2][i - 2];
	}
}

int main(){

	int i, j, t;	
	scanf("%d", &t);

	for (i = 0; i < t; i++){
		scanf("%d", &nums);
		for (j = 1; j <= nums; j++)
			scanf("%d", &D[1][j]); 
		for (j = 1; j <= nums; j++)
			scanf("%d", &D[2][j]);
		setmax();
		if (D[1][nums] > D[2][nums]) printf("%d\n", D[1][nums]);
		else printf("%d\n", D[2][nums]);
	}
	return 0;
}