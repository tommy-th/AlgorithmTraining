#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#define nums 1000005

int D[nums], stones[nums];
int T, N, K;

int movePoint(int start, int idx){
	int counts = 0;
	while (1){
		if (start + K >= stones[idx + counts]) counts++;
		if (stones[idx + counts] > start + K){
			counts--;
			break;
		}
		if (idx + counts >= N) break;
	}
	return counts;
}

int minCounts(){
	int start = 0, idx = 0, len, istrue = 0, counts = 0;

	do {
		len = movePoint(start, idx);
		idx += len;
		counts++;
		if (idx == N)break;
		start = stones[idx];
	} while (len);

	if (idx == N) return counts;
	else return -1;
}

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){

		memset(D, 0, sizeof(D));
		cin >> N;
		for (int i = 1; i <= N; i++){
			cin >> stones[i];
		}
		cin >> K;
		printf("Case #%d\n", t);
		cout << minCounts() << endl;
	}

	return 0;
}