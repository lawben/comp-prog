#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>


u_int64_t misplacements = 0;

void merge(std::vector<int> &toMerge, u_int64_t left, u_int64_t right) {
    std::vector<int> merged(right - left + 1);
    u_int64_t i = left;
    u_int64_t middle = (left + right) / 2;
    u_int64_t j = middle + 1;
    u_int64_t insertPos = 0;

    while (i <= middle && j <= right) {
        if (toMerge.at(i) >= toMerge.at(j)) {
            merged.at(insertPos) = toMerge.at(i);
            i++;
        } else {
            merged.at(insertPos) = toMerge.at(j);
            misplacements += middle - i + 1;
            j++;
        }
        insertPos++;
    }
    for (; i <= middle; i++) {
        merged.at(insertPos) = toMerge.at(i);
        insertPos++;
    }
    for (; j <= right; j++) {
        merged.at(i + j - middle - 1 - left) = toMerge.at(j);
        insertPos++;
    }

    for (int k = 0; k < right - left + 1; k++) {
        toMerge.at(k + left) = merged.at(k);
    }
}

void mergesort(std::vector<int>& toMerge, u_int64_t left, u_int64_t right) {
    if (right <= left) {
        return;
    }
    u_int64_t middle = (left + right) / 2;
    mergesort(toMerge, left, middle);
    mergesort(toMerge, middle + 1, right);
    merge(toMerge, left, right);
}

u_int64_t countMisplacements(std::vector<int> &input) {
    misplacements = 0;
    mergesort(input, 0, input.size() - 1);
    return misplacements;
}

int main(int argc, char* argv[]) {
    int numTests;
    std::cin >> numTests;

    for (int i = 0; i < numTests; i++) {
        unsigned int sequenceLength;
        std::cin >> sequenceLength;
        std::vector<int> sequence(sequenceLength);
        for (unsigned int j = 0; j < sequenceLength; j++) {
            std::cin >> sequence.at(j);
        }

        std::cout << countMisplacements(sequence) << std::endl;
    }
}