#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct POS{
	int x;
	int y;
public:
	POS(int x, int y) : x(x), y(y) {}
	bool operator < (const POS &a) const {
		return x < a.x;
	}
};

vector<POS> S;
int P[100005];
int M, N, L, result;

int isTrue(POS s, int hx){
	if (abs(P[hx] - s.x) + s.y <= L) return 1;
	return 0;
}

void search(){
	int hunter = 0, ship = 0;

	while (1){
		if (isTrue(S[ship], hunter)){
			result++;
			ship++;
		}
		else{
			if (abs(S[ship].x - P[hunter + 1]) < abs(S[ship].x - P[hunter])) hunter++;
			else ship++;
		}
		if (ship >= N || hunter >= M) break;
	}
}

int main(){

	int x, y, t;
	cin >> M >> N >> L;

	for (int i = 0; i < M; i++)
		cin >> P[i];
	sort(P, P + M);

	for (int i = 1; i <= N; i++){
		cin >> x >> y;
		S.push_back(POS(x, y));
	}
	sort(S.begin(), S.end());

	search();

	cout << result << endl;

	return 0;
}