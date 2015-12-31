#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define FOR(i, n) for(int i = 1; i <= n; i++)
#define FORL(i, n) for(int i = n - 1; i >= 0; i--)

struct quail{
	double pos, v;
	quail(){}
	quail(int pos, int v) : pos(pos), v(v) { }
	bool operator < (const quail & oth) const{
		return pos < oth.pos;
	}	
};

vector<quail> lq, rq;
int lc, rc, T, Y, N, testcnt, testmax;
double D[2][505][505], P[505], S[505];

void get_right(int n, double s, double t, int r);

void get_left(int n, double s, double t, int r){
	testcnt++;
	if (testcnt > testmax)testmax = testcnt;
	if (n > lc) return;
	int rv = Y - lq[n - 1].v;
	double lt = (double)((lq[n - 1].pos + t*lq[n - 1].v + s) / rv);
	double ls = (double)(lq[n - 1].pos + (lt + t)*lq[n - 1].v);

	while (n < lc){
		rv = Y - lq[n].v;
		double tt = (double)((lq[n].pos + t*lq[n].v + s) / rv);
		if (tt <= lt){
			if (D[0][n][r] == 0 || lt + t < D[0][n][r]) D[0][n][r] = lt + t;
			n++;
		}
		else break;
	}

	if (D[0][n][r] == 0 || lt + t < D[0][n][r]) D[0][n][r] = lt + t;
	//else return;
	get_left(n + 1, -1 * ls, lt + t, r);
	get_right(r + 1, ls, lt + t, n);
	testcnt--;
}

void get_right(int n, double s, double t, int r){
	testcnt++;
	if (testcnt > testmax)testmax = testcnt;
	if (n > rc) return;
	int rv = Y - rq[n - 1].v;
	double rt = (double)((rq[n - 1].pos + t*rq[n - 1].v + s) / rv);
	double rs = (double)(rq[n - 1].pos + (rt + t)*rq[n - 1].v);

	while (n < rc){
		rv = Y - rq[n].v;
		double tt = (double)((rq[n].pos + t*rq[n].v + s) / rv);
		if (tt <= rt){
			if (D[1][n][r] == 0 || rt + t < D[1][n][r]) D[1][n][r] = rt + t;
			n++;
		}
		else break;
	}

	if (D[1][n][r] == 0 || rt + t < D[1][n][r]) D[1][n][r] = rt + t;
	//else return;
	get_right(n + 1, -1 * rs, rt + t, r);
	get_left(r + 1, rs, rt + t, n);
	testcnt--;
}

int main(){
	FILE *fin = freopen("C-large-practice.in", "r", stdin);
	FILE *fout = freopen("C-large-practice.out", "w", stdout);

	int max;
	
	cin >> T;
	FOR(t, T){
		cin >> Y >> N;
		FOR(i, N) cin >> P[i];
		FOR(i, N) cin >> S[i];
		lc = rc = 0;
		lq.clear();
		rq.clear();
		FOR(i, N){
			if (P[i] < 0) { lq.push_back(quail(-1 * P[i], S[i])); lc++; }
			else { rq.push_back(quail(P[i], S[i])); rc++; }
		}
		std::sort(lq.begin(), lq.end());
		std::sort(rq.begin(), rq.end());
		max = 0;
		FORL(i, lc){
			if (lq[i].v > max) max = lq[i].v;
			else { vector<quail>::iterator it = lq.erase(lq.begin() + i); lc--; }
		}
		max = 0;
		FORL(i, rc){
			if (rq[i].v > max) max = rq[i].v;
			else { vector<quail>::iterator it = rq.erase(rq.begin() + i); rc--; }
		}
		testmax = testcnt = 0;
		memset(D, 0, sizeof(D));
		get_left(1, 0, 0, 0);
		get_right(1, 0, 0, 0);
		
		double r2 = D[1][rc][lc];
		double r1 = D[0][lc][rc];
	
		cout << "Case #" << t << ": ";
		if (r1 > r2 && r2 != 0) printf("%.12f\n", r2);
		else printf("%.12f\n", r1);

		fprintf(stderr, "Case #%d : %d\n", t, testmax);
	}
	return 0;
}