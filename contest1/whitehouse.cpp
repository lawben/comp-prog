#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

typedef vector<vector<int>> Graph;

class Node {
    Node &parent;
public:
    Node() : parent(*this) {}
    Node *getParent() { return &parent; }
    void setParent(Node &newParent) { this->parent = newParent; }

    bool operator==(const Node &rhs) {
        return this == &rhs;
    }
};

Node makeSet(int x) {
    return Node();
}

Node find(Node &x) {
    Node *parent = x.getParent();
    if (parent == &x) {
        return x;
    } else {
        return find(*parent);
    }
}

void unionSets(Node &x, Node &y) {
    Node xRoot = find(x);
    Node yRoot = find(y);
    xRoot.setParent(yRoot);
}


vector<pair<int, int>> findCriticalRooms(int numRooms, Graph &whitehouse, vector<vector<int>> &circles) {
    vector<pair<int, int>> criticals;
    for (int i = 0; i < numRooms; i++) {
        vector<int> room = whitehouse.at(i);
        vector<int>::iterator firstDoor = room.begin();
        vector<int>::iterator notFound = room.end();

        if (firstDoor == notFound) {
            continue;
        }

        for (int j = 0; j < room.size(); j++) {
            if (find(room.begin(), room.end(), j) != room.end()) {
                continue;
            } else {
                int firstDoorTo = *firstDoor;
                if (++firstDoor == notFound) {
                    criticals.push_back(make_pair(min(firstDoorTo, i), max(firstDoorTo, i)));
                    room.clear();
                    whitehouse.at(i) = room;
                    vector<int> otherRoom = whitehouse.at(firstDoorTo);
                    otherRoom.erase(std::remove(otherRoom.begin(), otherRoom.end(), i), otherRoom.end());
                    whitehouse.at(firstDoorTo) = otherRoom;
                }
            }
        }
    }

    return criticals;
}

void findCircles(Graph &whitehouse, vector<vector<int>> &circles, int numRooms) {
    vector<Node> nodes(numRooms);
    vector<bool> nodeExists(numRooms, false);
    for (int i = 0; i < numRooms; i++) {
        vector<int> room = whitehouse.at(i);
        Node x = makeSet(i);
        nodes.at(i) = x;

        for (int j = 0; j < room.size(); j++) {
            Node y;
            if (nodeExists.at(j)) {
                y = nodes.at(j);
            } else {
                y = makeSet(j);
                nodes.at(j) = y;
                nodeExists.at(j) = true;
            }

            Node rootX = find(x);
            Node rootY = find(y);
            if (&rootX == &rootY) {
                circles.at(i).push_back(j);
                circles.at(j).push_back(i);
            } else {
                unionSets(x, y);
            }
        }
    }
}

bool smallerPair(pair<int, int> i, pair<int, int> j) {
    bool firstEqual = i.first == j.first;
    if (firstEqual) {
        return i.second < j.second;
    }

    return i.first < j.first;
}

int main(int argc, char* argv[]) {
    int numTests;
    cin >> numTests;

    for (int t = 0; t < numTests; ++t) {
        int numRooms, numDoors;
        cin >> numRooms >> numDoors;
        Graph whitehouse(numRooms);

        for (int d = 0; d < numDoors; ++d) {
            int r1, r2;
            cin >> r1 >> r2;
            r1--;
            r2--;
            whitehouse.at(r1).push_back(r2);
            whitehouse.at(r2).push_back(r1);
        }

        vector<vector<int>> circles(numRooms, -1);
        findCircles(whitehouse, circles, numRooms);

        vector<pair<int, int>> critialRooms = findCriticalRooms(numRooms, whitehouse, circles);
        bool foundNew = !critialRooms.empty();

        while (foundNew) {
            vector<pair<int, int>> newCriticalRooms = findCriticalRooms(numRooms, whitehouse, circles);
            if (newCriticalRooms.empty()) {
                foundNew = false;
                break;
            }

            critialRooms.insert(critialRooms.end(), newCriticalRooms.begin(), newCriticalRooms.end());
        }

        cout << critialRooms.size() << endl;
        sort(critialRooms.begin(), critialRooms.end(), smallerPair);
        for (int i = 0; i < critialRooms.size(); i++) {
            pair<int, int> door = critialRooms.at(i);
            cout << door.first + 1 << " " << door.second + 1 << endl;
        }
    }

}
