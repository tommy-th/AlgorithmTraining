#include <iostream>
#include <set>
#include <functional>
#include <vector>
#include <algorithm>

struct Dot {
    int x, y;

    Dot(int x, int y) : x(x), y(y) {}
};

std::set<int> xdots;
std::set<int, std::greater<int>> ydots;
std::vector<Dot> dots;

int cols, rows, dotNum, recSize;
int result, rleft, rtop;

inline void calcRect(const int left, const int top) {
    int counts = 0;

    for (const auto& dot : dots) {
        if (dot.x >= left && dot.x <= left + recSize) {
            if (dot.y >= top - recSize && dot.y <= top) {
                counts++;
            }
        }
    }

    if (counts > result) {
        result = counts;
        rleft = left;
        rtop = top;
    }
}

int main() {
    int x, y;

    std::cin >> cols >> rows >> dotNum >> recSize;

    for(int i = 1; i <= dotNum; i++) {
        std::cin >> x >> y;
        dots.emplace_back(x, y);
        xdots.insert(x);
        ydots.insert(y);
    }

    for(auto xdot : xdots) {
        if (xdot > cols - recSize)
            xdot = cols - recSize;

        for(auto ydot : ydots) {
            if (ydot < recSize)
                ydot = recSize;

            calcRect(xdot, ydot);

            if (ydot == recSize)
                break;
        }

        if (xdot == cols - recSize)
            break;
    }

    std::cout << rleft << " " << rtop << std::endl;
    std::cout << result << std::endl;
}
