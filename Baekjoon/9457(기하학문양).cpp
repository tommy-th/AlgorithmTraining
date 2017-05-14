#include <iostream>
using namespace std;

#define MAX 10007

int T, N, R[50005][10];
int rf[8][8] = { 
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1 }, 
		{ 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 1, 1, 1, 0, 0, 0, 0 },
};

void init_table(){
	for (int i = 1; i <= 7; i++){
		R[2][i] = 1;
	}
}

void set_table(){
	for (int n = 3; n <= 50000; n++){
		for (int i = 1; i <= 7; i++){
			for (int j = 1; j <= 7; j++){
				if (rf[i][j]) R[n][i] += R[n - 1][j];
			}
			R[n][i] %= MAX;
		}
	}
}

int rec_cases(int s, int e, int n){
	int ret = 0;
	for (int i = s; i <= e; i++){
		ret += R[n][i];
	}
	return ret % MAX;
}

int main(){
	init_table();
	set_table();

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N;
		int result = rec_cases(4, 7, N);
		cout << result << endl;
		result += rec_cases(1, 3, N - 1);
		result += 2*rec_cases(4, 7, N - 1);
		result *= N;
		result -= N;
		result %= MAX;
		cout << result << endl;
	}

	return 0;
}