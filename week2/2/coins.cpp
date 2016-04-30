#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int getValue(std::vector<std::vector<int> > &coinTable, std::vector<int> &coins, unsigned int i, unsigned int j, bool ownTurn) {
    int leftCoin = coins.at(i);
    int rightCoin = coins.at(coinTable.size() - j);
    if (i + j == coinTable.size() - 1) {
        return std::max(leftCoin, rightCoin);
    }
    int leftCoinTake = coinTable.at(i + 1).at(j) + leftCoin;
    int rightCoinTake = coinTable.at(i).at(j + 1) + rightCoin;
    int enemyMove = std::min(coinTable.at(i + 1).at(j), coinTable.at(i).at(j + 1));
    return ownTurn ? std::max(leftCoinTake, rightCoinTake) : enemyMove;
}


int maxCoinValue(unsigned int numCoins, std::vector<int>& coins) {
    if (coins.size() == 1) {
        return coins.at(0);
    }

    if (coins.size() == 2) {
        return std::max(coins.at(0), coins.at(1));
    }

    bool ownTurn = true;
    std::vector<std::vector<int> > coinTable(numCoins - 1, std::vector<int>(numCoins - 1));

    for (int i = numCoins - 2; i >= 0; i--) {
        unsigned int x = 0;
        unsigned int y = (unsigned int) i;
        for (unsigned int j = 0; j <= i; j++) {
            coinTable.at(y).at(x) = getValue(coinTable, coins, y, x, ownTurn);
            ++x;
            y--;
        }
        ownTurn = !ownTurn;
    }
    int finalVal = coinTable.at(0).at(0);
    int sum = std::accumulate(coins.begin(), coins.end(), 0);
    if (coins.size() % 2 == 0) {
        return finalVal;
    } else {
        return sum - finalVal;
    }
}


int main(int argc, char *argv[]) {
    int numTests;
    std::cin >> numTests;
    for (int i = 0; i < numTests; i++) {
        unsigned int numCoins;
        std::cin >> numCoins;
        std::vector<int> coins(numCoins);
        for (unsigned int j = 0; j < numCoins; j++) {
            std::cin >> coins.at(j);
        }
        std::cout << maxCoinValue(numCoins, coins) << std::endl;
    }
}
