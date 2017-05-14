#include <stdio.h>
#include <math.h>

int start, end;
int D[10000];
int prime[10000];
int dump[1000];

char isTruePrime(int n){
	char on = 1;
	int j;
	if (n < 2 || prime[n] == -1) return 0;
	if (prime[n] == 1) return 1;
	for (j = 2; j <= sqrt(n) + 1; j++){
		if (n % j == 0) on = 0;
	}
	if (on) prime[n] = 1;
	else prime[n] = -1;
	return on;
}

void search(int idx, int path){
	int a[4], temp[1000];
	int i, j, t, u, sum, k = 0;

	for (t = 0; t < idx; t++){
		a[0] = dump[t] % 10;
		a[1] = (dump[t] / 10) % 10;
		a[2] = (dump[t] / 100) % 10;
		a[3] = dump[t] / 1000;
		for (i = 0; i < 4; i++){
			u = a[i];
			for (j = 0; j < 10; j++){
				if (a[i] != j){
					a[i] = j;
					sum = a[0] + a[1] * 10 + a[2] * 100 + a[3] * 1000;
					if (isTruePrime(sum) && D[sum] == 0 && sum>1000){
						if (sum == end){
							D[end] = path + 1;
							return;
						}
						else{
							D[sum] = path + 1;
							temp[k] = sum;
							k++;
						}
					}
					a[i] = u;
				}
			}
		}
	}
	for (i = 0; i < k; i++) dump[i] = temp[i];
	if (k > 0) search(k, path + 1);
}

int main(){
	int i, j;

	scanf("%d %d", &start, &end);
	if (start == end)
		printf("0\n");
	else{
		dump[0] = start;
		D[start] = 1;
		search(1, 0);
		printf("%d\n", D[end]);
	}
	return 0;
}