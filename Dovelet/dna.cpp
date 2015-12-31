#include <iostream>
#include <cstring>
using namespace std;

int result;
int N;
int len[20];

char sum[100];
char input[20][20];

int match(int a, int b, int n){
	int on = 1;

	if (a - b < 0) return 0;
	
	for (int i = 0; i < b; i++){
		if (sum[a - b + i] != input[n][i]) on = 0;
	}
	return on;
}

void overlap(int* odr){

	int sub, idx = 0;

	for (int i = 0; i < N; i++){
		sub = 0;
		for (int j = 1; j <= len[odr[i]]; j++){
			if (match(idx, j, odr[i])) sub = j;
		}
		for (int j = sub; j < len[odr[i]]; j++){
			sum[idx++] = input[odr[i]][j];
		}
	}
	if (idx < result) result = idx;
}

void search(int idx, int* odr){
	int on;

	for (int i = 0; i < N; i++){
		on = 1;
		for (int j = 0; j < idx; j++){
			if (odr[j] == i) on = 0;
		}
		if (on){
			odr[idx] = i;
			if (idx < N - 1) search(idx + 1, odr);
			else overlap(odr);
		}
	}
}

int main(){

	int order[7] = { 0, };

	result = 100000;

	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> input[i];
		len[i] = strlen(input[i]);
	}

	search(0, order);

	cout << result << endl;

	return 0;
}