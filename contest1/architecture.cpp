#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

typedef vector<tuple<int, int, int>> Floors;

int crashCost(const int numFloors, Floors &building, const int maxCost) {
//    vector<vector<int>> weights(numFloors, std::vector<int>(maxCost));
    int weights[numFloors][maxCost];

    int currCost, currWeight, currCapacity;
    tie(currWeight, currCapacity, currCost) = building.at(0);

    for (int j = 0; j < maxCost; j++) {
        if (j >= currCost) {
            weights[0][j] = currWeight;
        } else {
            weights[0][j] = 0;
        }
    }

    for (int i = 1; i < numFloors - 1; i++) {
        tie(currWeight, currCapacity, currCost) = building.at(i);
        for (int j = 0; j < maxCost; j++) {
            int sameCostPrev = weights[i-1][j];
            int cheaperPrevIdx = j - currCost;
            int cheaperPrev = (cheaperPrevIdx < 0) ? 0 : weights[i-1][cheaperPrevIdx];

            int withPrevCollapse = sameCostPrev + (((sameCostPrev + currWeight) > currCapacity) ? currWeight : 0);
            int withNewCollapse = cheaperPrev + ((j >= currCost) ? currWeight : 0);

            weights[i][j] = max(withNewCollapse, withPrevCollapse);
        }
    }

    tie(currWeight, currCapacity, currCost) = building.at(numFloors - 1);
    for (int j = 0; j < maxCost; j++) {
        if (weights[numFloors-2][j] + currWeight > currCapacity) {
            return j;
        }
    }

    return maxCost;
}

int main(int argc, char* argv[]) {
    int numTests;
//    cin >> numTests;

    ifstream inFile("/home/lawrence/repos/comp-prog/contest1/architecture-LargeSample.in");
//    ifstream ansFile("/home/lawrence/repos/comp-prog/contest1/whiteHouse-LargeSample.ans");

//    inFile.open("whiteHouse-LargeSample.in");
    string line;

    if (inFile.is_open()) {
        inFile >> numTests;


        for (int t = 0; t < numTests; ++t) {
            int numFloors;
            inFile >> numFloors;

            Floors building = Floors(numFloors);

            for (int f = 0; f < numFloors; ++f) {
                int weight, capacity, cost;
                inFile >> weight >> capacity >> cost;
                tuple<int, int, int> floor = make_tuple(weight, capacity, cost);
                building.at(f) = floor;
            }

            int maxCost = get<2>(building.at(0));

            reverse(building.begin(), building.end());

            building.at(0);
            cout << crashCost(numFloors, building, maxCost) << endl;
        }

    } else {
        cout << "sdfdf";
    }
}