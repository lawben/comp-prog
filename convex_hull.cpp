#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;


struct Point
{
    int x, y;
};

float cotan(Point &p1, Point &p2) {
    return static_cast<float>(p2.x - p1.x) / (p2.y - p1.y);
}

int dist(Point &p1, Point &p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

int ccw(Point p1, Point p2, Point p3)
{
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0) return 0;  // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool comparePoints(Point &p1, Point &p2, Point reference) {
    if (p1.y == reference.y && p2.y == reference.y) {
        return dist(p1, reference) < dist(p2, reference);
    } else if (p1.y == reference.y) {
        return false;
    } else if (p2.y == reference.y) {
        return true;
    } else {
        float cotan_p1 = cotan(reference, p1);
        float cotan_p2 = cotan(reference, p2);
        if (cotan_p1 == cotan_p2) {
            return dist(p1, reference) < dist(p2, reference);
        }
        return cotan_p1 < cotan_p2;
    }
}

bool onSegment(Point &p, Point &q, Point &r)
{
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);

}

bool doIntersect(Point &p1, Point &q1, Point &p2, Point &q2)
{
    int o1 = ccw(p1, q1, p2);
    int o2 = ccw(p1, q1, q2);
    int o3 = ccw(p2, q2, p1);
    int o4 = ccw(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    return o4 == 0 && onSegment(p2, q1, q2);
}

class PointSorter
{
    Point point_;
public:
    PointSorter(Point point){ point_ = point; }
    int operator()(Point p1, Point p2) const {
        return comparePoints(p1 , p2 , point_);
    }
};

vector<pair<Point, Point>> find_convex_hull(vector<Point> &points) {
    Point lowest = points.at(0);
    long size = points.size();
    int index = 0;
    for (int i = 1; i < size; ++i) {
        Point current = points.at(i);
        if (current.y < lowest.y) {
            lowest = current;
            index = i;
        } else if (current.y == lowest.y && current.x < lowest.x) {
            index = i;
            lowest = current;
        }
    }
    // Swap lowest point to the beginning of the list
    Point tmp = points.at(0);
    points.at(0) = lowest;
    points.at(index) = tmp;
    sort(++points.begin(), points.end(), PointSorter(lowest));

    int m = 1;
    for (int j = 1; j < size; ++j) {
        while (j < size-1 && ccw(lowest, points[j], points[j+1]) == 0) {
            j++;
        }
        points.at(m++) = points[j];
    }

    if (m < 3) {
        vector<pair<Point, Point>> hull;
        hull.push_back(make_pair(points[0], points[1]));
        return hull;
    }

    stack<Point> hull;
    hull.push(points.at(0));
    hull.push(points.at(1));
    hull.push(points.at(2));

    for (int i = 3; i < m; i++) {
        Point top = hull.top();
        hull.pop();
        while (ccw(hull.top(), top, points[i]) != 1)   {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }

    vector<pair<Point, Point>> hull_edges(hull.size() - 1);
    Point prev = hull.top();
    Point first = Point{prev.x, prev.y};

    hull.pop();
    while (!hull.empty())
    {
        Point curr = hull.top();
        hull.pop();
        hull_edges.push_back(make_pair(prev, curr));
        prev = curr;
    }
    hull_edges.push_back(make_pair(first, prev));

    return hull_edges;
}


void flies_across(vector<pair<Point, Point>> &hull, pair<Point, Point> &flight) {
    bool has_intersection = false;
    for (int j = 0; j < hull.size(); ++j) {
        pair<Point, Point> edge = hull.at(j);
        if (doIntersect(edge.first, edge.second, flight.first, flight.second)) {
            cout << "PUNISH" << endl;
            has_intersection = true;
            break;
        }
    }
    if (!has_intersection) {
        cout << "HONEST" << endl;
    }
}


int main() {

    ios::sync_with_stdio(false);

    int num_tests;
    cin >> num_tests;


    for (int i = 0; i < num_tests; ++i) {
        int n, m;
        cin >> n >> m;
        vector<Point> trees(n);
        for (int j = 0; j < n; ++j) {
            int x, y;
            cin >> x >> y;
            trees.at(j) = Point{x, y};
        }
        vector<pair<Point, Point>> hull = find_convex_hull(trees);
        for (int k = 0; k < m; ++k) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Point from = Point{x1, y1};
            Point to = Point{x2, y2};
            pair<Point, Point> flight = make_pair(from, to);
            flies_across(hull, flight);
        }
    }

}

//int main(int argc, char *argv[]) {
//    Point points[] = {{6, 4},
//                      {0, 0},
//                      {1, 1},
//                      {1, 3},
//                      {2, 1},
//                      {3, 1},
//                      {3, 0}};
//
//    vector<Point> bulb(points, points + sizeof points / sizeof points[0]);
//    vector<pair<Point, Point>> hull = find_convex_hull(bulb);
//
//    vector<pair<Point, Point>> flights;
//    flights.push_back(make_pair(Point{0, 4}, Point{5, 4}));
//    flights.push_back(make_pair(Point{0, 2}, Point{5, 2}));
//    flights.push_back(make_pair(Point{3, 0}, Point{0, 3}));
//    flights.push_back(make_pair(Point{4, 0}, Point{4, 5}));
//
//
//    for (int i = 0; i < flights.size(); ++i) {
//        pair<Point, Point> flight = flights.at(i);
//        bool has_intersection = false;
//        for (int j = 0; j < hull.size(); ++j) {
//            pair<Point, Point> edge = hull.at(j);
//            if (doIntersect(edge.first, edge.second, flight.first, flight.second)) {
//                cout << "intersect" << endl;
//                has_intersection = true;
//                break;
//            }
//        }
//        if (!has_intersection) {
//            cout << "no intersect" << endl;
//        }
//    }
//}
