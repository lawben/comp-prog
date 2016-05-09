#include <string>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const map<char, char> makeMirrorMap() {
    map<char, char> mirrorChars;
    mirrorChars['A'] = 'A';
    mirrorChars['E'] = '3';
    mirrorChars['H'] = 'H';
    mirrorChars['I'] = 'I';
    mirrorChars['J'] = 'L';
    mirrorChars['L'] = 'J';
    mirrorChars['M'] = 'M';
    mirrorChars['O'] = 'O';
    mirrorChars['S'] = '2';
    mirrorChars['T'] = 'T';
    mirrorChars['U'] = 'U';
    mirrorChars['V'] = 'V';
    mirrorChars['W'] = 'W';
    mirrorChars['X'] = 'X';
    mirrorChars['Y'] = 'Y';
    mirrorChars['Z'] = '5';
    mirrorChars['1'] = '1';
    mirrorChars['2'] = 'S';
    mirrorChars['3'] = 'E';
    mirrorChars['5'] = 'Z';
    mirrorChars['8'] = '8';
    return mirrorChars;
};

bool palindromeCheck(string word) {
    string reversed = word;
    reverse(reversed.begin(), reversed.end());
    return reversed == word;
}

bool mirrorCheck(string word) {
    const char *wordChar = word.c_str();
    const char *leftOffset, *rightOffset;
    map<char, char> mirrorChars = makeMirrorMap();
    map<char, char>::iterator notFound = mirrorChars.end();

    unsigned long wordLength = word.length();
    leftOffset = wordChar + (wordLength / 2) - 1;
    rightOffset = wordChar + (wordLength / 2);
    unsigned long charsLeft = wordLength / 2;

    if (wordLength % 2 == 1) {
        map<char, char>::iterator middleChar = mirrorChars.find(*rightOffset);
        if (middleChar == notFound) {
            return false;
        } else if (middleChar->first != middleChar->second) {
            return false;
        }
        rightOffset++;
    }



    while (charsLeft > 0) {
        map<char, char>::iterator leftChar = mirrorChars.find(*leftOffset);
        map<char, char>::iterator rightChar = mirrorChars.find(*rightOffset);

        if (leftChar != notFound && rightChar != notFound) {
            if (leftChar->second != *rightOffset || rightChar->second != *leftOffset) {
                return false;
            }
        } else {
            return false;
        }

        leftOffset--;
        rightOffset++;
        charsLeft--;
    }

    return true;
}

void wordCheck(string word) {
    bool isPalindrome = palindromeCheck(word);
    bool isMirrored = mirrorCheck(word);
    string text;

    if (isMirrored && isPalindrome) {
        text = " -- is a mirrored palindrome.";
    } else if (isMirrored) {
        text = " -- is a mirrored string.";
    } else if (isPalindrome) {
        text = " -- is a regular palindrome.";
    } else {
        text = " -- is not a palindrome.";
    }
    cout << word << text << endl;
}

int main(int argc, char *argv[]) {
    unsigned int amountTests;
    cin >> amountTests;
    for (unsigned int i = 0; i < amountTests; ++i) {
        string word;
        cin >> word;
        wordCheck(word);
    }
}