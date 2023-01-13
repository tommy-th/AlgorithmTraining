#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_N = 200005;
int N;

int ESCAPE_EARNING = 1200000000;
int ESCAPE_EARNING_THRESHOLD = 1000000000;

struct Investment{
  int holding;
  int earning;
  Investment(int holding, int earning) : holding(holding), earning(earning) {}
};

int earnings[MAX_N];
int costs[MAX_N];
int maxCosts[MAX_N];
int nodeOrderLen;
int nodeOrder[MAX_N];
vector<int> children[MAX_N];
vector<Investment> totalChildInvestments;
int investmentNodeStartIndex[MAX_N];
vector<Investment> investmentNodes[MAX_N];


void buildMaxCost(const int node) {
  int childMaxCost = 0;

  for (int child : children[node]) {
    childMaxCost += maxCosts[child];
  }

  int cost = costs[node];
  int earning = earnings[node];

  maxCosts[node] = max(max(0, cost - 1), cost - earning + childMaxCost);
}

void buildInvestments(const int node) {
  totalChildInvestments.clear();

  for (int child : children[node]) {
    auto& childInvestments = investmentNodes[child];

    if (investmentNodeStartIndex[child] < childInvestments.size()) {
      totalChildInvestments.insert(
          totalChildInvestments.end(),
          childInvestments.begin() + investmentNodeStartIndex[child],
          childInvestments.end());
    }
  }

  std::sort(totalChildInvestments.begin(), totalChildInvestments.end(),
            [](const auto& lhs, const auto& rhs) {
    return lhs.holding < rhs.holding or (lhs.holding == rhs.holding and lhs.earning > rhs.earning);
  });

  int holdings = 0;
  int earningSum = earnings[node];
  int accumEarning = earningSum;
  auto& investments = investmentNodes[node];

  for (const auto& investment : totalChildInvestments) {
    if (holdings + accumEarning >= investment.holding) {
      earningSum += investment.earning;
    } else {
      investments.emplace_back(holdings, earningSum);
      holdings = investment.holding;
      earningSum = investment.earning;
    }
    accumEarning += investment.earning;
  }
  investments.emplace_back(holdings, earningSum);

  int cost = costs[node];
  int si = 0;

  if (cost > 0) {
    accumEarning = -cost;

    for (; si < investments.size(); ++si) {
      if (accumEarning < 0) {
        accumEarning += investments[si].earning;
      }
      if (accumEarning >= 0) {
        break;
      }
    }

    if (accumEarning >= 0) {
      investments[si].holding += cost;
      investments[si].earning = accumEarning;
    }
  }

  investmentNodeStartIndex[node] = si;
}

void initAndGetInputs() {
  for (int i=0; i<N; ++i) {
    children[i].clear();
    investmentNodes[i].clear();
  }

  int parent, earning, cost;
  for (int node=1; node<N; ++node) {
    cin >> parent >> earning >> cost;
    earnings[node] = earning == -1 ? ESCAPE_EARNING : earning;
    costs[node] = cost;
    children[parent].push_back(node);
  }
}

void buildLeafFirstOrderTree() {
  queue<int> q;
  q.push(0);

  nodeOrderLen = 0;
  while(not q.empty()) {
    int node = q.front(); q.pop();
    nodeOrder[nodeOrderLen++] = node;

    for (const auto &child : children[node]) {
      q.push(child);
    }
  }
}

int findMaxSearchHoldings() {
  for (int i=nodeOrderLen - 1; i>=0; --i) {
    buildMaxCost(nodeOrder[i]);
  }
  return maxCosts[0] + 1;
}

int findMinSearchHoldings() {
  for (int i=nodeOrderLen - 1; i>=0; --i) {
    buildInvestments(nodeOrder[i]);
  }

  int accumEarnings = 0;

  for (int i = investmentNodeStartIndex[0]; i<investmentNodes[0].size(); ++i) {
    const auto& investment = investmentNodes[0][i];
    if (investment.earning > ESCAPE_EARNING_THRESHOLD) {
      return investment.holding - accumEarnings;
    } else {
      accumEarnings += investment.earning;
    }
  }
}

void printInvestmentNodes(const int node) {
  auto& investmentNode = investmentNodes[node];
  cout << endl << node << endl;

  for (int i = investmentNodeStartIndex[node]; i<investmentNode.size(); ++i) {
    const auto& investment = investmentNode[i];
    cout << investment.holding << " " << investment.earning << endl;
  }
  cout << endl;
}

void initWithDummyInputs() {
  for (int i=0; i<N; ++i) {
    children[i].clear();
    investmentNodes[i].clear();
  }

  for (int node=1; node<N - 500; ++node) {
    costs[node] = 1;
    earnings[node] = 1;
    children[node-1].push_back(node);
  }

  int cost = 1;
  int earning = 2;

  for (int node=N-500; node<N; ++node) {
    costs[node] = cost;
    earnings[node] = earning;
    children[N-501].push_back(node);
    cost += 2;
    earning += 2;
  }

  earnings[N-1] = ESCAPE_EARNING;
}

int main(int argc, char** argv) {
  int test_case;
  int T;
  cin>>T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N;
    initAndGetInputs();
//    N = 200000;
//    initWithDummyInputs();
    buildLeafFirstOrderTree();

    cout << "#" << test_case << " " << findMaxSearchHoldings() << " " << findMinSearchHoldings() << endl;
  }

  return 0;
}
