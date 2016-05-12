#include <iostream>
#include <cstring>

using namespace std;

bool calculated[101][10];
unsigned long long int values[101][10];

unsigned long long int amountTightWords(int wordLength, int alphabetDigit, int maxDigit) {
    if (wordLength < 0 || alphabetDigit < 0 || alphabetDigit > maxDigit) {
        return 0;
    }
    if (wordLength == 1) {
        return 1;
    }
    if (calculated[wordLength][alphabetDigit]) {
        return values[wordLength][alphabetDigit];
    }

    values[wordLength][alphabetDigit] = ( amountTightWords(wordLength - 1, alphabetDigit, maxDigit) +
                                          amountTightWords(wordLength - 1, alphabetDigit - 1, maxDigit) +
                                          amountTightWords(wordLength - 1, alphabetDigit + 1, maxDigit) ) % 100003;

    calculated[wordLength][alphabetDigit] = true;
    return values[wordLength][alphabetDigit];
}

int main(int argc, char* argv[]) {
    int numTests = 100;
    cin >> numTests;

    for (int t = 0; t < numTests; ++t) {
        int wordLength, alphabetSize;
        cin >> alphabetSize >> wordLength;

        memset(calculated, false, sizeof(calculated));
        unsigned long long int sum = 0;
        for (int i = 0; i <= alphabetSize; ++i) {
            unsigned long long int num = amountTightWords(wordLength, i, alphabetSize);
            sum += amountTightWords(wordLength, i, alphabetSize);
        }

        unsigned long long int result = sum % 100003;
        cout << result << endl;
    }
}
