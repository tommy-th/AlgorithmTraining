#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#define SINK 200000

int T, N, result;
int A[5005], D[400005];

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){

		result = 0;
		memset(A, 0, sizeof(A));
		memset(D, 0, sizeof(D));

		cin >> N;
		for (int i = 1; i <= N; i++){
			cin >> A[i];
			for (int j = 1; j < i; j++) {
				if (D[A[i] - A[j] + SINK]) {
					result++;
					break;
				}
			}
			for (int j = 1; j <= i; j++){
				D[A[i] + A[j] + SINK] = 1;
			}
		}

		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}