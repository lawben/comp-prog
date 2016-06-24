#include <iostream>
#include <vector>

using namespace std;

bool is_connected(int a, int b, vector<int> &parents) {
    bool is_conn = false;
    int parent_a = parents.at(a);
    int parent_b = parents.at(b);
    if (parent_a == parent_b) {
        is_conn = true;
    } else if (parent_a == b) {
        is_conn = true;
    } else if (parent_b == a) {
        is_conn = true;
    }

    return is_conn;
}

void print_vector(vector<int> &parents) {
    for (int i = 0; i < parents.size(); ++i) {
        cout << parents.at(i) << " ";
    }
    cout << endl;
}


void build(int a, int b, vector<vector<int>> &children, vector<int> &parents) {
    if (is_connected(a, b, parents)) {
        return;
    }

    int parent_a = parents.at(a);
    int parent_b = parents.at(b);
    unsigned long num_children_a = children.at(parent_a).size();
    unsigned long num_children_b = children.at(parent_b).size();

    if (num_children_a > num_children_b) {
        children.at(parent_a).insert(children.at(parent_a).end(), children.at(parent_b).begin(), children.at(parent_b).end());
        for (int i = 0; i < num_children_b; ++i) {
            parents.at(children.at(parent_b).at(i)) = parent_a;
        }
        children.at(parent_b).clear();
    } else {
        children.at(parent_b).insert(children.at(parent_b).end(), children.at(parent_a).begin(), children.at(parent_a).end());
        for (int i = 0; i < num_children_a; ++i) {
            parents.at(children.at(parent_a).at(i)) = parent_b;
        }
        children.at(parent_a).clear();
    }
}

void print_if_connected(int a, int b, vector<int> &parents) {
    cout << (is_connected(a, b, parents) ? 1 : 0) << endl;
}

int main() {

    int num_islands, m;
    string task_req;
    cin >> num_islands >> m;

    vector<vector<int>> children(num_islands);
    vector<int> parents(num_islands);
    for (int j = 0; j < num_islands; ++j) {
        children.at(j) = vector<int>();
        children.at(j).push_back(j);
        parents.at(j) = j;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> task_req >> a >> b;
        if (task_req.compare("build") == 0) {
            build(a, b, children, parents);
        } else {
            print_if_connected(a, b, parents);
        }
    }
}