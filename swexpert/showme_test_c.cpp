#include <iostream>

using namespace std;

int dp[3][16] = {0, };

int calcCases(int t, int days) {
  if (days <= 0) {
    return 0;
  }
  if (dp[t][days] > 0) {
    return dp[t][days];
  }

  int cases = 0;
  if (t == 0) {
    cases += (2 * max(1, calcCases(0, days - 1)));
    cases += calcCases(1, days-1);
    cases += calcCases(2, days-1);
  } else if (t == 1) {
    cases += (1 * max(1, calcCases(0, days - 1)));
    cases += calcCases(2, days-1);
  } else {
    cases += (1 * max(1, calcCases(0, days - 1)));
    cases += calcCases(1, days-1);
  }

  dp[t][days] = cases;
  return cases;
}

int main() {
  int N;
  cin >> N;
  cout << calcCases(0, N) << endl;

  return 0;
}
