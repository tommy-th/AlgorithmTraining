#include <iostream>
#include <string>
#include <vector>
using namespace std;

using Point = pair<int, int>;

int N, M;
Point O;
int map[15][15] = {0,};

vector<Point> dirs{ Point(1,0), Point(-1,0), Point(0,1), Point(0,-1)};

int slide(int count, int d, Point R, Point B) {
  Point dir = dirs[d];

  bool isMoving = true;
  bool bExited = false;
  bool rExited = false;

  while (isMoving) {
    isMoving = false;

    if (not bExited) {
      Point NB = Point(B.first + dir.first, B.second + dir.second);
      if (map[NB.first][NB.second] == 0 && (NB != R || rExited)) {
        B = NB;
        isMoving = true;
        if (B == O) {
          bExited = true;
        }
      }
    }

    if (not rExited) {
      Point NR = Point(R.first + dir.first, R.second + dir.second);
      if (map[NR.first][NR.second] == 0 && (NR != B || bExited)) {
        R = NR;
        isMoving = true;
        if (R == O) {
          rExited = true;
        }
      }
    }
  }

  cout << "count: " << count << endl;
  cout << "R    : " << R.first << " " << R.second << endl;
  cout << "B    : " << B.first << " " << B.second << endl;

  if (bExited) {
    return -1;
  }

  if (rExited) {
    return count;
  }

  if (count >= 10) {
    return -1;
  }

  int ret = 11;
  for (int d = 0; d < 4; ++d) {
    int nc = slide(count + 1, d, R, B);
    if (nc > 0) {
      ret = min(ret, nc);
    }
  }

  return ret > 10 ? -1 : ret;
}


int main() {
  cin >> N >> M;

  string mstr;
  Point R, B;
  for (int i=1; i<=N; i++) {
    cin >> mstr;
    for (int j=1; j<=M; j++) {
      if (mstr[j] == '#') {
        map[i][j] = 1;
      } else if (mstr[j-1] == 'R') {
        R = Point(i, j);
      } else if (mstr[j-1] == 'B') {
        B = Point(i, j);
      } else if (mstr[j-1] == 'O') {
        O = Point(i, j);
      }
    }
  }

  int ret = 11;
  for (int d = 0; d < 4; ++d) {
    int nc = slide(1, d, R, B);
    if (nc > 0) {
      ret = min(ret, nc);
    }
  }
  if (ret > 10) {
    ret = -1;
  }

  cout << ret << endl;

  return 0;
}