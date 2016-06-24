#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

pair<int, int> minMove(int startIdx, vector<vector<int>> &dists, int n) {
    int minIdx = -1;
    int minDist = 1000000;
    for (int i = 0; i < n; ++i) {
        int dist = dists.at(startIdx).at(i);
        if (dist == -1) {
            continue;
        }
        if (dist < minDist) {
            minDist = dist;
            minIdx = i;
        }
    }

    dists.at(startIdx).at(minIdx) = -1;
    dists.at(minIdx).at(startIdx) = -1;
    return make_pair(minIdx, minDist);
}


int shortestPath(int x, int y, int robotX, int robotY, const int n, pair<int, int> *coins) {
    vector<vector<int>> coinDists(n, vector<int>(5));

    int startIdx = 0;
    int startDist = 1000000;
    for (int k = 0; k < n; ++k) {
        pair<int, int> coin = coins[k];
        int dist = abs(robotX - coin.first) + abs(robotY - coin.second);
        if (dist < startDist) {
            startDist = dist;
            startIdx = k;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                coinDists[i][j] = coinDists[j][i] = -1;
                continue;
            }
            pair<int, int> coin1 = coins[i];
            pair<int, int> coin2 = coins[j];
            int distance = abs(coin1.first - coin2.first) + abs(coin1.second - coin2.second);
            coinDists[i][j] = coinDists[j][i] = distance;
        }
    }

    int totalDist = startDist;
    int currIdx = startIdx;
    for (int l = 0; l < n - 1; ++l) {
        pair<int, int> move = minMove(currIdx, coinDists, n);
        totalDist += move.second;
        currIdx = move.first;
    }

    pair<int, int> lastCoin = coins[currIdx];
    totalDist += abs(lastCoin.first - robotX) + abs(lastCoin.second - robotY);

    return totalDist;
}


int main(int argc, char *argv[]) {
    int numTests;
    cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        int x, y, startX, startY, n, coinX, coinY;
        cin >> x >> y;
        cin >> startX >> startY;
        cin >> n;
        pair<int, int> coins[n];
        for (int j = 0; j < n; j++) {
            cin >> coinX >> coinY;
            coins[j] = make_pair(coinX, coinY);
        }

        cout << shortestPath(x, y, startX, startY, n, coins) << endl;
    }
}

int test() {
    int distances[max][max];

    setup(distances);

    std::vector<int> route(max);

    std::iota(route.begin(), route.end(), 0);

    int best_distance = std::numeric_limits<int>::max();
    do {
        int distance = 0;
        for (int i = 1; i < route.size(); i++) {
            distance += distances[route[i - 1]][route[i]];
            if (distance > best_distance)
                break;
        }
        distance += distances[route[max - 1]][0];

        if (distance < best_distance) best_distance = distance;
    } while (std::next_permutation(route.begin() + 1, route.end()));

    std::cout << "best distance: " << best_distance << "\n";3
}