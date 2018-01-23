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
// a*x + b*y = gcd(a, b), a < b 일 때 정수 x, y를 반환
std::pair<int64_t, int64_t> xgcd(int64_t a, int64_t b) {
    int64_t x[3] = {0, 1, 1}, y[3] = {1, 0, 0};

    while (b % a) {
        int64_t q = b / a;

        x[2] = x[0] - q*x[1];
        y[2] = y[0] - q*y[1];

        x[0] = x[1]; x[1] = x[2];
        y[0] = y[1]; y[1] = y[2];

        int64_t rest = b % a;
        b = a;
        a = rest;
    }

    return std::make_pair(x[2], y[2]);
}

// 재귀적으로 구하는 함수
std::pair<int64_t, int64_t> xgcd2(int64_t a, int64_t b) {
    if (a == 0)
        return std::make_pair(0, 1);

    auto next = xgcd2(b % a, a);

    int64_t x = next.first;
    int64_t y = next.second;

    return std::make_pair(y - (b/a)*x, x);
}

uint32_t privateKey(uint32_t e, uint32_t En) {
//    int64_t ret = xgcd2(e, En).first;
    int64_t ret = xgcd(e, En).first;

    if (ret < 0)
        ret += En;

    if (ret > En)
        ret %= En;

    return ret;
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

int main() {
    uint32_t n, En, e, d;

    cout << "p: " << p << "  q: " << q << endl;

    if (not isPrime(p) || not isPrime(q)) {
        cout << "p와 q중에 소수가 아닌 수가 있습니다" << endl;
        return 0;
    }

    n = (uint32_t)(p * q);
    En = ((uint32_t)(p - 1) * (uint32_t)(q - 1));
    e = coprimeKey(En);
    d = privateKey(e, En);

    cout << "Pi(pq): " << En << "    e: " << e << "    d: " << d << endl;

    // private key valied check
    uint64_t isValid = ((uint64_t)e*(uint64_t)d) % (uint64_t)En;
    if (isValid != 1) {
        cout << "public key, private key 쌍이 유효하지 않습니다" << endl;
        return 0;
    }

    while (1) {
        uint32_t data, encoded, decoded;
        cout << "암호화 할 자연수를 입력하세요. ("<< n << " 미만)\n";
        cout << "data: "; cin >> data; 

        if (data >= n) break;

        encoded = fastPow(data, e, n); 
        decoded = fastPow(encoded, d, n); 

        cout << "encoded data: " << encoded << std::endl;
        cout << "decoded data: " << decoded << std::endl;

    }

    return 0;
}
