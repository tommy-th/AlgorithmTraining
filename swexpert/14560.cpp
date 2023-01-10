#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;
using Bitset = deque<bool>;

const vector<string> NEXT_OPT{
  "X", "Y"
};

const int MAX_OPT_LEN = 12;

Bitset buildBitset(const int n) {
  Bitset ret;
  int i = 1;
  while (i <= n) {
    if (i & n) {
      ret.push_front(true);
    } else {
      ret.push_front(false);
    }
    i <<= 1;
  }
  return ret;
}

string toString(const Bitset& bitset) {
  stringstream ret;
  for (const bool bit : bitset) {
    ret << (bit ? "1" : "0");
  }
  return ret.str();
}

struct BitsetResult {
  Bitset a;
  Bitset b;
  string opts;
  int diff;

  BitsetResult() : diff(10000) {
  }

  BitsetResult(BitsetResult&& other)
      : a(std::move(other.a)), b(std::move(other.b)), opts(std::move(other.opts)), diff(other.diff) {
  }

  BitsetResult(Bitset&& a_, Bitset&& b_, const string& opts)
      :a(std::move(a_)), b(std::move(b_)), opts(opts) {
    diff = max(a.size(), b.size()) - getCommonLen();
  }

  BitsetResult& operator=(BitsetResult&& other) {
    a = std::move(other.a);
    b = std::move(other.b);
    opts = std::move(other.opts);
    diff = other.diff;
    return *this;
  }

  bool operator< (const BitsetResult& other) {
    return diff < other.diff or (diff == other.diff and opts.size() < other.opts.size());
  }

  int getCommonLen() {
    int i = 0;
    while (i < a.size() and i < b.size() and a[i] == b[i]) {
      ++i;
    }
    return i;
  }

  void popCommonBits() {
    const int commonLen = getCommonLen();
    for (int i = 0; i < commonLen; ++i) {
      if (a.size() <= 1 or b.size() <= 1)
        break;
      a.pop_front();
      b.pop_front();
    }
  }
};

void addOne(Bitset& target, Bitset& another) {
  int i = target.size() - 1;
  while (i >= 0) {
    target[i] = !target[i];
    if (target[i]) break;
    i -= 1;
  }

  if (i < 0) {
    target.push_front(true);
    another.push_front(false);
  }
}

bool mulTwo(Bitset& bitset) {
  bitset.push_back(false);
}

void applyOperator(Bitset& a, Bitset& b, const char& opt) {
  if (opt == 'X') {
    addOne(a, b);
    mulTwo(b);
  } else {
    addOne(b, a);
    mulTwo(a);
  }
}

BitsetResult applyRandomOperators(Bitset&& a, Bitset&& b, const string opts) {
  applyOperator(a, b, opts[opts.size() - 1]);

  BitsetResult result;

  if (opts.size() < MAX_OPT_LEN) {
    for (const string& nopt : NEXT_OPT) {
      Bitset ta(a.size());
      copy(a.begin(), a.end(), ta.begin());
      Bitset tb(b.size());
      copy(b.begin(), b.end(), tb.begin());

      auto next = applyRandomOperators(std::move(ta), std::move(tb), opts + nopt);
      if (next < result) {
        result = std::move(next);
      }
    }
  }

  auto cur = BitsetResult(std::move(a), std::move(b), opts);
  if (cur < result) {
    result = std::move(cur);
  }

  return std::move(result);
}

BitsetResult applyGreedyOperators(Bitset&& a, Bitset&& b) {
  stringstream optsBuf;

  BitsetResult result = BitsetResult(std::move(a), std::move(b), "");
  if (min(result.a.size(), result.b.size()) >= 6) {
    return result;
  }

  bool reversed = !(result.a.size() < result.b.size());
  Bitset& minBits = result.a.size() < result.b.size() ? result.a : result.b;
  Bitset& maxBits = result.a.size() < result.b.size() ? result.b : result.a;

  int minLeft = 0;
  for (const bool minBit : minBits) {
    minLeft <<= 1;
    if (!minBit) {
      minLeft += 1;
    }
  }

  for (int i=0; i<minLeft; ++i) {
    applyOperator(minBits, maxBits, 'X');
    optsBuf.put('X');
  }

  int maxLeft = 0;
  for (int i=0; i<minBits.size(); ++i) {
    if (!maxBits[i]) {
      maxLeft += pow(2, maxBits.size() - 1 - i);
    }
  }

  for (int i=0; i<maxLeft; ++i) {
    applyOperator(minBits, maxBits, 'Y');
    optsBuf.put('Y');
  }

  while (minBits[0] == maxBits[0]) {
    result.popCommonBits();
    if (minBits.size() < maxBits.size()) {
      applyOperator(minBits, maxBits, 'Y');
      optsBuf.put('Y');
    } else {
      applyOperator(minBits, maxBits, 'X');
      optsBuf.put('X');
    }
    if (minBits.size() == maxBits.size())
      break;
  }

  string opts = optsBuf.str();
  if (reversed) {
    for (int i=0; i < opts.size(); ++i) {
      opts[i] = opts[i] == 'X' ? 'Y' : 'X';
    }
  }
  result.opts = opts;

  return result;
}

BitsetResult calcOperators(Bitset&& a, Bitset&& b, bool withGreedy) {
  cout << toString(a) << " " << toString(b) << endl;

  BitsetResult result;
  if (withGreedy) {
    Bitset ca(a.size());
    copy(a.begin(), a.end(), ca.begin());
    Bitset cb(b.size());
    copy(b.begin(), b.end(), cb.begin());
    result = std::move(applyGreedyOperators(std::move(ca), std::move(cb)));
  }

  for (const string& opts : NEXT_OPT) {
    Bitset ta(a.size());
    copy(a.begin(), a.end(), ta.begin());
    Bitset tb(b.size());
    copy(b.begin(), b.end(), tb.begin());

    auto next = applyRandomOperators(std::move(ta), std::move(tb), opts);
    if (next < result) {
      result = std::move(next);
    }
  }

  return result;
}

string calcOperators(int A, int B) {
  stringstream optCandidates;
  while(min(A, B) * 2 < max(A, B)) {
    if (A < B) {
      A *= 2;
      B += 1;
      optCandidates.put('Y');
    } else {
      A += 1;
      B *= 2;
      optCandidates.put('X');
    }
  }

  Bitset a = buildBitset(A);
  Bitset b = buildBitset(B);
  auto next = calcOperators(std::move(a), std::move(b), true);
  next.opts = optCandidates.str() + next.opts;

  BitsetResult result = std::move(next);

  stringstream optResult;
  optResult << result.opts;

  while (result.diff > 0 and optResult.str().size() < 1000) {
    result.popCommonBits();
    result = calcOperators(std::move(result.a), std::move(result.b), false);
    optResult << result.opts;
  }

  return optResult.str();
}

int main(int argc, char** argv) {
  int test_case;
  int T, A, B;
//  cin>>T;
//  for (test_case = 1; test_case <= T; ++test_case) {
//    cin >> A >> B;
//    cout << "#" << test_case << " " << calcOperators(A, B) << endl;
//  }

  for (int i = 1; i <= 100; ++i) {
    for (int j = i + 1; j <= 100; ++j) {
      if (i == j or j==9 or j == 16 or j == 32 or j == 34 or j == 64) continue;
      string opts = calcOperators(i, j);
      cout << i << " " << j << " : " <<  opts.size() << endl;
    }
  }

  return 0;
}
