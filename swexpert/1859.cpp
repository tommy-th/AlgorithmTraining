#include <iostream>
#include <stack>

using namespace std;

using LL = long long int;

int prices[1000005] = {0, };

stack<int> buildSellingPoints(int N) {
  stack<int> sellingPoints;

  int maxPrice = 0;

  for (int i = N - 1; i >= 0; --i) {
    if (prices[i] > maxPrice) {
      maxPrice = prices[i];
      sellingPoints.push(i);
    }
  }

  return sellingPoints;
}

LL perfectTrading(int N) {
  stack<int> sellingPoints = buildSellingPoints(N);

  LL profitSum = 0;
  int point = sellingPoints.top();
  for (int i = 0; i<N; ++i) {
    if (i == point) {
      sellingPoints.pop();
      if (sellingPoints.empty())
        break;
      point = sellingPoints.top();
    } else {
      profitSum += (prices[point] - prices[i]);
    }
  }
  return profitSum;
}

int main(int argc, char** argv) {
  int test_case;
  int T, N;
  cin>>T;

  for(test_case = 1; test_case <= T; ++test_case) {
    cin >> N;

    for (int i = 0; i<N; ++i) {
      cin >> prices[i];
    }
    cout << "#" << test_case << " " << perfectTrading(N) << endl;
  }

  return 0;
}