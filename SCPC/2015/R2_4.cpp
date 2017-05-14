#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// Fail

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
int T, N, D[100005], H[100005], start;

void pushSector(int n, int pIdx){
	
	int isTrue = 1;
	if (H[pIdx] == start) return;
	H[pIdx] = start;
	if (sector[n].a < sector[pIdx].a) return;
	if (sector[n].b > sector[pIdx].b) return;

	vector<int>::iterator iter;
	for (iter = ptree[pIdx].begin(); iter != ptree[pIdx].end(); ++iter){
		if (sector[n].a < sector[*iter].a) continue;
		if (sector[n].b > sector[*iter].b) continue;
		isTrue = 0;
		pushSector(n, *iter);
	}
	if (isTrue) ptree[pIdx].push_back(n);
}

int calcMax(int n){
	int temp, max = 0;

	if (D[n]) return D[n];

	vector<int>::iterator iter;
	for (iter = ptree[n].begin(); iter != ptree[n].end(); ++iter){
		temp = calcMax(*iter);
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
		memset(H, 0, sizeof(H));
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
			start = i;
			pushSector(i, 0);
		}
		calcMax(0);
		printf("Case #%d\n", t);
		cout << D[0] - 1 << endl;
	}

	return 0;
}