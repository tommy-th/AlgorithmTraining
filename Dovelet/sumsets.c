#include <stdio.h>

int n;
int T[100001];
int D[1000001];

//int two(int u){
//	if (u == 0) return 1;
//	else{
//		if (T[u] == 0) T[u] = 2 * two(u - 1);
//		return T[u];
//	}
//}
//
//int nums(int u, int t){
//	int temp = u;
//	if (u == 0) return 1;
//	if (t == 1) return (int) u / 2+1;
//	if(D[u][t]==0){
//		D[u][t] = (D[u][t] + nums(temp, t - 1)) % 1000000000;
//		while (temp>0){
//			temp -= two(t);
//			if (temp < 0) break;
//			D[u][t] = (D[u][t] + nums(temp, t - 1)) % 1000000000;
//		}
//	}
//	return D[u][t];
//}


int main(){

	int i;

	scanf("%d", &n);

	D[0] = 1;
	D[1] = 1;
	D[2] = 2;
	D[3] = 2;

	for (i = 4; i <= n; i++){
		if (i % 2 == 0)
			D[i] = D[i - 1] + D[i / 2];
		else
			D[i] = D[i - 1];
		D[i] %= 1000000000;
	}

	//while (two(i) < n) i++;

	printf("%d", D[n]);

	return 0;
}