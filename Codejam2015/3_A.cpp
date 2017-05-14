#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define SET 1000005
#define LL long long

struct employee{
	int n, val;
	employee(){}
	employee(int n, int val) : n(n), val(val) { }
	bool operator < (const employee & oth) const{
		return val > oth.val;
	}
};
vector<employee> bq;
vector<employee> tq;
int low[SET], high[SET], H[SET];

int T, N, D;
int s, ts, as, cs, rs;
int m, am, cm, rm;

void reset(){
	bq.clear();
	tq.clear();
	memset(H, 0, sizeof(H));
	memset(low, 0, sizeof(low));
	memset(high, 0, sizeof(high));
}

int main(){
	
	FILE *fin = freopen("A-large-practice.in", "r", stdin);
	FILE *fout = freopen("A-large-practice.out", "w", stdout);
	
	cin >> T;
	for (int t = 1; t <= T; t++){
		int temp = 0, result = 0;
		cin >> N >> D;
		cin >> s >> as >> cs >> rs;
		cin >> m >> am >> cm >> rm;
		reset();
		ts = low[0] = high[0] = s;
		N--;
		for (int i = 1; i <= N; i++){
			int tmin, tmax;
			ts = (ts*as + cs) % rs;
			m = (m*am + cm) % rm;
			tmin = low[m%i]; tmax = high[m%i];
			if (ts < tmin) tmin = ts;
			if (ts > tmax) tmax = ts;
			low[i] = tmin; high[i] = tmax;
			bq.push_back(employee(i, tmin));
			tq.push_back(employee(i, tmax));
		}
		std::sort(bq.begin(), bq.end());
		std::sort(tq.begin(), tq.end());

		int i1 = 0;
		for (int i = 0; i < N; i++){
			if (tq[i].val > s + D || tq[i].val < s - D){
				H[tq[i].n] = 1;
				continue;
			}
			while (bq[i1].val >= tq[i].val - D){
				if (H[bq[i1].n] == 0){
					H[bq[i1].n] = 2;
					temp++;
				}
				i1++;
				if (i1 >= N) break;
			}
			if (H[tq[i].n] == 0) H[tq[i].n] = 1;
			if (temp > result) result = temp;
			if (H[tq[i].n] == 2) temp--;
			if (N - i1 + temp < result) break;
		}
		cout << "Case #" << t << ": " << result + 1 << endl;
		fprintf(stderr, "Case #%d: %d\n", t, result + 1);
	}

	return 0;
}