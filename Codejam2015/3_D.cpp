#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define LL long long
#define FOR(i, n) for(int i = 1; i <= n; i++)
#define FORS(i, s, n) for(int i = s; i <= n; i++)
#define FORL(i, n) for(int i = n; i >= 1; i--)

int T, P;
LL X, E[10005], F[10005];
vector<LL> ans;

void eraseNum(LL d){
	LL m;
	FOR(i, P){
		if (F[i]){
			if (d > 0){
				m = F[i];
				FORS(j, i + 1, P){
					if (F[j] && E[i]+d == E[j]){
						if (F[j] >= m) F[j] -= m;
						else F[j] = 0;
						break;
					}
				}
			}
			else F[i] /= 2;
		}
	}
	return;
}

int findMagn(){
	int on = 0;
	LL x, y;

	FORL(i, P){
		if (F[i]) {
			x = E[i]; 
			FORL(j, i){
				if (i == j && F[j] > 1) {
					y = E[j]; on = 1; break;
				}
				else if (i != j && F[j]) {
					y = E[j]; on = 1; break;
				}
			}
			break;
		}
	}
	if (on){
		ans.push_back(x - y);
		eraseNum(x - y);
	}
	return on; 
}

void findSign(LL match){
	int on = 0;
	vector<int> list;
	map<LL, int> D, temp;
	if (match > 0){
		D.insert(map<LL, int>::value_type(ans[0], 0));
		if (ans[0] == match) on = 1;
		FOR(i, ans.size() - 1){
			temp.clear();
			temp.insert(map<LL, int>::value_type(ans[i], i)); 
			if (ans[i] == match) on = 1;
			for (map<LL, int>::iterator iter = D.begin(); iter != D.end(); ++iter){
				if (iter->first + ans[i] > match) break;
				temp.insert(map<LL, int>::value_type(iter->first + ans[i], i));
				if (iter->first + ans[i] == match) on = 1;
				if (on) break;
			}
			for (map<LL, int>::iterator iter = temp.begin(); iter != temp.end(); ++iter){
				D.insert(map<LL, int>::value_type(iter->first, iter->second));
			}
			if (on) break;
		}

		map<LL, int>::iterator iter = D.find(match);
		while (iter->first != ans[iter->second]){
			list.push_back(iter->second);
			iter = D.find(iter->first - ans[iter->second]);
		}
		list.push_back(iter->second);
		for (int i = 0; i < list.size(); i++){
			ans[list[i]] *= -1;
		}
	}
	for (int i = 0; i < ans.size(); i++){
		ans[i] *= -1;
	}
	return;
}

int main(){
	
	FILE *fin = freopen("D-large-practice.in", "r", stdin);
	FILE *fout = freopen("D-large-practice.out", "w", stdout);
	
	cin >> T;

	FOR(t, T){
		cin >> P;

		ans.clear();

		FOR(i, P) cin >> E[i];
		FOR(i, P) cin >> F[i];
		X = E[P];

		while (findMagn());

		findSign(X);

		cout << "Case #" << t << ": ";

		std::sort(ans.begin(), ans.end());

		FOR(i, ans.size()) cout << ans[i - 1] << " "; 

		cout << endl;
		fprintf(stderr, "Case #%d done\n", t);
	}
	return 0;
}