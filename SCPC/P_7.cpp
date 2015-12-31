#include <cstdio>
#include <iostream>
#include <set>
using namespace std;

set<int> q[3];
int T, N, result;

void reset(){
	result = 0;
	for (int i = 0; i < 3; i++) q[i].clear();
}

void addNums(int n, int data){
	set<int>::const_iterator iter;
	pair<set<int>::iterator, bool> pr;
	
	pr = q[n].insert(data);
	if (n == 2 || pr.second == false) return;

	for (iter = q[0].begin(); iter != q[0].end(); ++iter){
		addNums(n + 1, data + *iter);
	}
}

int main(){
	set<int>::iterator iter;
	int input;

	cin >> T;
	for (int t = 1; t <= T; t++){

		reset();
		cin >> N;

		for (int i = 1; i <= N; i++){
			cin >> input;
			iter = q[2].find(input);
			if (iter != q[2].end())
				result++;
			addNums(0, input);
		}

		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}