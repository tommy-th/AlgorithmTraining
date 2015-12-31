#include <cstdio>
#include <iostream>
using namespace std;

#define LL long long
#define MAX 1000000007

LL D[2000005];
int T, N, M;

LL recip(LL n, int idx){
	if (idx == 0) return 1;
	if (idx == 1) return n;
	if (idx % 2 == 0) return recip((n*n) % MAX, idx / 2);
	else return (n*recip((n*n) % MAX, idx / 2)) % MAX;
}

LL combi(int n, int k){
	LL result = D[n];

	result *= recip((D[k]*D[n-k])%MAX, MAX - 2);

	return (result - 1) % MAX;
}

int main(){
	cin >> T;

	D[0] = D[1] = 1;
	for (LL i = 2; i <= 2000002; i++){
		D[i] = (i*D[i - 1]) % MAX;
	}
	for (int t = 1; t <= T; t++){
		cin >> N >> M;

		printf("Case #%d\n", t);
		cout << combi(N + M + 2, N + 1) << endl;
	}

	return 0;
}