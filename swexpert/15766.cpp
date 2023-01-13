#include <iostream>
#include <vector>
#include <stack>
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

int earnings[MAX_N];
int costs[MAX_N];
int maxCosts[MAX_N];
int nodeOrderLen;
int nodeOrder[MAX_N];
vector<int> children[MAX_N];

int totalInvestmentIndex;
int totalInvestmentStart[MAX_N];
int totalInvestmentLen[MAX_N];
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
  int childInvestmentStart = children[node].empty() ? totalInvestmentIndex : totalInvestmentStart[children[node][0]];
  int childInvestmentLen = 0;

  for (int child : children[node]) {
    childInvestmentLen += totalInvestmentLen[child];
  }

  if (childInvestmentLen > 0 and children[node].size() > 1) {
    sort(totalInvestments + childInvestmentStart,
         totalInvestments + childInvestmentStart + childInvestmentLen,
         investmentCompare);
  }

  int holdings = 0;
  int earningSum = earnings[node];
  int accumEarning = earningSum;

  totalInvestmentIndex = childInvestmentStart;
  for (int i=childInvestmentStart; i<childInvestmentStart + childInvestmentLen; ++i) {
    auto& investment = totalInvestments[i];
    if (holdings + accumEarning >= investment.holding) {
      earningSum += investment.earning;
    } else {
      auto newInvestment = Investment(holdings, earningSum);
      holdings = investment.holding;
      earningSum = investment.earning;
      totalInvestments[totalInvestmentIndex++] = newInvestment;
    }
    accumEarning += investment.earning;
  }
  totalInvestments[totalInvestmentIndex++] = Investment(holdings, earningSum);

  int cost = costs[node];
  int investmentOffset = 0;
  if (cost > 0) {
    accumEarning = -cost;

    for (int i=childInvestmentStart; i<totalInvestmentIndex; ++i) {
      auto& investment = totalInvestments[i];
      if (accumEarning < 0) {
        accumEarning += investment.earning;
        investmentOffset = i - childInvestmentStart;
      }
      if (accumEarning >= 0) {
        break;
      }
    }

    for (int i=childInvestmentStart; i<childInvestmentStart + investmentOffset; ++i) {
      totalInvestments[i] = Investment(0, 0);
    }

    if (accumEarning >= 0) {
      totalInvestments[childInvestmentStart + investmentOffset].holding += cost;
      totalInvestments[childInvestmentStart + investmentOffset].earning = accumEarning;
    }
  }

  totalInvestmentStart[node] = childInvestmentStart;
  totalInvestmentLen[node] = totalInvestmentIndex - childInvestmentStart;
}

void initAndGetInputs() {
  totalInvestmentIndex = 0;
  for (int i=0; i<N; ++i) {
    children[i].clear();
  }

  int parent, earning, cost;
  for (int node=1; node<N; ++node) {
    cin >> parent >> earning >> cost;
    earnings[node] = earning == -1 ? ESCAPE_EARNING : earning;
    costs[node] = cost;
    children[parent].push_back(node);
  }
}

void initWithDummyInputs() {
  totalInvestmentIndex = 0;
  for (int i=0; i<N; ++i) {
    children[i].clear();
  }

  int parent = -1;
  for (int node=1; node<N; ++node) {
    costs[node] = rand() % 1000;
    earnings[node] = rand() % 1000;
    if (node % 2 == 1) {
      parent += 1;
    }
    children[parent].push_back(node);
  }

  earnings[N-1] = ESCAPE_EARNING;
}

void buildLeafFirstOrderTree() {
  stack<int> st;
  st.push(0);

  nodeOrderLen = 0;
  while(not st.empty()) {
    int node = st.top(); st.pop();
    nodeOrder[nodeOrderLen++] = node;

    for (const auto &child : children[node]) {
      st.push(child);
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

  for (int i = totalInvestmentStart[node]; i<totalInvestmentStart[node] + totalInvestmentLen[node]; ++i) {
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
  for (int i = totalInvestmentStart[0]; i<totalInvestmentStart[0] + totalInvestmentLen[0]; ++i) {
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
//    N = 200000;
//    initWithDummyInputs();
    buildLeafFirstOrderTree();

    cout << "#" << test_case << " " << findMaxSearchHoldings() << " " << findMinSearchHoldings() << endl;
  }

  return 0;
}
