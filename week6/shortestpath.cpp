#include <iostream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

char DELIM = ' ';

void findShortestPaths(const int numVertices, vector<tuple<int, int, int>> &edges, vector<pair<int, int>> &pairs) {
    u_int64_t dists[numVertices][numVertices];
    u_int64_t max = numeric_limits<u_int64_t>::max();

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            dists[i][j] = max;
            dists[j][i] = max;
        }
    }

    for (auto edge : edges) {
        int a, b;
        u_int64_t dist;
        tie(a, b, dist) = edge;
        dists[a][b] = dist;
        dists[b][a] = dist;
    }

    for (int k = 0; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; ++j) {
                if (dists[i][k] == max || dists[k][j] == max) {
                    continue;
                }
                u_int64_t newDist = dists[i][k] + dists[k][j];
                if (dists[i][j] > newDist) {
                    dists[i][j] = newDist;
                    dists[j][i] = newDist;
                }
            }
        }
    }

    for (auto pair : pairs) {
        cout << dists[pair.first][pair.second] << endl;
    }
}


int main() {
    int numVertices, numEdges, numPairs;
    string useless;

    cin >> numVertices >> numEdges >> numPairs;
    getline(cin, useless);

    map<string, int> vertices;
    vector<tuple<int, int, int>> edges(numEdges);
    vector<pair<int, int>> pairs(numPairs);


    for (int n = 0; n < numVertices; n++) {
        string vertex;
        getline(cin, vertex);
        if (vertex.at(0) == '\n')
            vertex = vertex.erase(0, 1);
        vertices.insert(make_pair(vertex, n));
    }

    string a, b;
    for (int m = 0; m < numEdges; m++) {
        int distance;
        int vertexA, vertexB;

        getline(cin, a, DELIM);
        getline(cin, b, DELIM);
        cin >> distance;

        if (a.at(0) == '\n')
            a = a.erase(0, 1);
        if (b.at(0) == '\n')
            b = b.erase(0, 1);

        vertexA = vertices[a];
        vertexB = vertices[b];
        edges.at(m) = (make_tuple(vertexA, vertexB, distance));
    }

    for (int k = 0; k < numPairs; k++) {
        int vertexA, vertexB;
        getline(cin, a, DELIM);
        getline(cin, b);

        if (a.at(0) == '\n')
            a = a.erase(0, 1);
        if (b.at(0) == '\n')
            b = b.erase(0, 1);

        vertexA = vertices[a];
        vertexB = vertices[b];


        pairs.at(k) = (make_pair(vertexA, vertexB));
    }

    findShortestPaths(numVertices, edges, pairs);
    return 0;
}

