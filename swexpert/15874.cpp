#include <iostream>
#include <vector>

using namespace std;

using LL = long long int;

int p[2005] = {0, };

int calcPercent(int N, int K, int MOD) {
  memset(p, 0, 2001);
  p[0] = 1;

  int k = 0;
  for (int i = 1; i <= N; ++i) {
    k = min(K, k + 1);
    for (int j = k; j > 0; --j) {
      LL sum = (LL)(p[j-1]) * i + p[j];
      p[j] = sum % MOD;
    }
  }

  return p[K];
}


int main(int argc, char** argv) {
  int test_case;
  int T, N, K, MOD;
  cin>>T;

  for(test_case = 1; test_case <= T; ++test_case) {
    cin >> N >> K >> MOD;
    cout << "#" << test_case << " " << calcPercent(N, K, MOD) << endl;
  }

  return 0;
}