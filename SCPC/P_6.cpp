#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

#define LL long long

int T, N, K;
LL result, table[200005];

void set_table(){
	for (int i = 1; i <= N; i++){
		table[i] = table[i - 1] + i;
	}
	for (int i = N + 1; i <= 2 * N - 1; i++){
		table[i] = table[i - 1] + 2 * N - i;
	}
}

LL roomNum(int y, int x){
	int d = x + y - 1;
	LL ret = table[d];

	if (d % 2 == 0) {
		if (d > N) ret -= (x - 1 - d + N);
		else ret -= (x - 1);
	}
	else{
		if (d > N) ret -= (y - 1 - d + N);
		else ret -= (y - 1);
	}

	return ret;
}

void search(string track){
	int x, y;
	x = y = 1;

	result += roomNum(y, x);
	for (int i = 0; i < K; i++){
		if (track[i] == 'D') y++;
		else if (track[i] == 'R') x++;
		else if (track[i] == 'U') y--;
		else if (track[i] == 'L') x--;
		result += roomNum(y, x);
	}
}

int main(){

	string input;

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> K;
		cin >> input;

		result = 0;
		set_table();
		search(input);
		
		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}