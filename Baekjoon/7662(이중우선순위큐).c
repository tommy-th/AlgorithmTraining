#include <stdio.h>

int hIdx;
int max[1000010];
int min[1000010];

void insert_data(int data){
	int temp, idx;
	hIdx++;
	max[hIdx] = data;
	min[hIdx] = data;
	idx = hIdx;

	// max heap
	while (idx != 1 && max[idx / 2] < max[idx]){
		temp = max[idx];
		max[idx] = max[idx / 2];
		max[idx / 2] = temp;
		idx /= 2;
	}

	// min heap
	idx = hIdx;
	while (idx != 1 && min[idx / 2] > min[idx]){
		temp = min[idx];
		min[idx] = min[idx / 2];
		min[idx / 2] = temp;
		idx /= 2;
	}
}

void delete_data(int d){
	int result, temp, ridx, idx = 1, i, j = hIdx;

	if (hIdx <= 0) return;

	// D 1
	if (d == 1){
		result = max[1];
		max[1] = max[hIdx];
		while (idx * 2 <= hIdx - 1){
			if (max[idx * 2] > max[idx * 2 + 1] || idx * 2 + 1 > hIdx - 1) ridx = idx * 2;
			else ridx = idx * 2 + 1;
			if (max[idx] < max[ridx]){
				temp = max[ridx];
				max[ridx] = max[idx];
				max[idx] = temp;
				idx = ridx;
			}
			else{
				break;
			}
		}
		while (result != min[j]) j--;
		min[j] = min[hIdx];
		while (j != 1 && min[j / 2] > min[j]){
			temp = min[j];
			min[j] = min[j / 2];
			min[j / 2] = temp;
			j /= 2;
		}

	}

	// D -1
	else{
		result = min[1];
		min[1] = min[hIdx];
		while (idx * 2 <= hIdx - 1){
			if (min[idx * 2] < min[idx * 2 + 1] || idx * 2 + 1 > hIdx - 1) ridx = idx * 2;
			else ridx = idx * 2 + 1;
			if (min[idx] > min[ridx]){
				temp = min[ridx];
				min[ridx] = min[idx];
				min[idx] = temp;
				idx = ridx;
			}
			else{
				break;
			}
		}
		while (result != max[j]) j--;
		max[j] = max[hIdx];
		while (j != 1 && max[j / 2] < max[j]){
			temp = max[j];
			max[j] = max[j / 2];
			max[j / 2] = temp;
			j /= 2;
		}
	}
	hIdx--;
}

int main(){
	char s[10];
	char d;
	int t, k, i, j, data;

	scanf("%d", &t);

	for (i = 0; i < t; i++){
		scanf("%d", &k);
		for (j = 0; j < k; j++){
			gets(s);
			scanf("%c", &d);
			scanf("%d", &data);
			if (d == 'D'){
				if (data == 1){
					delete_data(1);
				}
				else{
					delete_data(0);
				}
			}
			else{
				insert_data(data);
			}
		}
		if (hIdx){
			printf("%d %d\n", max[1], min[1]);
		}
		else{
			printf("EMPTY\n");
		}
		hIdx = 0;
	}

	return 0;
}