#include <stdio.h>
#include <stdlib.h>

int main(){
	int temp;
	int* answer;
	int* s;
	int n,i,j,q,a,b;

	scanf("%d", &n);
	s = (int*)malloc(sizeof(int)*(n+1));
	s[0] = 0;

	for (i = 1; i < n + 1; i++){
		scanf("%d", &temp);
		s[i] = s[i - 1] + temp;
	}

	scanf("%d", &q);

	answer = (int*)malloc(sizeof(int)*(q + 1));

	for (i = 1; i < q + 1; i++){
		scanf("%d %d", &a, &b); 
		answer[i] = s[b]-s[a-1];
	}
	for (i = 1; i < q + 1; i++){
		printf("%d\n", answer[i]);
	}
	free(s);
	free(answer);
}