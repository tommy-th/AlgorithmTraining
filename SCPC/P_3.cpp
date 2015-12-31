#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int T, N, K;
vector<int> scores;

int main(){

	int score, result;

	cin >> T;
	for (int t = 1; t <= T; t++){
		
		cin >> N >> K;
		scores.clear(); 
		result = 0;
		for (int i = 1; i <= N; i++){
			cin >> score;
			scores.push_back(score);
		}
		sort(scores.begin(), scores.end(), greater<int>());

		for (int i = 0; i < K; i++) result += scores[i];

		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}