#include <iostream>
using namespace std;
#define MAX 42043

int N, K, T, idx;
int I[20005];
int D[100005][1005];

void set_table(){
	int temp;

	for (int j = 0; j <= K; j++){
		D[1][j] = D[1][j - 1] + I[j];
	}
	for (int i = 2; i <= N; i++){
		for (int j = 0; j <= K; j++){
			temp = 0;
			for (int k = 0; k <= j; k++){
				temp += I[k] * D[i - 1][j - k];
			}
			D[i][j] = temp % MAX;
		}
	}
}

int main(){
	int temp;

	cin >> N >> K >> T;
	for (int i = 1; i <= T; i++){
		cin >> temp;
		I[temp]++;
		if (temp > idx) idx = temp;
	}

	set_table();

	cout << D[N][K] << endl;

	return 0;
}