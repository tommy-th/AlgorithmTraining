#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define LL long long
#define MOD 1000000007

struct obstacle{
	int x, y, n;
	obstacle(){}
	obstacle(int x, int y, int n) : x(x), y(y), n(n){}
	bool operator < (const obstacle& oth) const{
		return x < oth.x || (x == oth.x && y < oth.y);
	}
};

vector<obstacle> obstacles;
LL pecto[200010], recips[200010];
int T, N, M, K;

void make_pecto(){
	pecto[0] = 1;
	for (int i = 1; i <= 200009; i++){
		pecto[i] = (pecto[i - 1] * i) % MOD;
	}
}

LL recip(LL n, int e){
	if (e == 0) return 1;
	if (e == 1) return n;
	if (e % 2 == 0) return recip((n*n) % MOD, e / 2);
	else return (n*recip((n*n) % MOD, e / 2)) % MOD;
}

LL combi(LL n, int r){
	LL ret = pecto[n];
	if (recips[n - r] == 0) recips[n - r] = recip(pecto[n - r], MOD - 2);
	if (recips[r] == 0) recips[r] = recip(pecto[r], MOD - 2);

	ret *= (recips[r] * recips[n - r]) % MOD;

	return ret % MOD;
}

LL paths(int h, int w){
	return combi(w + h - 2, h - 1);
}

void cut_paths(){
	int w, h;

	K = obstacles.size();
	for (int i = 0; i < K; i++){
		for (int j = i + 1; j < K; j++){
			if (obstacles[j].y >= obstacles[i].y){
				w = obstacles[j].x - obstacles[i].x + 1;
				h = obstacles[j].y - obstacles[i].y + 1;
				obstacles[j].n -= (obstacles[i].n * paths(h, w)) % MOD;
				if (obstacles[j].n < 0) obstacles[j].n += MOD;
			}
		}
	}
}

int main(){
	LL n;
	int x, y;

	make_pecto();
	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> M >> K;

		obstacles.clear();
		for (int i = 1; i <= K; i++){
			cin >> y >> x;
			if (x > M || x < 0 || y > N || y < 0) continue;
			obstacles.push_back(obstacle(x, y, paths(y, x)));
		}
		obstacles.push_back(obstacle(M, N, paths(N, M)));
		sort(obstacles.begin(), obstacles.end());

		cut_paths();

		printf("Case #%d\n", t);
		cout << obstacles[K - 1].n << endl;
	}

	return 0;
}