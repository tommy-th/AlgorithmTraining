#include <iostream>
using namespace std;

int N, L;
int len[3005], dir[3005], gap[3005];
int t, s = 1;

int main(){

	cin >> N >> L;

	for (int i = 1; i <= N; i++){
		cin >> len[i] >> dir[i];
		if (dir[i]){
			dir[i] = -1;
			gap[i] = L - len[i];
		}
		else dir[i] = 1; 
	}

	while (s < N){
		int on = 1;
		while (on){
			if (len[s + 1] + gap[s + 1] < gap[s]) on = 0;
			if (len[s] + gap[s] < gap[s + 1]) on = 0;
			if (on) s++;
		}
		for (int i = s; i <= N; i++){
			if (len[i] + dir[i] + gap[i] > L) dir[i] *= -1;
			else if (len[i] + dir[i] + gap[i] < 0) dir[i] *= -1;
			gap[i] += dir[i];
		}
		t++;
	}

	if (N == 1) cout << "0" << endl;
	else cout << t-1 << endl;

	return 0;
}