#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 105

struct Source{
	double r, c;
	Source(){}
	Source(double r, double c) : r(r), c(c) { }
	bool operator < (const Source & oth) const {
		return c < oth.c || (c == oth.c && r < oth.r);
	}
};

vector <Source> q;
double V, X;
int N, T;

int main(){

	
	FILE *fin = freopen("B-small-practice.in", "r", stdin);
	FILE *fout = freopen("B-small-practice.out", "w", stdout);
	
	double tr, tc, temp, sum, result;
	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> V >> X;
		q.clear();
		for (int i = 1; i <= N; i++){
			cin >> tr >> tc;
			q.push_back(Source(tr, tc - X));
		}
		std::sort(q.begin(), q.end());
		sum = temp = 0;
		for (int i = 0; i < N; i++){
			temp += (q[i].c * q[i].r);
			sum += q[i].r;
		}
		if (temp == 0);
		else if (temp < 0){
			sum = temp = 0;
			for (int i = N - 1; i >= 0; i--){
				temp += (q[i].c * q[i].r);
				sum += q[i].r;
				if (temp < 0){
					temp -= (q[i].c * q[i].r);
					sum -= q[i].r;
					sum += temp / (-1 * q[i].c);
					break;
				}
			}
		}
		else{
			sum = temp = 0;
			for (int i = 0; i < N; i++){
				temp += (q[i].c * q[i].r);
				sum += q[i].r;
				if (temp > 0){
					temp -= (q[i].c * q[i].r);
					sum -= q[i].r;
					sum += (-1 * temp) / q[i].c;
					break;
				}
			}
		}

		cout << "Case #" << t << ": ";
		if (sum == 0) {
			cout << "IMPOSSIBLE" << endl;
			fprintf(stderr, "Case #%d IMPOSSIBLE\n", t);
		}
		else {
			result = (double)V / sum;
			printf("%0.6f\n", result);
			fprintf(stderr, "Case #%d POSSIBLE\n", t);
		}
	}

	return 0;
}