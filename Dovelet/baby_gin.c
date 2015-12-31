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

	if (low < j) quicksort(a,low, j);
	if (i < high)quicksort(a, i, high);
}

int main(){

	int card[6], card2[6] = { 0, }, i, h, j = 0, gin = 0;

	for (i = 0; i < 6; i++)
		scanf("%d", &card[i]);

	quicksort(card, 0, 5);

	for (i = 0; i < 6;){
		if (card[i] == card[i+1] && card[i+1] == card[i+2]){
			card[i] = card[i + 1] = card[i + 2] = -1;
			gin++;
			i += 3;
		}
		else
			i++;
	}
	if (gin == 0){
		for (i = 0; i < 5; i++){
			if (card[i + 1] == card[i] + 1)
				gin++;
		}
		if (gin == 5)
			gin = 2;
		else
			gin = 0;
	}

	else if (gin == 1){
		quicksort(card, 0, 5);
		if (card[4] == card[3] + 1 && card[5] == card[4] + 1)
			gin++;
	}

	if (card[1] == card[0] && card[2] == card[1] + 1 && card[3] == card[2] && card[4] == card[3] + 1 && card[5] == card[4])
		gin = 2;

	if (gin == 2)
		printf("gin\n");
	else
		printf("lose\n");
}