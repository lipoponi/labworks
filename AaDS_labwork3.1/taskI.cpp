#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cstdio>

const double INF = 123456;

struct point {
    int x, y;

    double operator-(const point &other) const {
        int dx = this->x - other.x;
        int dy = this->y - other.y;

        return std::sqrt(dx * dx + dy * dy);
    }
};

std::vector<point> vertices;
std::vector<bool> used;
std::vector<double> minDistances;

void addVertex(int v) {
    used[v] = true;
    minDistances[v] = INF;

    for (int i = 0; i != minDistances.size(); i++) {
        if (used[i]) {
            continue;
        }

        minDistances[i] = std::min(minDistances[i], vertices[v] - vertices[i]);
    }
}

int main() {
    int n;
    std::cin >> n;

    vertices.resize(n);
    used.resize(n, false);
    minDistances.resize(n, INF);

    for (int i = 0; i < n; i++) {
        std::cin >> vertices[i].x >> vertices[i].y;
    }

    addVertex(0);
    int count = 1;
    double answer = 0;

    while (count < n) {
        auto it = std::min_element(minDistances.begin(), minDistances.end());
        auto idx = std::distance(minDistances.begin(), it);
        answer += minDistances[idx];

        addVertex(idx);
        count++;
    }

    std::cout << std::fixed << std::setprecision(8);
    std::cout << answer << std::endl;

    return 0;
}