#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void findBestPosition(unsigned int numParasols, vector<int> parasols) {
    vector<int>::iterator minPos = min_element(parasols.begin(), parasols.end());
    vector<int>::iterator maxPos = max_element(parasols.begin(), parasols.end());
    long range = *maxPos - *minPos + 1;

    vector<int> positions;
    for (int pos = *minPos; pos <= *maxPos; ++pos) {
        positions.push_back(pos);
    }

    pair<int, int> distanceMatrix[numParasols][range];

    for (unsigned int r = 0; r < range; ++r) {
        pair<int, int> entry = make_pair(0, 0);
        int distance = abs(positions.at(r) - parasols.at(0));
        if (distance <= 100) {
            entry = make_pair(1, distance);
        }
        distanceMatrix[0][r] = entry;
    }

    for (unsigned int i = 1; i < numParasols; ++i) {
        for (unsigned int j = 0; j < range; ++j) {
            int pos = positions.at(j);
            int parasol = parasols.at(i);
            pair<int, int> prev = distanceMatrix[i-1][j];
            pair<int, int> entry = prev;

            int distance = abs(pos - parasol);
            if (distance <= 100) {
                entry = make_pair(prev.first + 1, max(prev.second, distance));
            }

            distanceMatrix[i][j] = entry;
        }
    }

    int maxParasols = 0;
    int minDistance = 101;
    vector<int> bestPositions;
    for (unsigned int r = 0; r < range; ++r) {
        pair<int, int> entry = distanceMatrix[numParasols - 1][r];
        if (entry.first > maxParasols) {
            maxParasols = entry.first;
            minDistance = entry.second;
            bestPositions.clear();
            bestPositions.push_back(positions[r]);
        } else if (entry.first == maxParasols) {
            if (entry.second < minDistance) {
                minDistance = entry.second;
                bestPositions.clear();
                bestPositions.push_back(positions[r]);
            } else if (entry.second == minDistance) {
                bestPositions.push_back(positions[r]);
            }
        }
    }

    sort(bestPositions.begin(), bestPositions.end());
    cout << maxParasols << " " << minDistance << endl;
    for (vector<int>::iterator it = bestPositions.begin(); it != bestPositions.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;


}

int main(int argc, char *argv[]) {
    unsigned int amountTests;
    cin >> amountTests;
    for (unsigned int i = 0; i < amountTests; ++i) {
        unsigned int numParasols;
        cin >> numParasols;

        vector<int> parasols;
        int parasolPos;
        for (unsigned int j = 0; j < numParasols; ++j) {
            cin >> parasolPos;
            parasols.push_back(parasolPos);
        }

        findBestPosition(numParasols, parasols);
    }
}
