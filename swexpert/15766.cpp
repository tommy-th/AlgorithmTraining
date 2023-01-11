#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;

int ESCAPE_EARNING = 1200000000;
int ESCAPE_EARNING_THRESHOLD = 1000000000;

struct Investment {
  int holding;
  int earning;

  Investment(int holding, int earning) : holding(holding), earning(earning) {}
};


struct InvestmentNode;

vector<int> earnings;
vector<int> costs;
vector<int> leafFirstOrder;
vector<vector<int>> children;
vector<InvestmentNode> investmentNodes;

struct InvestmentNode {
  int node;
  int maxCost;
  vector<Investment> investments;

  InvestmentNode() = default;

  void buildMaxCost() {
    int childMaxCost = 0;

    for (int child : children[node]) {
      childMaxCost += investmentNodes[child].maxCost;
    }

    int cost = costs[node];
    int earning = earnings[node];

    maxCost = max(max(0, cost - 1), cost - earning + childMaxCost);
  }

  void buildInvestments() {
    vector<Investment> tempInvestments;
    vector<Investment> totalChildInvestments;

    for (int child : children[node]) {
      const auto& childInvestments = investmentNodes[child].investments;
      totalChildInvestments.insert(
          totalChildInvestments.end(), childInvestments.begin(), childInvestments.end());
    }

    std::sort(totalChildInvestments.begin(), totalChildInvestments.end(),
              [](const auto& lhs, const auto& rhs) {
      return lhs.holding < rhs.holding or (lhs.holding == rhs.holding and lhs.earning > rhs.earning);
    });

    int holdings = 0;
    int accumEarning = earnings[node];
    for (const auto& investment : totalChildInvestments) {
      if (holdings + accumEarning >= investment.holding) {
        accumEarning += investment.earning;
      } else {
        tempInvestments.emplace_back(holdings, accumEarning);
        holdings = investment.holding;
        accumEarning = investment.earning;
      }
    }
    tempInvestments.emplace_back(holdings, accumEarning);

    int cost = costs[node];
    int si = 0;

    if (cost > 0) {
      accumEarning = -cost;

      for (; si < tempInvestments.size(); ++si) {
        if (accumEarning < 0) {
          accumEarning += tempInvestments[si].earning;
        }
        if (accumEarning >= 0) {
          break;
        }
      }

      if (accumEarning >= 0) {
        investments.emplace_back(tempInvestments[si].holding + cost, accumEarning);
      }
    } else {
      investments.emplace_back(tempInvestments[si].holding + cost, tempInvestments[si].earning);
    }

    for (int i=si+1; i<tempInvestments.size(); ++i) {
      investments.emplace_back(tempInvestments[i].holding + cost, tempInvestments[i].earning);
    }
  }
};

void initAndGetInputs() {
  earnings = vector<int>(N, 0);
  costs = vector<int>(N, 0);
  leafFirstOrder = vector<int>();
  children = vector<vector<int>>(N, vector<int>());
  investmentNodes = vector<InvestmentNode>(N);
  for (int i=0; i<N; ++i) {
    investmentNodes[i].node = i;
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

  while(not q.empty()) {
    int node = q.front(); q.pop();
    leafFirstOrder.push_back(node);

    for (const auto &child : children[node]) {
      q.push(child);
    }
  }

  std::reverse(leafFirstOrder.begin(), leafFirstOrder.end());
}

int findMaxSearchHoldings() {
  for (const auto& node : leafFirstOrder) {
    investmentNodes[node].buildMaxCost();
  }
  return investmentNodes[0].maxCost + 1;
}

int findMinSearchHoldings() {
  for (const auto& node : leafFirstOrder) {
    investmentNodes[node].buildInvestments();
  }

  int accumEarnings = 0;

  for (const auto &investment : investmentNodes[0].investments) {
    if (investment.earning > ESCAPE_EARNING_THRESHOLD) {
      return investment.holding - accumEarnings;
    } else {
      accumEarnings += investment.earning;
    }
  }
}

void printInvestmentNodes() {
  for (auto& investmentNode : investmentNodes) {
    cout << investmentNode.node << endl;
    for (auto& investment : investmentNode.investments) {
      cout << investment.holding << " " << investment.earning << endl;
    }
    cout << endl;
  }
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
