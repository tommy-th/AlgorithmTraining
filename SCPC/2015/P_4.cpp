#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define PI 3.141592

static int scores[20] = { 6, 13, 4, 18, 1, 20, 5, 12, 9, 14, 11, 8, 16, 7, 19, 3, 17, 2, 15, 10 };
int A, B, C, D, E;
int T, N; 

int main(){

	double theta, r;
	int x, y, s, result;

	cin >> T;
	for (int t = 1; t <= T; t++){
		result = 0;
		cin >> A >> B >> C >> D >> E; 
		cin >> N;
		for (int i = 1; i <= N; i++){
			cin >> x >> y;
			r = sqrt((x*x + y*y));
			theta = atan2(y, x) * 180 / PI;
			if (theta < 0) theta += 360;
			theta += 9;
			if (theta >= 360) theta -= 360;
			s = theta / 18;

			if (r <= A) result += 50;
			else if (r >= B && r <= C) result += 3 * scores[s];
			else if (r >= D && r <= E) result += 2 * scores[s];
			else if (r <= E) result += scores[s];
		}

		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}