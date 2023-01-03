#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


int H, W, N;
vector<string> words;

bool checkWordSize(const int csize) {
  bool newLine = true;
  int remainH = H - csize, remainW = W, wi = 0;

  while (wi < words.size()) {
    if (newLine) {
      if (remainW < words[wi].size() * csize) {
        return false;
      }

      newLine = false;
      remainW -= words[wi].size() * csize;
      wi += 1;
    } else {
      if (remainW >= (words[wi].size() + 1) * csize) {
        remainW -= (words[wi].size() + 1) * csize;
        wi += 1;
      } else {
        if (remainH < csize) {
          return false;
        }

        newLine = true;
        remainW = W;
        remainH -= csize;
      }
    }
  }

  return remainH >= 0;
}

int bsearch() {
  int csize = 0;
  int from = 0, to = 1000;

  while (from <= to) {
    int mid = (from + to) / 2;

    bool checkResult = checkWordSize(mid);
    if (checkResult) {
      from = mid + 1;
      csize = max(csize, mid);
    } else {
      to = mid - 1;
    }
  }

  return csize;
}

int main(int argc, char** argv) {
  int test_case;
  int T;
  cin>>T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> H >> W >> N;
    words.clear();

    string word;
    for (int i=0; i<N; ++i) {
      cin >> word;
      words.push_back(word);
    }

    cout << "#" << test_case << " " << bsearch() << endl;
  }

  return 0;
}
