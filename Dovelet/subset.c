#include <stdio.h>

int D[40][40][400];

int serch(int n, int num, int sum){
	int cut = n*num - num*(num - 1) / 2;
	
	if (cut < sum || n < num || sum <= 0)
		return 0;
	else if (num == 1 && n >= sum || cut==sum)
		return 1;
	else{
		if (D[n - 1][num][sum] == 0) D[n - 1][num][sum] = serch(n - 1, num, sum);
		if (D[n - 1][num - 1][sum - n] == 0) D[n - 1][num - 1][sum - n] = serch(n - 1, num - 1, sum - n);
		return D[n - 1][num][sum] + D[n - 1][num - 1][sum - n];
	}
}

int main(){
	
	int n, m, temp, sum = 0, idx = 0, result = 0;
	scanf("%d", &n);

	m = (n + 1)*n / 2;

	if (m % 2 == 1){
		printf("0\n");
		return 0;
	}

	m /= 2;
	temp = n;

	while (sum < m){
		sum += temp;
		temp--;
		idx++;
	}

	// idx부터 temp사이 중간까지 serch~!
	if ((idx + temp) % 2 == 0){
		temp = (idx + temp) / 2;
		while (idx <= temp){
			result += serch(n, idx, m);
			idx++;
		}
		result -= serch(n, temp, m)/2;
	}
	else{
		temp = (idx + temp) / 2;
		while (idx <= temp){
			result += serch(n, idx, m);
			idx++;
		}
	}

	printf("%d", result);
	return 0;
}