#include <stdio.h>

int cow[205];
int dis[205];
int M, S, C;

void quicksort(int* a, int low, int high){

	int i = low, j = high, h;
	int x = a[(low + high) / 2];

	do{
		while (a[i] > x) i++;
		while (a[j] < x) j--;
		if (i <= j){
			h = a[i]; a[i] = a[j]; a[j] = h;
			i++; j--;
		}
	} while (i <= j);

	if (low < j) quicksort(a, low, j);
	if (i < high)quicksort(a, i, high);
}

int main(){

	int i, j = 0, temp, a=1000, b=0, count = 0, result;

	scanf("%d %d %d", &M, &S, &C);


	for (i = 1; i <= C; i++){
		scanf("%d", &temp);
		cow[temp] = 1;
		if (temp < a)a = temp;
		if (temp > b)b = temp; 
	}

	for (i = a; i <= b; i++){
		if(cow[i]==0) count++;
		else if(count != 0){
			dis[j++] = count;
			count = 0;
		}
	}

	quicksort(dis, 0, j);

	result = b - a + 1;

	for (i = 0; i < M - 1; i++)
		result -= dis[i];

	printf("%d\n", result);

	return 0;
}