#include <cstdio>
#include <iostream>
using namespace std; 

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int T, N, result;
int P[100005], LH[100005], RH[100005];

void left_set(){
	int idx = 1, height = 1;

	while (idx <= N){
		if (P[idx] < height) height = P[idx];
		LH[idx] = height;
		idx++, height++;
	}
}

void right_set(){
	int idx = N, height = 1;

	while (idx >= 1){
		if (P[idx] < height) height = P[idx];
		RH[idx] = height;
		idx--, height++;
	}
}

void search(){
	for (int i = 1; i <= N; i++){
		result = MAX(result, MIN(LH[i], RH[i]));
	}
}

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){
		result = 0;
		cin >> N;

		for (int i = 1; i <= N; i++) cin >> P[i];

		left_set();
		right_set();
		search();

		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}