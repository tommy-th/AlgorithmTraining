#include <iostream>
using namespace std;

char target[105];
int K, L, S, H[1005];

int max(){
	int result = 1, p, t, len = strlen(target);

	p = len;
	for (int i = 1; i < len; i++){
		t = 0;
		while (target[t] == target[i + t] && i + t < len) t++;
		if (i + t == len){
			p = i;
			break;
		}
	}
	result += (int)((S - L) / (L - (len - p)));
	return result;
}

double answer(){

	double s = 1, temp;

	for (int i = 0; i < strlen(target); i++){
		temp = H[target[i] - 'A' + 1];
		temp /= H[0];
		s *= temp;
	}
	s *= (S - L + 1);

	return s;
}

int main(){
	
	FILE *fin = freopen("B-large-practice.in", "r", stdin);
	FILE *fout = freopen("B-large-practice.out", "w", stdout);
	
	double result;
	char temp;
	int t, ans, on;

	cin >> t;
	for (int i = 1; i <= t; i++){
		cin >> K >> L >> S;
		memset(H, 0, sizeof(H));
		for (int j = 1; j <= K; j++){
			cin >> temp;
			H[(int)(temp - 'A') + 1]++;
			H[0]++;
		}
		cin >> target;
		on = 1;
		for (int j = 0; j < L; j++){
			if (H[target[j] - 'A' + 1] == 0) on = 0;
		}
		if (on) result = max() - answer();
		else result = 0.0;
		printf("Case #%d: %.10lf\n", i, result);
	}

	return 0;
}