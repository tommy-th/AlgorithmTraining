#include <iostream>

using namespace std;


const int N = 100;
const double pv = 1000;
const double pmt = 300;
const double error = 0.00001;

double bsearch(double s, double e) {
  const double mid = (s + e) / 2;
  const double yield = 1 + mid;

  double sum = 0;
  double r = yield;
  for (int i = 0; i < N; ++i) {
    sum += (pmt / r);
    r *= yield;
  }

  if (sum > pv - error and sum <= pv + error) {
    return mid;
  }

  cout << sum << " " << s << " " << e << endl;

  if (sum > pv + error) {
    return bsearch(mid, e);
  } else {
    return bsearch(s, mid);
  }
}

//int main() {
//  cout.precision(17);
//  cout << bsearch(0, 1) << endl;
//}