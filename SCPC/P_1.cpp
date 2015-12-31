#include <cstdio>
#include <iostream>
using namespace std;

int T, N;

int main(){

	int input, result;

	cin >> T;

	for (int t = 1; t <= T; t++){
		result = 0;
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> input;
			result ^= input;
		}
		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}