#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair< pair<int, int>, pair<int, int> > make_reach_pair(int leftR, int leftD, int rightR, int rightD) {
    return make_pair(make_pair(leftR, leftD), make_pair(rightR, rightD));
};

vector< pair<pair<int, int>, pair<int, int> > > initReachable(vector<int> parasols) {
    vector< pair< pair<int, int>, pair<int, int> > > reachable;

    int maxParasol = parasols.at(parasols.size() - 1);
    unsigned int nextIdx = 1;
    int minPos = parasols.at(0);
    int nextParasol = minPos;
    int amountReachable = 0;
    int maxDistance = 0;
    while (nextParasol < maxParasol) {
        nextParasol = parasols.at(nextIdx++);
        int distance = abs(minPos - nextParasol);
        if (distance <= 100) {
            amountReachable++;
            maxDistance = max(maxDistance, distance);
        }
    }

    reachable.push_back(make_reach_pair(1, 0, amountReachable, maxDistance));
    return reachable;
};




void findBeachBarPosition(unsigned int numParasols, vector<int> &parasols) {
    sort(parasols.begin(), parasols.end());

    int maxParasol = parasols.at(numParasols - 1);

    vector< pair< pair<int, int>, pair<int, int> > > reachable = initReachable(parasols);

    unsigned int currentParasolIdx = 0;
    unsigned int currIdx = 1;
    int nextParasol = parasols.at(currentParasolIdx + 1);
    bool isParasolPos = false;
    for (int currPos = parasols.at(0) + 1; currPos <= maxParasol; ++currPos) {
        if (currPos == nextParasol) {
            currentParasolIdx++;
            isParasolPos = true;
            if (nextParasol != maxParasol) {
                nextParasol = parasols.at(currentParasolIdx + 1);
            }
        }

        pair< pair<int, int>, pair<int, int> > prev = reachable.at(currIdx - 1);

        int leftReach, rightReach, leftDist, rightDist;

        int prevLeftReach = prev.first.first;
        int prevLeftDist = prev.first.second;
        int prevRightReach = prev.second.first;
        int prevRightDist = prev.second.second;

        if (prevLeftDist == 100) {
            leftReach = prevLeftReach - 1;
            if (leftReach > 0) {
                leftDist = abs(currPos - parasols.at(currentParasolIdx + 1 - leftReach));
            } else {
                leftDist = 0;
            }
        } else {
            leftReach = prevLeftReach;
            if (leftReach > 0) {
                leftDist = prevLeftDist + 1;
            } else {
                leftDist = 0;
            }
        }


        rightReach = prevRightReach;
        rightDist = prevRightDist - 1;

        if (prevRightDist >= 0) {
            unsigned int candIdx = currentParasolIdx + prevRightReach + 1;
            if (isParasolPos) {
                candIdx--;
            }
            if (candIdx < numParasols) {
                int candidate = parasols.at(candIdx);
                int dist = abs(currPos - candidate);
                if (dist <= 100) {
                    rightReach++;
                    rightDist = dist;
                }
            }
        }

        if (isParasolPos) {
            leftReach++;
            rightReach--;
        }

        reachable.push_back(make_reach_pair(leftReach, leftDist, rightReach, rightDist));
        currIdx++;
        isParasolPos = false;
    }

    int minParasol = parasols.at(0);
    int maxParasols = 0;
    int minDistance = 101;
    vector<int> bestPositions;
    for (unsigned int r = 0; r < reachable.size(); ++r) {
        pair< pair<int, int>, pair<int, int> > reach = reachable.at(r);
        pair<int, int> entry = make_pair(reach.first.first + reach.second.first, max(reach.first.second, reach.second.second));
        if (entry.first > maxParasols) {
            maxParasols = entry.first;
            minDistance = entry.second;
            bestPositions.clear();
            bestPositions.push_back(minParasol + r);
        } else if (entry.first == maxParasols) {
            if (entry.second < minDistance) {
                minDistance = entry.second;
                bestPositions.clear();
                bestPositions.push_back(minParasol + r);
            } else if (entry.second == minDistance) {
                bestPositions.push_back(minParasol + r);
            }
        }
    }

    sort(bestPositions.begin(), bestPositions.end());
    std::cout << maxParasols << " " << minDistance << std::endl;

    for (vector<int>::iterator it = bestPositions.begin(); it != bestPositions.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;
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

        if (numParasols == 1) {
            cout << "1 0" << endl << parasolPos << endl;
            continue;
        }

        findBeachBarPosition(numParasols, parasols);
    }
}
