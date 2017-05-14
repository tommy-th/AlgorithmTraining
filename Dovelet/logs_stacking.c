#include <stdio.h>

int main(){

	int n, i, pre1 = 1, pre2 = 1, temp = 1;

	scanf("%d", &n);

	n %= 75000;

	for (i = 2; i <= n; i++){
		temp = (3 * pre1 - pre2)%100000;
		if (temp < 0) temp += 100000;
		pre2 = pre1;
		pre1 = temp;
	}

	printf("%d\n", temp); 

	return 0;
}