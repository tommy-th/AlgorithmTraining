#include <stdio.h>

int D[202][5];
int coins[5] = { 1, 5, 10, 25, 50 };

int nums(int n, int s){
	int temp = n, sum = 0;

	if (s == 0) return 1;

	while (temp >= coins[s]){
		if (D[temp][s - 1] == 0) D[temp][s - 1] = nums(temp, s - 1);
		sum += D[temp][s - 1];
		temp -= coins[s];
	}
	if (temp < coins[s]){
		if (D[temp][s - 1] == 0) D[temp][s - 1] = nums(temp, s - 1);
		sum += D[temp][s - 1];
	}

	return sum;
}

int main(){

	int coin, i = 4;
	double input;

	scanf("%lf", &input);
	coin = input * 100;

	while (coins[i] > coin) i--;

	printf("%d\n", nums(coin, i));

	return 0;
}