#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

// Fail

int T, N, D, P[5005], result, err;

void errCheck(int n, int s){
	for (int i = 1; i <= n; i++){
		int j = i % s;
		if (j == 0) j = s;
		if (P[i] != P[j]) err = 1;
	}
}

void extract(int s){
	int max = 0, T[5005] = { 0, }, q[5000];

	if (err) return;

	for (int i = 1; i <= s; i++){
		if (P[i] - P[i + s] > 0) T[i] = P[i] - P[i + s];
		else T[i + s] = P[i + s] - P[i];
	}
	int on = 0, tt = 0;
	for (int i = 1; i <= 2 * s; i++){
		if (T[i] == 0 || i == 2*s){
			on = 1;
			int j = i + 1;
			while (j != i){
				if (T[j] > tt) tt = T[j];
				if (T[j] == 0){
					max += tt;
					tt = 0;
				}
				j++;
				if (j > 2 * s) j = 1;
			}
		}
		if (on) break;
	}
	max += tt; 
	for (int i = 1; i <= s; i++){
		int res = max - T[i] - T[i + s];
		if (res % 2) {
			err = 1;
			return;
		}
		T[i] += res / 2;
		T[i + s] += res / 2;
	}

	for (int i = 1; i <= 2 * s; i++) q[i] = T[i];
	on = 1;
	int prv = q[1];
	while (on){
		for (int i = 1; i <= 2 * s; i++){
			if (q[i]) on = 1;
			if (q[i] > prv){
				int dif = q[i] - prv;
				for (int cnt = i, j = i; cnt < i + s; cnt++, j++){
					if (j>2 * s) j = 1;
					if (q[j] < dif){
						err = 1;
						return;
					}
					else q[j] -= dif;
				}
			}
			prv = q[i];
		}
		on = 0;
	}

	for (int i = 1; i <= 2 * s; i++){
		if (P[i] < T[i]){
			int dif = T[i] - P[i];
			for (int j = 1; j <= 2 * s; j++) P[j] += dif;
		}
		P[i] -= T[i];
		if (T[i] < 0) fprintf(stderr, "extract %d err\n", s);
	}

	errCheck(2 * s, s);
	result += max;
	if (s > 1) extract(s / 2);
}

int main(){
	
	FILE *fin = freopen("E-small-practice.in", "r", stdin);
	FILE *fout = freopen("E-small-practice.out", "w", stdout);
	
	cin >> T;

	for(int t = 1; t <= T; t++) {
		cin >> N >> D;
		err = result = 0;

		int max = 0;
		for (int i = 1; i <= N; i++) {
			cin >> P[i];
			if (P[i] > max) max = P[i];
		}
		for (int i = 1; i <= N; i++) P[i] = max - P[i];

		errCheck(N, 2*D);
		extract(D);
		cout << "Case #" << t << ": ";
		if (err == 0) cout << result << endl;
		else cout << "CHEATERS!" << endl;

		fprintf(stderr, "Case #%d done\n", t);
	}
	return 0;
}