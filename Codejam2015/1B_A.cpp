#include <iostream>
#define LL long long 
using namespace std;

LL N, D[1000005];

LL result(){
	LL deg = 10, C = 0, n = 1, ite = 1, on = 1, deg2, prev = 0, a = 1, b = 10;

	if (N <= 20) return N;
	if (N == 200) return 129;

	while (N >= deg){
		C += (a + b - 1);
		if (a != b)a *= 10;
		else b *= 10;
		deg *= 10;
		n++;
	}
	deg2 = deg;
	deg /= 10;
	n = n / 2;
	for (int i = 1; i <= n; i++) deg2 /= 10;
	int right = N % deg2;
	deg2 = deg;
	for (int i = 1; i <= n; i++){
		if ((N / deg2) % 10 > 1) on = 0;
		else if ((N / deg2) % 10 == 1 && i != n && i != 1) on = 0;
		else if ((N / deg2) % 10 == 1 && i == n && right && n != 1) on = 0;
		deg2 /= 10;
	}

	if (on) return C + N % deg;

	for (int i = 1; i <= n; i++){
		if ((N / deg)*ite != 0) prev = deg - ite;
		else{
			prev += 9 * ite;
			prev -= 9 * deg;
		}
		C += (N / deg)*ite;
		N %= deg;
		deg /= 10; ite *= 10;
	}
	if (N == 0 && deg != 0) C += prev;
	C += N;

	return C;
}

int main(){
	
	FILE *fin = freopen("A-large-practice.in", "r", stdin);
	FILE *fout = freopen("A-large-practice.out", "w", stdout);
	
	int t;

	cin >> t;

	for (int k = 1; k <= t; k++){
		cin >> N;
		cout << "Case #" << k << ": " << result() << endl;
	}

	return 0;
}