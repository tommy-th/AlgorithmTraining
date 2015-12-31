#include <stdio.h>

int n;
int a[12];
int count;

void print_case(int in, int idx){
	int i;
	for (i = in; i < a[idx]; i++)
		printf("x");
	printf("o");
	if (idx == n)
		printf("\n");
	else
		print_case(a[idx]+1,idx+1);
}

void serch(){
	int i=n, j;
	print_case(1,1);
	count++;
	while (a[1] != n){
		if (a[i] != 2 * n - 1 && a[i] != a[i + 1] - 1){
			a[i]++;
			j = i;
			while (j != n){
				a[j + 1] = a[j] + 1;
				j++;
			}
			print_case(1,1);
			count++;
			i = n;
		}
		else{
			i--;
		}
	}
}

int main(){

	int i;
	scanf("%d", &n);
	a[n + 1] = 0;
	for (i = 1; i < n+1; i++){
		a[i] = i;
	}
	serch();
	printf("total %d case(s)\n", count);

	return 0;
}