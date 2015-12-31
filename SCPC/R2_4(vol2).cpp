#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct stick{
	int a, b;
	stick(){}
	stick(int a, int b) : a(a), b(b){}
	bool operator < (const stick& oth) const{
		return a < oth.a || (a == oth.a && b > oth.b);
	}
};

vector<int> ptree[100005];
vector<stick> sector;
int T, N, D[100005], P[100005];

void pushSector(int n, int pIdx){

	int grandParent = P[pIdx];

	vector<int>::iterator iter;
	for (iter = ptree[grandParent].begin(); iter != ptree[grandParent].end(); ++iter){
		int next = *iter;
		if (next == pIdx) continue;
		if (next == n) continue;
		if (sector[n].a < sector[next].a) continue;
		if (sector[n].b > sector[next].b) continue;
		ptree[next].push_back(n);
	}
}

int calcMax(int n){
	int temp, max = 0;

	if (D[n]) return D[n];

	vector<int>::iterator iter;
	for (iter = ptree[n].begin(); iter != ptree[n].end(); ++iter){
		int next = *iter;
		temp = calcMax(next);
		if (temp > max) max = temp;
	}

	D[n] = max + 1;

	return D[n];
}

int main(){

	int min, max;
	int a, b;

	cin >> T;

	for (int t = 1; t <= T; t++){
		cin >> N;
		for (int i = 0; i <= N; i++){
			ptree[i].clear();
		}
		memset(D, 0, sizeof(D));
		memset(P, 0, sizeof(P));
		sector.clear();
		min = 99999999;
		max = -99999999;
		for (int i = 1; i <= N; i++){
			cin >> a >> b;
			sector.push_back(stick(a, b));
			if (a < min) min = a;
			if (b > max) max = b;
		}
		sector.push_back(stick(min, max));
		sort(sector.begin(), sector.end());

		for (int i = 1; i < sector.size(); i++){
			for (int j = i - 1; j >= 0; j--){
				if (sector[j].a <= sector[i].a) {
					if (sector[j].b >= sector[i].b) {
						P[i] = j; 
						ptree[j].push_back(i);
						break;
					}
				}
			}
		}

		for (int i = 1; i < sector.size(); i++){
			pushSector(i, P[i]);
		}

		calcMax(0);
		printf("Case #%d\n", t);
		cout << D[0] - 1 << endl;
	}

	return 0;
}