#include <iostream>
#include <cassert>

using namespace std;

long long int time, to, from;
int barder[1005];
int B, N, max, result;

void astermate(){
	long long int nums;

	to = 0; from = 100000000000000;
	time = from / 2;
	while (1){
		nums = 0;
		for (int i = 1; i <= B; i++){
			nums += time / barder[i];
			if (time % barder[i] != 0) nums++;
		}
		if (nums >= N){
			from = time;
			time = (from + to) / 2;			
		}
		else{
			to = time;
			time = (from + to) / 2;
			if (to == time) 
				break;
		}
	}
}

void solve(){
	int on = 1;
	long long int nums = 0;

	for (int i = 1; i <= B; i++){
		nums += time / barder[i];
		if (time % barder[i] != 0) nums++;
	}

	while (on){
		time++;
		for (int i = 1; i <= B; i++){
			if ((time-1) % barder[i] == 0) nums++;
			if (nums == N) {
				result = i;
				on = 0;
				break;
			}
		}
	}

}

int main(){
//	
//	FILE *fin = freopen("B-large-practice.in", "r", stdin);
//	assert(fin != NULL);
//	FILE *fout = freopen("B-large-practice.out", "w", stdout);
//	
	int t;
	cin >> t;

	for (int i = 1; i <= t; i++){
		cin >> B >> N;
		max = 0;
		for (int j = 1; j <= B; j++){
			cin >> barder[j];
			if (barder[j] > max) max = barder[j];
		}
		astermate();
		solve();
		cout << "Case #" << i << ": " << result << endl;
	}



	return 0;
}