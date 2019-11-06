#include <iostream>
#include <vector>

using namespace std;


constexpr int mod = 42043;

int main() {
  int N, K, T;

  cin >> N >> K >> T;

  vector<vector<int>> keeps;
  vector<int> results = vector<int>(K+1, 0);

  int t;
  for (int i=0; i<T; i++) {
    cin >> t;
    if (t > K) continue;
    results[t] += 1;
  }

  while (N > 1) {
    if (N % 2 == 1) {
      keeps.push_back(results);
      N--;
    } else {
      vector<int> temp = vector<int>(K+1, 0);

      for (int i=0; i<=K; i++) {
        for (int j=0; i+j<=K; j++) {
          temp[i+j] = (temp[i+j] + (results[i] * results[j])) % mod;
        }
      }
      N /= 2;
      results = move(temp);
    }
  }

  for (const auto& keep : keeps) {
      vector<int> temp = vector<int>(K+1, 0);

      for (int i=0; i<=K; i++) {
        for (int j=0; i+j<=K; j++) {
          temp[i+j] = (temp[i+j] + (keep[i] * results[j])) % mod;
        }
      }
      results = move(temp);
  }

  int result = 0;
  for (int i=0; i<=K; i++) {
    result = (result + results[i]) % mod;
  }

  cout << result << endl;
}