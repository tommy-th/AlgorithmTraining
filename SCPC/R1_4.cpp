#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// Fail

#define INF 100000005
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct __line{
	int a, b;
	__line(){ a = b = 0; }
	__line(int a, int b) :a(a), b(b) {}
	bool operator < (const __line& oth) const{
		return a < oth.a || (a == oth.a && b < oth.b);
	}
}line;

vector<line> lineCol, lineRow;
int width, height;
int T, N;

void reset(){
	width = height = INF;
	lineCol.clear();
	lineRow.clear();
}

void searchDir(vector<line> lines, int dir){
	int p1, p2, lim = INF;

	p2 = lines[N - 1].a;
	lim = lines[0].b;
	for (int i = 0; i < N; i++){
		p1 = lines[i].a;
		if (p1 > lim){
			if (dir) width = MIN(width, p2 - lim);
			else height = MIN(height, p2 - lim);
			break;
		}
		if (dir)width = MIN(width, p2 - p1);
		else height = MIN(height, p2 - p1);
		if (lines[i].b < lim) lim = lines[i].b;
		if (lines[i].b > p2) p2 = lines[i].b;
	}
}

void print(){
	double result = MAX(width, height);
	cout << (double)result / 2 << endl;
}

int main(){
	int x1, x2, y1, y2;

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N;
		reset();
		for (int i = 1; i <= N; i++){
			cin >> x1 >> y1 >> x2 >> y2;
			lineCol.push_back(line(MIN(x1, x2), MAX(x1, x2)));
			lineRow.push_back(line(MIN(y1, y2), MAX(y1, y2)));
		}
		sort(lineCol.begin(), lineCol.end());
		sort(lineRow.begin(), lineRow.end());
		searchDir(lineCol, 1);
		searchDir(lineRow, 0);

		printf("Case #%d\n", t);
		print();
	}

	return 0;
}