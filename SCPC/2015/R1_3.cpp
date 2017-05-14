#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define LL long long
int T, N;

LL calcSum(LL b){
	LL ret = 0, temp = 1;
	while (ret + temp <= N){
		ret += temp;
		temp *= b;
	}
	return ret;
}

LL minUniform(){
	LL ret = N, sum;

	if (N == 1) return 2;
	for (int i = 2; i <= sqrt(N); i++){
		sum = calcSum(i);
		if (N % sum == 0)
			return i;
	}

	for (int i = 1; i <= sqrt(N); i++){
		if (N % i == 0){
			if (N / i - 1 < ret && N / i - 1 > sqrt(N))
				ret = N / i - 1;
		}
	}

	return ret;
}

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N;

		printf("Case #%d\n", t);
		cout << minUniform() << endl;
	}

	return 0;
}