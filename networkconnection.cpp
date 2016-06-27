#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef vector<vector<pair<int, int>>> vvpi;
typedef unsigned long long ull;

ull minimumCableLength(const unsigned int num_cities, vvpi &highways, int start) {
    ull length = 0;
    unsigned int num_seen = 0;
    bool seen[num_cities];
    int costs[num_cities];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> to_visit;

    for (int i = 0; i < num_cities; ++i) {
        seen[i] = false;
        costs[i] = INT32_MAX;
    }

    to_visit.push(make_pair(0, start));
    while (num_seen < num_cities && !to_visit.empty()) {
        pair<int, int> weightTo = to_visit.top();
        to_visit.pop();
        int weight = weightTo.first;
        int city = weightTo.second;
        if (seen[city]) continue;

        for (pair<int, int> edge : highways[city]) {
            int to = edge.first;
            int cost = edge.second;

            if (!seen[to]) {
                if (cost < costs[to]) {
                    to_visit.push(make_pair(cost, to));
                    costs[to] = cost;
                }
            }
        }

        length += weight;
        seen[city] = true;
        num_seen += 1;
    }

    return length;
}


int main() {
//    unsigned int num_cities, num_highways;
//    cin >> num_cities >> num_highways;
//    vvpi highways(num_cities);
//    unsigned int a, b, w;
//    for (int i = 0; i < num_highways; i++) {
//        cin >> a >> b >> w;
//        highways.at(a).push_back(make_pair(b, w));
//        highways.at(b).push_back(make_pair(a, w));
//    }
//
//    ull length = minimumCableLength(num_cities, highways, a);
//    cout << length << endl;

    int array[] = {2, 3, 4};
    int other_array[4] = {0, 2, 3, 4};
    int n = 3;
    n++;
    for (int j = 0; j < n; j++) {
        cout << other_array[j] << " and ";
        cout << array[j] << endl;
    }
}

