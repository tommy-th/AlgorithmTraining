#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200005;
int N;

int ESCAPE_EARNING = 1200000000;
int ESCAPE_EARNING_THRESHOLD = 1000000000;

struct Investment{
  int holding;
  int earning;
  Investment() : holding(0), earning(0) {}
  Investment(int holding, int earning) : holding(holding), earning(earning) {}
}__attribute__((packed, aligned(1)));

bool investmentCompare(const Investment &lhs, const Investment &rhs) {
  return lhs.holding < rhs.holding or (lhs.holding == rhs.holding and lhs.earning > rhs.earning);
}

int tree[MAX_N];
int earnings[MAX_N];
int costs[MAX_N];
int maxCosts[MAX_N];
int nodeOrderLen;
int nodeOrder[MAX_N];
vector<int> children[MAX_N];

int totalInvestmentIndex;
int totalInvestmentStart[MAX_N];
int totalInvestmentEnd[MAX_N];
Investment totalInvestments[MAX_N];


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
  int childrenLen = children[node].size();
  int childInvestmentStart = children[node].empty() ? totalInvestmentIndex : totalInvestmentStart[children[node][0]];
  int childInvestmentEnd = children[node].empty() ? totalInvestmentIndex : totalInvestmentEnd[children[node][childrenLen - 1]];

  if (childInvestmentEnd > childInvestmentStart and childrenLen > 1) {
    std::sort(totalInvestments + childInvestmentStart,
         totalInvestments + childInvestmentEnd,
         investmentCompare);
  }

  int cost = costs[node];
  int holdings = cost;
  int earningSum = earnings[node] - cost;
  int accumEarning = earningSum;

  totalInvestmentIndex = childInvestmentStart;
  for (int i=childInvestmentStart; i<childInvestmentEnd; ++i) {
    auto& investment = totalInvestments[i];
    if (accumEarning < 0 or holdings + accumEarning >= investment.holding) {
      earningSum += investment.earning;
    } else {
      auto newInvestment = Investment(holdings, earningSum);
      holdings = investment.holding;
      earningSum = investment.earning;
      totalInvestments[totalInvestmentIndex++] = newInvestment;
    }
    accumEarning += investment.earning;
  }

  if (earningSum > 0) {
    totalInvestments[totalInvestmentIndex++] = Investment(holdings, earningSum);
  }

  totalInvestmentStart[node] = childInvestmentStart;
  totalInvestmentEnd[node] = totalInvestmentIndex;
}

void initAndGetInputs() {
  totalInvestmentIndex = 0;
  for (int i=0; i<N; ++i) {
    children[i] = vector<int>();
  }

  int parent, earning, cost;
  for (int node=1; node<N; ++node) {
    scanf("%d%d%d", &parent, &earning, &cost);
    earnings[node] = earning == -1 ? ESCAPE_EARNING : earning;
    costs[node] = cost;
    children[parent].push_back(node);
  }
}

void initWithDummyInputs() {
  totalInvestmentIndex = 0;
  for (int i=0; i<N; ++i) {
    children[i] = vector<int>();
  }

  int parent;
  for (int node=1; node<N; ++node) {
    parent = rand() % node;
    costs[node] = rand() % 1000;
    earnings[node] = rand() % 1000;
    children[parent].push_back(node);
  }

  earnings[N-1] = ESCAPE_EARNING;
}


void buildLeafFirstOrderTree() {
  int treeIdx = 0;
  tree[treeIdx++] = 0;

  nodeOrderLen = 0;
  while(treeIdx > 0) {
    int node = tree[--treeIdx];
    nodeOrder[nodeOrderLen++] = node;

    for (const auto &child : children[node]) {
      if (node != child) {
        tree[treeIdx++] = child;
      }
    }
  }
}

int findMaxSearchHoldings() {
  for (int i=nodeOrderLen - 1; i>=0; --i) {
    buildMaxCost(nodeOrder[i]);
  }
  return maxCosts[0] + 1;
}

void printInvestmentNodes(const int node) {
  cout << endl << node << endl;

  for (int i = totalInvestmentStart[node]; i<totalInvestmentEnd[node]; ++i) {
    const auto& investment = totalInvestments[i];
    cout << investment.holding << " " << investment.earning << endl;
  }
  cout << endl;
}

int findMinSearchHoldings() {
  for (int i=nodeOrderLen - 1; i>=0; --i) {
    buildInvestments(nodeOrder[i]);
  }

  int holding = 0;
  int accumEarnings = 0;
  for (int i = totalInvestmentStart[0]; i<totalInvestmentEnd[0]; ++i) {
    const auto& investment = totalInvestments[i];
    if (investment.earning > ESCAPE_EARNING_THRESHOLD) {
      if (holding + accumEarnings >= investment.holding) {
        return holding;
      } else {
        return investment.holding - accumEarnings;
      }
    } else {
      holding = investment.holding;
      accumEarnings += investment.earning;
    }
  }
  return -1;
}

int main(int argc, char** argv) {
  int test_case;
  int T;
  cin>>T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N;
    initAndGetInputs();
    buildLeafFirstOrderTree();

    cout << "#" << test_case << " " << findMaxSearchHoldings() << " " << findMinSearchHoldings() << endl;
  }

  return 0;
}
