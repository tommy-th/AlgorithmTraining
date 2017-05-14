#include <stdio.h>

int result;
int p, s[150005];

int subsum(int n){
	int i = n + 1, max, min;
	max = s[n];
	while (max <= s[i]){
		max = s[i++];
	}
	min = s[i];
	while (min > s[i] && i < p + 2){
		min = s[i++];
	}
	result = result + max - min;

	return i;
}

void search(){
	int idx = subsum(1);

	while (idx <= p){
		idx = subsum(idx);
	}
}

int main(){


	int i;

	scanf("%d", &p);

	for (i = 1; i <= p; i++)
		scanf("%d", &s[i]);

	search();
	printf("%d\n", result);

	return 0;
}