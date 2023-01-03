#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int to;
  int xw;
  int yw;

  Edge(int to, int xw, int yw) : to(to), xw(xw), yw(yw) {}
};

struct Visit {
  int xwSum;
  int ywSum;

  Visit(int xw_sum, int yw_sum) : xwSum(xw_sum), ywSum(yw_sum) {}
};

int N, M, result;
vector<Edge> edges[25];
vector<Visit> visits[25];

void reset() {
  for (int i=0; i<=N; ++i) {
    edges[i].clear();
    visits[i].clear();
  }

  result = -1;
}

void searchNode(int node, int xwSum, int ywSum) {
  if (node == 2) {
    result = result < 0 ? xwSum * ywSum : min(result, xwSum * ywSum);
  }

  for (const auto& visit : visits[node]) {
    if (visit.xwSum <= xwSum and visit.ywSum <= ywSum) {
      return;
    }
  }
  visits[node].emplace_back(xwSum, ywSum);

  for (const auto &edge : edges[node]) {
    searchNode(edge.to, xwSum + edge.xw, ywSum + edge.yw);
  }
}

int main(int argc, char** argv) {
  int test_case;
  int T;
  cin>>T;

  int from, to, xw, yw;
  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N >> M;
    reset();

    for (int j=1; j<=M; ++j) {
      cin >> from >> to >> xw >> yw;
      edges[from].emplace_back(to, xw, yw);
      edges[to].emplace_back(from, xw, yw);
    }
    searchNode(1, 0, 0);

    cout << "#" << test_case << " " << result << endl;
  }

  return 0;
}