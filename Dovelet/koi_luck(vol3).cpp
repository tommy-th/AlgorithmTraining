#include <iostream>
using namespace std;
#define MAX 42043

int N, K, T;
int D[100005][1005];

void multiply(int a, int b){
	for (int i = 0; i <= K; i++){
		for (int j = 0; i + j <= K; j++){
			D[a + b][i + j] += D[a][i] * D[b][j];
			D[a + b][i + j] %= MAX;
		}
	}
}

void set_table(){

	int n = N, idx = 1, a = 1;

	while (a + idx <= N){
		multiply(a, idx);
		a += idx;
		idx *= 2;
	}

	while (a != N){
		if (N >= a + idx){
			multiply(a, idx);
			a += idx;
		}
		else{
			idx /= 2;
		}
	}
}

int main(){
	int temp, result = 0;

	cin >> N >> K >> T;
	for (int i = 1; i <= T; i++){
		cin >> temp;
		D[1][temp]++;
	}

	set_table();

	for (int i = 0; i <= K; i++){
		result += D[N][i];
		result %= MAX;
	}

	cout << result << endl;

	return 0;
}