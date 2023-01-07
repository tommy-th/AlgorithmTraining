#include <iostream>
#include <vector>

using namespace std;
using LL = long long int;


struct Dot {
  int x;
  int y;
  int z;

  Dot(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct Plane {
  LL a;
  LL b;
  LL c;
  LL d;

  Plane() {}

  Plane(const Dot& p, const Dot& q, const Dot& r) {
    a = (LL)p.y*(q.z - r.z) + (LL)q.y*(r.z - p.z) + (LL)r.y*(p.z - q.z);
    b = (LL)p.z*(q.x - r.x) + (LL)q.z*(r.x - p.x) + (LL)r.z*(p.x - q.x);
    c = (LL)p.x*(q.y - r.y) + (LL)q.x*(r.y - p.y) + (LL)r.x*(p.y - q.y);
    d = -(LL)p.x*((LL)q.y*r.z - (LL)r.y*q.z) - (LL)q.x*((LL)r.y*p.z - (LL)p.y*r.z) - (LL)r.x*((LL)p.y*q.z - (LL)q.y*p.z);
  }

  bool inValid() {
    return a == 0 and b == 0 and c == 0;
  }

  bool isIncluded(const Dot& dot) {
    return a*dot.x + b*dot.y + c*dot.z + d == 0;
  }
};

vector<Dot> dots;
Plane plain;
int lastPassedDotIndex;

void searchPlain() {
  const Dot& p = dots[0];
  const Dot& q = dots[1];

  for (int i=2; i<dots.size(); ++i) {
    const Dot& r = dots[i];
    plain = Plane(p, q, r);
    if (not plain.inValid()) {
      lastPassedDotIndex = i;
      break;
    }
  }
}

bool checkAllDots() {
  for (int i=lastPassedDotIndex + 1; i<dots.size(); ++i) {
    if (not plain.isIncluded(dots[i]))
      return false;
  }
  return true;
}

int main(int argc, char** argv) {
  int test_case;
  int T, N;
  cin>>T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N;
    dots.clear();
    dots.reserve(N);

    LL x, y, z;
    for (int i=0; i<N; ++i) {
      cin >> x >> y >> z;
      dots.emplace_back(x, y, z);
    }

    if (N < 3) {
      cout << "#" << test_case << " TAK" << endl;
    } else {
      searchPlain();
      if (checkAllDots()) {
        cout << "#" << test_case << " TAK" << endl;
      } else {
        cout << "#" << test_case << " NIE" << endl;
      }
    }

  }

  return 0;
}
