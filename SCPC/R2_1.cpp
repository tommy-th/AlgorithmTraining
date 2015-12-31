#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

#define LL long long
#define MOD 1000000007
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

vector<LL> nums;
set<LL> difs;
LL arr[100005];
int T, N;

void childs(LL n){
	nums.clear();
	for (LL i = 1; i <= sqrt(n); i++){
		if (n % i == 0){
			nums.push_back(i);
			if (n / i != i) nums.push_back(n / i);
		}
	}
}

int main(){
	
	int on;
	LL result;

	cin >> T;

	for (int t = 1; t <= T; t++){
		
		cin >> N; 
		for (int i = 1; i <= N; i++){
			cin >> arr[i];
		}
		difs.clear();
		for (int i = 2; i <= N; i++){
			difs.insert(arr[i] - arr[i - 1]);
		}

		set<LL>::iterator first;
		vector<LL>::iterator iter2;

		first = difs.begin();

		printf("Case #%d\n", t);

		if (*first == 0){
			if (difs.size() > 1) cout << "0" << endl;
			else cout << "1" << endl;
		}
		else{
			result = 0;
			childs(*first);
			for (iter2 = nums.begin(); iter2 != nums.end(); ++iter2){
				on = 1;
				for (set<LL>::iterator iter = difs.begin(); iter != difs.end(); ++iter){
					if (*iter % *iter2 != 0){
						on = 0;
						break;
					}
				}
				if (on) result++;
			}
			cout << result << endl;
		}
	}

	return 0;
}