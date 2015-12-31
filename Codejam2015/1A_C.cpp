#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

#define PI acos(-1.0)

vector<double>th;
int N, D[3005], X[3005], Y[3005];

int main(){
	
//	FILE *fin = freopen("C-large-practice.in", "r", stdin);
//	assert(fin != NULL);
//	FILE *fout = freopen("C-large-practice.out", "w", stdout);
	
	int t; cin >> t;
	for (int i = 1; i <= t; i++){
		cin >> N;
		memset(D, 0, sizeof(D));
		for (int j = 1; j <= N; j++) cin >> X[j] >> Y[j];

		for (int j = 1; j <= N; j++){
			th.clear();
			for (int k = 1; k <= N; k++){
				if (j == k) continue;
				th.push_back(atan2(Y[k] - Y[j], X[k] - X[j]) * 180 / PI);
				th.push_back(atan2(Y[k] - Y[j], X[k] - X[j]) * 180 / PI + 360);
			}
			std::sort(th.begin(), th.end());
			int e = 0;
			for (int k = 0; k < th.size(); k++){
				while (th[k] - th[e] > 180 && e < th.size()) e++;
				if (k - e + 1 > D[j]) D[j] = k - e + 1;
			}
		}
		cout << "Case #" << i << ":" << endl;
		for (int j = 1; j <= N; j++) cout << N - D[j] - 1 << endl;
	}
	return 0;
}