#include <stdio.h>

void quicksort(int* a, int low, int high){

	int i = low, j = high, h;
	int x = a[(low + high) / 2];

	do{
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if (i <= j){
			h = a[i]; a[i] = a[j]; a[j] = h;
			i++; j--;
		}
	} while (i <= j);

	if (low < j) quicksort(a, low, j);
	if (i < high)quicksort(a, i, high);
}

int main(){

	int result[4200][3];
	int s[30];
	int num, i, j, k, idx = 0, count=0;

	scanf("%d", &num);

	for (i = 0; i < num; i++)
		scanf("%d", &s[i]); 

	quicksort(s, 0, num-1);

	for (i = 0; i < num - 2; i++){
		for (j = i + 1; j < num - 1; j++){
			for (k = j + 1; k < num; k++){
				if (s[j] - s[i] == s[k] - s[j])
					count++;
			}
		}
	}

	printf("%d", count);

	return 0;


}