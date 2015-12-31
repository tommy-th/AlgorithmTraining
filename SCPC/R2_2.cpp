#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Fail

#define LL long long
#define MOD 1000000007
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

char result[10];
int a, b, c;
int T, N, K;

char compare(){
	int d, on = 0;

	for (int i = 1; i <= b; i++){
		int s = N - i;
		d = K*b + a;
		s %= d;
		while (s <= K*a){
			if (s >= a && s <= K*a) return 'a';
			s += d;
		}
	}
	return 'b';
}

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> a >> b >> c;
		printf("Case #%d\n", t);
		for (int i = 0; i < c; i++){
			cin >> N >> K;
			result[i] = compare();
		}
		result[c] = '\0';
		cout << result << endl;
	}

	return 0;
}