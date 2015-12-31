#include <iostream>
using namespace std;
#define LL long long

LL C, D, V, coin[105];

int search(){
	LL a, r, n = 0, cnt = 0, cidx = 1;
	
	while (n < V){
		if (n + 1 >= coin[cidx] && cidx <= D){
			n += C*coin[cidx];
			cidx++;
		}
		else{
			n += C*(n + 1);
			cnt++;
		}
	}
	return cnt;
}

int main(){
	
	FILE *fin = freopen("C-large-practice.in", "r", stdin);
	FILE *fout = freopen("C-large-practice.out", "w", stdout);
	
	int t;
	
	cin >> t;
	for (int i = 1; i <= t; i++){
		cin >> C >> D >> V;

		for (int j = 1; j <= D; j++) cin >> coin[j];

		cout << "Case #" << i << ": " << search() << endl;

		fprintf(stderr, "Case #%d completed\n", i);
	}
	return 0;
}