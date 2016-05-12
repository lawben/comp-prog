#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> Relation;
typedef vector<vector<Relation>> Graph;

void printArray(int size, vector<bool> &array) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int findFriends(const int numPeople, Graph friends) {
    vector<bool> trusted(numPeople, false);
    int amountFriends = 0;
    queue<int> toInspect;

    // Bob is always trusted
    trusted.at(0) = true;
    toInspect.push(0);

    while (!toInspect.empty()) {
        int personId = toInspect.front();
        toInspect.pop();
        for (Relation person : friends.at(personId)) {
            if (person.second >= 3) {
                int id = person.first;
                if (!trusted[id]) {
                    amountFriends++;
                    trusted.at(id) = true;
                    toInspect.push(id);
                }
            }
        }
    }

    return amountFriends;
}

int main(int argc, char* argv[]) {
    int numPeople, numFriendships;
    cin >> numPeople >> numFriendships;

    Graph friends(numPeople);

    for (int i = 0; i < numFriendships; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        friends.at(a).push_back(make_pair(b, c));
        friends.at(b).push_back(make_pair(a, c));
    }

    int amountFriends = findFriends(numPeople, friends);
    cout << amountFriends << endl;
}