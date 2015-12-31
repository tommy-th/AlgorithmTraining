#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct __dot{
	int n, p;
	__dot(){ n = 0, p = 0; }
	__dot(int in, int ip){ n = in, p = ip; }
	bool operator < (const __dot & oth) const {
		return oth.p > p;
	}
}DOT;

int H[105], N, M, T, K, rx, ry, result;
vector<DOT> dotx, doty;

void search_col(int sx){
	int temp;
	for (int i = 0; i < doty.size(); i++){
		int sy = doty[i].p;
		int j = i;
		temp = 0;
		while (doty[j].p <= sy + K){
			if(H[doty[j].n]) temp++;
			j++;
			if (j >= doty.size()) break;
		}
		if (temp > result){
			result = temp;
			rx = sx, ry = sy + K;
		}
	}
}
void search_row(){
	for (int i = 0; i < dotx.size();){
		int sx = dotx[i].p;
		int j = i;
		while (dotx[j].p <= sx + K){
			H[dotx[j].n] = 1;
			j++;
			if (j >= dotx.size()) break;
		}
		search_col(sx);
		while (sx == dotx[i].p){
			H[dotx[i].n] = 0;
			i++;
			if (i >= dotx.size()) break;
		}
	}
}

int main(){

	int x, y;
	cin >> N >> M >> T >> K;

	for (int i = 1; i <= T; i++){
		cin >> x >> y;
		dotx.push_back(DOT(i, x));
		doty.push_back(DOT(i, y));
	}
	sort(dotx.begin(), dotx.end());
	sort(doty.begin(), doty.end());
	search_row();
	cout << rx << " " << ry << endl << result << endl;

	return 0;
}