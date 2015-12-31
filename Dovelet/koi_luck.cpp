#include <iostream>
using namespace std;
#define MAX 42043

int N, K, T, idx;
int I[20005];
int D[100005][1005];

int case_num(int n, int k){
	int result = 0;
	if (n == 1){
		for (int i = 0; i <= idx; i++){
			if (k >= i) result += I[i];
		}
	}
	else{
		for (int i = 0; i <= idx; i++){
			if (k >= i){
				if (D[n - 1][k - i] == 0)
					D[n - 1][k - i] = case_num(n - 1, k - i);
				
				result += I[i]*D[n - 1][k - i];
				result %= MAX;
			}
		}
	}

	D[n][k] = result % MAX;
	return D[n][k];
}

int main(){

	int temp;

	cin >> N >> K >> T;
	for (int i = 1; i <= T; i++){
		cin >> temp;
		I[temp]++;
		if (temp > idx) idx = temp;
	}

	cout << case_num(N, K) << endl;

	return 0;
}