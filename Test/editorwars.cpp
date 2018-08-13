#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
vector<int> acks(10005);
vector<int> diss(10005);

void init() {
    for (int i=0; i<N; i++) {
        acks[i] = i;
        diss[i] = -1;
    }
}

int root(int n) {
    if (n < 0) return n;
    if (n != acks[n]) {
        acks[n] = root(acks[n]);
        return acks[n];
    } else {
        return n;
    }
}

bool addTree(bool agree, int a, int b) {
    int ra = root(a);
    int rb = root(b);
    int disra = root(diss[ra]);
    int disrb = root(diss[rb]);

    if (agree) {
        if (disra == rb || disrb == ra)
            return false;

        if (disra >= 0 && disrb >= 0) {
             acks[disrb] = disra;
        } else if (disra < 0 && disrb >= 0) {
            diss[ra] = disrb;
        }

        acks[rb] = ra;
    } else {
        if (ra == rb || (disra == disrb && disra != -1))
            return false;

        if (disrb >= 0)
            acks[disrb] = ra;

        if (disra >= 0)
            acks[disra] = rb;

        diss[rb] = ra;
        diss[ra] = rb;
    }
    return true;
}

int maxPeople() {
    vector<int> sums(N, 0);
    int total = 0;

    for (int i=0; i<N; i++)
        sums[root(i)]++;

    for (int i=0; i<N; i++) {
        if (sums[i] > 0) {
            int otherSum = 0;
            int disroot = root(diss[i]);
            if (disroot >= 0) {
                otherSum = sums[disroot];
                sums[disroot] = 0;
            }
            total += max(sums[i], otherSum);
            sums[i] = 0;
        }
    }

    return total;
}

int main() {
    int T;

    cin>>T;
    for (int t=0; t<T; t++) {
        bool valid = true;
        cin >> N >> M;
        init();

        for (int i=1; i<=M; i++) {
            int a, b;
            string comment;
            cin >> comment >> a >> b;
            if (not valid) continue;
            if (not addTree(comment == "ACK" ? true : false, a, b)) {
                cout << "CONTRADICTION AT " << i << endl;
                valid = false;
            }
        }
        if (valid)
            cout << "MAX PARTY SIZE IS " << maxPeople() << endl;
    }
}
