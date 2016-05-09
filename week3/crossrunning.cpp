#include <iostream>

unsigned int findWaterObstacle(unsigned int numPoints, unsigned int *points, unsigned int start, unsigned int end) {
    if (end == start) {
        return points[start];
    }
    if (end - start == 1) {
        return std::min(points[start], points[end]);
    }

    unsigned int first = points[start];
    unsigned int last = points[end];
    unsigned int midPos = (start + end) / 2;
    unsigned int mid = points[midPos];

    if (mid < points[midPos + 1] && mid < points[midPos - 1]) {
        return mid;
    }

    if (first < last) {
        if (first < points[start + 1]) {
            return first;
        } else {
            if (mid < first) {
                if (points[midPos - 1] > mid) {
                    return findWaterObstacle(numPoints, points, midPos, end);
                } else {
                    return findWaterObstacle(numPoints, points, start, midPos);
                }
            } else {
                return findWaterObstacle(numPoints, points, start, midPos);
            }
        }
    } else {
        if (last < points[end - 1]){
            return last;
        } else {
            if (mid < last) {
                if (points[midPos - 1] > mid) {
                    return findWaterObstacle(numPoints, points, midPos, end);
                } else {
                    return findWaterObstacle(numPoints, points, start, midPos);
                }
            } else {
                return findWaterObstacle(numPoints, points, midPos, end);
            }
        }
    }
}


int main(int argc, char *argv[]) {

    unsigned int numPoints;
    std::cin >> numPoints;
    unsigned int points[numPoints];

    for (unsigned int i = 0; i < numPoints; ++i) {
        std::cin >> points[i];
    }

    std::cout << findWaterObstacle(numPoints, points, 0, numPoints - 1) << std::endl;
}
