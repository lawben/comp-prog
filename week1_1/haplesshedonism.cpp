#include <iostream>
#include <math.h>

using namespace std;

long long trianglesFromSticks(long long n) {
    long long firstTerm = n * n * n * 2;
    long long secondTerm = 9 * n * n;
    long long thirdTerm = 10 * n;
    return static_cast<long long int>(floorl((firstTerm - secondTerm + thirdTerm) / 24));
}

int main(int argc, char *argv[]) {
    unsigned int amountTest;
    cin >> amountTest;
    for (unsigned int i = 0; i < amountTest; ++i) {
        long long numSticks;
        cin >> numSticks;
        cout << trianglesFromSticks(numSticks) << endl;
    }
}
