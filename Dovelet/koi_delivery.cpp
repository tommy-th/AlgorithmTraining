#include <iostream>
using namespace std;

typedef struct __point{
	int a;
	int b;
	int c;
} point;

point hTree[10005], vInfo[10005];

int N, C, M;
int H[2005], truck[2005], curVolume, result;

void push_point(int n){
	point temp;

	while (n > 1){
		if (hTree[n].a <= hTree[n / 2].a){
			if (hTree[n].b < hTree[n / 2].b || hTree[n].a < hTree[n / 2].a){
				temp = hTree[n];
				hTree[n] = hTree[n / 2];
				hTree[n / 2] = temp;
				n /= 2;
			}
			else break;
		}
		else break;
	}
}

point pop_point(int n){
	int cur = 1, next;
	point temp, result = hTree[1];

	hTree[1] = hTree[n];
	while (cur * 2 <= n - 1){

		next = cur * 2;
		if (next + 1 <= n - 1){
			if (hTree[next + 1].a < hTree[next].a) next++;
			else if (hTree[next + 1].a == hTree[next].a && hTree[next + 1].b < hTree[next].b) next++;
		}

		if (hTree[cur].a >= hTree[next].a){
			if (hTree[cur].b > hTree[next].b || hTree[cur].a > hTree[next].a){
				temp = hTree[cur];
				hTree[cur] = hTree[next];
				hTree[next] = temp;
				cur = next;
			}
			else break;
		}
		else break;
	}
	return result;
}

void search_point(int n){
	int cur = H[n];

	result += truck[n];
	curVolume -= truck[n];
	truck[n] = 0;

	while (vInfo[cur].a == n){
		curVolume += vInfo[cur].c;
		truck[vInfo[cur].b] += vInfo[cur].c;
		cur++;
	}
	cur = N;
	while (curVolume > C){
		curVolume -= truck[cur];
		if (curVolume < C){
			truck[cur] = C - curVolume;
			curVolume = C;
		}
		else{
			truck[cur] = 0;
		}
		cur--;
	}
}


int main(){

	int curPoint = 0;
	cin >> N >> C >> M;

	for (int i = 1; i <= M; i++){
		cin >> hTree[i].a >> hTree[i].b >> hTree[i].c;
		push_point(i);
	}
	for (int i = 1; i <= M; i++){
		vInfo[i] = pop_point(M - i + 1);
		if (vInfo[i].a != curPoint){
			H[vInfo[i].a] = i;
			curPoint = vInfo[i].a;
		}
	}

	for (int i = 1; i <= N; i++){
		search_point(i);
	}
	cout << result << endl;

	return 0;
}