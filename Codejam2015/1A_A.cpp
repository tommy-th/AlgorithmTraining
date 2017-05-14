#include <iostream>
#include <cassert>
#define MIN(a,b) ((a) < (b) ? (a) : (b))
using namespace std;

int N, mash[100005], max;

int method1(){
	int result = 0;
	max = 0;
	for (int i = 1; i <= N; i++){
		if (mash[i - 1] - mash[i] > 0){
			result += mash[i - 1] - mash[i];
			if (mash[i - 1] - mash[i] > max) max = mash[i - 1] - mash[i];
		}
	}
	return result;
}

int method2(){
	int result = 0;

	for (int i = 1; i < N; i++){
		result += MIN(mash[i], max);
	}
	return result;
}

int main(){

	FILE *fin = freopen("A-large-practice.in", "r", stdin);
	assert(fin != NULL);
	FILE *fout = freopen("A-large-practice.out", "w", stdout);

	int t;

	cin >> t;

	for (int i = 1; i <= t; i++){
		cin >> N;
		for (int j = 1; j <= N; j++){
			cin >> mash[j];
		}
		cout << "Case #" << i << ": " << method1() << " ";
		cout << method2() << endl;
	}

	return 0;
}