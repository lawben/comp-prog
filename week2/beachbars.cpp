#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <iterator>
#include <sstream>
#include <climits>
#include "iostream"

int maxParasols;
int distToMaxParasol;
std::vector<int> possiblePositions;


std::vector<int> getPossiblePosition(int range, int start) {
    std::vector<int> positions;

    if (range % 2 == 1) {
        int firstPossibility = (int) (start + std::floor(range / (double) 2));
        int secondPossibility = (int) (start + std::ceil(range / (double) 2));
        positions.push_back(firstPossibility);
        positions.push_back(secondPossibility);
    } else {
        positions.push_back(start + range / 2);
    }
    return positions;
}


void updateMax(std::vector<int> &currentInRange) {
    int range = std::abs(currentInRange.at(currentInRange.size() - 1) - currentInRange.at(0));
    distToMaxParasol = (int) std::ceil(range / (double) 2);
    maxParasols = (int) currentInRange.size();
    possiblePositions = getPossiblePosition(range, currentInRange.at(0));
}

void calculateBestPosition(std::vector<int> &parasolPositions) {
    maxParasols = 0;
    distToMaxParasol = 1000000;
    possiblePositions.clear();

    std::sort(parasolPositions.begin(), parasolPositions.end());
    std::vector<int> currentInRange;
    for (unsigned int i = 0; i < parasolPositions.size(); ++i) {
        currentInRange.push_back(parasolPositions.at(i));
        int mostRight = currentInRange.at(currentInRange.size() - 1);
        while (mostRight - 200 > currentInRange.at(0)) {
            currentInRange.erase(currentInRange.begin());
        }
        int range = std::abs(currentInRange.at(currentInRange.size() - 1) - currentInRange.at(0)) ;
        if (currentInRange.size() > maxParasols) {
            updateMax(currentInRange);
        } else if(currentInRange.size() == maxParasols) {
            int currentDistToMax = (int) std::ceil(range / (double) 2);
            if (currentDistToMax < distToMaxParasol) {
                updateMax(currentInRange);
            } else if (currentDistToMax == distToMaxParasol){
                std::vector<int> newPossibilities = getPossiblePosition(range, currentInRange.at(0));
                possiblePositions.insert(possiblePositions.end(), newPossibilities.begin(), newPossibilities.end());
            }
        }
    }
    std::unique(possiblePositions.begin(), possiblePositions.end());
    std::sort(possiblePositions.begin(), possiblePositions.end());
    std::cout << maxParasols << " " << distToMaxParasol << std::endl;
    std::ostringstream ss;
    std::copy(possiblePositions.begin(), possiblePositions.end() - 1, std::ostream_iterator<int>(ss, " "));
    ss << possiblePositions.back();
    std::cout << ss.str() << "\n";
}


int main(int argc, char *argv[]) {
    unsigned int amountTests;
    std::cin >> amountTests;
    for (unsigned int i = 0; i < amountTests; ++i) {
        unsigned int numParasols;
        std::cin >> numParasols;

        std::vector<int> parasols;
        int parasolPos;
        for (unsigned int j = 0; j < numParasols; ++j) {
            std::cin >> parasolPos;
            parasols.push_back(parasolPos);
        }

        if (numParasols == 1) {
            std::cout << "1 0" << std::endl << parasolPos << std::endl;
            continue;
        }

        calculateBestPosition(parasols);
    }
}