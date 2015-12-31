#include <stdio.h>

int P[10001];
int D[10001];
int S[10001];
int start, end, idx;

void set_table(){
	int i, j;
	for (i = 2; i < 101; i++){
		for (j = 1000; j < 10000; j++){
			if (j%i == 0) P[j] = 1;
		}
	}
}

int dec(int n){
	if (n < 2) return 1;
	return 10 * dec(n - 1);
}

int push(int n){
	int i, j, temp;
	if (end == n)
		return 1;
	for (i = 1; i <= 4; i++){
		temp = (n / dec(i + 1))*dec(i + 1) + n % dec(i);
		for (j = 0; j <= 9; j++){
			if (j == 0 && i == 4) j++;
			temp += j*dec(i);
			if (D[temp] == 0 && P[temp] == 0){
				D[temp] = D[n] + 1;
				S[idx++] = temp;
			}
			temp -= j*dec(i);
		}
	}
	return 0;
}

void search(){
	int i, on = 0;
	for (i = 0; i < idx; i++)
		if(on == 0) on = push(S[i]);
}

int main(){
	set_table();
	scanf("%d %d", &start, &end);
	S[idx++] = start;
	D[start] = 1;
	search();
	printf("%d\n", D[end]-1);

	return 0;
}