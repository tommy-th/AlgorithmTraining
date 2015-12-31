#include <stdio.h>

int main(){

	int n,i,g[31];
	int sam, ella;
	int meat1, meat2;

	scanf("%d", &n);
	sam = 1; ella = n;

	for (i = 1; i <= n; i++){
		scanf("%d", &g[i]);
	}

	meat1 = g[1], meat2 = g[n];

	while (sam != ella - 1){
		if (meat1 <= meat2){
			sam++;
			meat1 += g[sam];
		}
		else if (meat2 <= meat1){
			ella--;
			meat2 += g[ella];
		}
	}

	if (meat1 == meat2){
		printf("Sam stops at position %d and Ella stops at position %d.\n", sam, ella);
	}
	else{
		printf("No equal partitioning.\n");
	}
}