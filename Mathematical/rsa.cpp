#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
bool isPrime(T n) {
    if (n <= 1) return false;

    for (T i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }

    return true;
}

uint32_t gcd(uint32_t a, uint32_t b) {
    if (b > a) swap(a, b);
    if (a % b == 0) return b;
    return gcd(b, a % b);
}


// 유클리드 호제법 확장
// a*x + b*y = gcd(a, b), a > b 일 때 정수 x, y를 반환
std::pair<int64_t, int64_t> xgcd(int64_t a, int64_t b) {
    int64_t x[3] = {1, 0, 0}, y[3] = {0, 1, 1};

    while (a % b) {
        int64_t q = a / b;

        x[2] = x[0] - q*x[1];
        y[2] = y[0] - q*y[1];

        x[0] = x[1]; x[1] = x[2];
        y[0] = y[1]; y[1] = y[2];

        int64_t rest = a % b;
        a = b;
        b = rest;
    }

    return std::make_pair(x[2], y[2]);
}

std::pair<int64_t, int64_t> xgcd2(int64_t a, int64_t b) {
    if (b == 0)
        return std::make_pair(1, 0);

    auto next = xgcd2(b, a % b);

    int64_t x = next.first;
    int64_t y = next.second;

    return std::make_pair(y, x - (a/b)*y);
}

uint32_t privateKey(uint32_t a, uint32_t b) {
    int64_t temp, s[3], t[3], m = a;

    t[2] = s[0] = t[1] = 1;
    s[2] = s[1] = t[0] = 0;

    while (a % b){
        s[2] = s[0] - (a / b)*s[1];
        t[2] = t[0] - (a / b)*t[1];

        s[0] = s[1];
        t[0] = t[1];
        s[1] = s[2];
        t[1] = t[2];

        temp = a;
        a = b;
        b = temp % b;
    }

    if (t[2] < 0)
        t[2] += m;

    return t[2];
}

uint32_t coprimeKey(uint32_t n) {
    uint32_t ret = 1;
    int count = 10;

    for (uint32_t i = n - 1; i > 1; i--) {
        if (gcd(n, i) == 1) {
            ret = i;
            if (--count == 0)
                break;
        }
    }

    return ret;
}

uint64_t fastPow(uint64_t base, uint64_t exp, uint32_t mod) {
    uint64_t result = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result*base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

uint16_t p = 47111;
uint16_t q = 64237;

/*
uint16_t p = 7;
uint16_t q = 17;
*/

int main() {
    uint32_t data[100], enData[100], deData[100], dataNum;
    uint32_t n, En, e, d;

    cout << "p: " << p << "  q: " << q << endl;

    if (not isPrime(p) || not isPrime(q)) {
        cout << "p와 q중에 소수가 아닌 수가 있습니다" << endl;
        return 0;
    }

    n = (uint32_t)(p * q);
    En = ((uint32_t)(p - 1) * (uint32_t)(q - 1));
    e = coprimeKey(En);
    d = privateKey(En, e);

    auto c1 = xgcd(En, e);
    auto c2 = xgcd2(En, e);

    cout << "Pi(pq): " << En << "    e: " << e << "    d: " << d << endl;

    cout << "e*d = " << (uint64_t)(e*d) % (uint64_t)En << " (mod " << En << ")" << endl;


    cout << "s: " << c1.first << "    t: " << c1.second << endl;
    cout << "s: " << c2.first << "    t: " << c2.second << endl;
    cout << "암호문의 수: ";
    cin >> dataNum;

    for (int i = 1; i <= dataNum; i++) {
        cin >> data[i];
        enData[i] = fastPow(data[i], e, n);
        deData[i] = fastPow(enData[i], d, n);
    }

    for (int i = 1; i <= dataNum; i++)
        cout << enData[i] << " ";
    cout << endl;

    for (int i = 1; i <= dataNum; i++)
        cout << deData[i] << " ";
    cout << endl;

    return 0;
}
