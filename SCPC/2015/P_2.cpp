#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>     
using namespace std;

vector<int> people;
int T, N;

int main(){

	int score, max, result;

	cin >> T;
	for (int t = 1; t <= T; t++){

		cin >> N;
		max = result = 0;
		people.clear();
		for (int i = 1; i <= N; i++){
			cin >> score;
			people.push_back(score);
		}
		sort(people.begin(), people.end());

		for (int i = 0; i < N; i++) {
			people[i] += (N - i);
			if (people[i]>max) max = people[i];
		}
		for (int i = 0; i < N; i++)
			if (people[i] + i >= max) result++;
		
		printf("Case #%d\n", t);
		cout << result << endl;
	}

	return 0;
}