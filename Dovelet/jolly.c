#include <stdio.h>
#include <stdlib.h>

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

	int* nums;
	int* subs;
	int n, i, j, jolly = 0;

	scanf("%d", &n);
	if (n == 1){
		printf("Jolly\n");
		return 0;
	}
	nums = (int*)malloc(sizeof(int)*(n+1));
	subs = (int*)malloc(sizeof(int)*(n+1));
	nums[0] = 0;
	for (i = 1; i <= n; i++){
		scanf("%d", &nums[i]);
		if (nums[i] > nums[i - 1])
			subs[i] = nums[i] - nums[i - 1];
		else
			subs[i] = nums[i - 1] - nums[i];
	}
	quicksort(subs, 2, i-1);

	for (j = 2; j < i; j++){
		if (subs[j] != j - 1){
			printf("Not jolly\n");
			free(nums);
			free(subs);
			return 0;
		}
	}
	printf("Jolly\n");
	free(nums);
	free(subs);
	return 0;
}