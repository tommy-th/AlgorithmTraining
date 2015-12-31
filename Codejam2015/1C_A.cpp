#include <iostream>
using namespace std;

int R, C, W;

int main(){
	FILE *fin = freopen("A-small-practice.in", "r", stdin);
	FILE *fout = freopen("A-small-practice.out", "w", stdout);

	int t, ans;

	cin >> t;
	for (int i = 1; i <= t; i++){
		cin >> R >> C >> W;
		ans = (R - 1)*(C / W);
		ans += W;
		if (C % W) ans += C / W;
		else ans += (C / W - 1);
		cout << "Case #" << i << ": " << ans << endl;
	}

	return 0;
}