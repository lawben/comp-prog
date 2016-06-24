#include <iostream>

#define INF 1000000000

using namespace std;
typedef long long int ll;


struct position {
    int x;
    int y;
    position(int x, int y) : x(x), y(y) {};
};

template <int N> struct Grid {
    ll grid[N][N][N][N];
};

template <int N> struct Grid2D {
    ll grid[N][N];
};


bool isvalid(position p, int gridsize) {
    return !(p.x < 0 || p.y < 0 || p.x >= gridsize || p.y >= gridsize);
}

bool found_end(position first, position second, int gridsize) {
    if (!(first.x == gridsize-1 && first.y == gridsize-1)) {
        return false;
    }
    return second.x == 0 && second.y == 0;
}

template <int N>
ll get_max(position first, position second, Grid<N> &dp, Grid2D<N> &grid, int gridsize) {
    // if P1 or P2 is at an invalid cell
    if (!isvalid(first, gridsize) || !isvalid(second, gridsize)) return -INF;
    if (found_end(first, second, gridsize)) {
        ll first_val = grid.grid[first.x][first.y];
        ll second_val = grid.grid[second.x][second.y];
        return first_val + second_val;
    }
    if (dp.grid[first.x][first.y][second.x][second.y] != -1) {
        return dp.grid[first.x][first.y][second.x][second.y];
    }
    ll ans =  -INF;
    ll value_this_move;
    if (first.x == second.x && first.y == second.y) {
        value_this_move =  grid.grid[first.x][first.y];
    } else {
        value_this_move =  grid.grid[second.x][second.y] + grid.grid[first.x][first.y];
    }

//    cout << value_this_move << endl;

    // Add possible next steps
    position first_right = position(first.x + 1, first.y);
    position first_down = position(first.x, first.y + 1);
    position second_left = position(second.x - 1, second.y);
    position second_up = position(second.x, second.y - 1);
    ans = max(ans, value_this_move + get_max<N>(first_right, second_up, dp, grid, gridsize));
    ans = max(ans, value_this_move + get_max<N>(first_right, second_left, dp, grid, gridsize));
    ans = max(ans, value_this_move + get_max<N>(first_down, second_up, dp, grid, gridsize));
    ans = max(ans, value_this_move + get_max<N>(first_down, second_left, dp, grid, gridsize));
//    cout << ans <<endl;

    dp.grid[first.x][first.y][second.x][second.y] = ans;
    return ans;
}


template <int N> ll findMaxTraversal(Grid2D<N> &grid, int gridsize) {
    // Store found value for position of already seen
    //    int ****dp; //[gridsize][gridsize][gridsize][gridsize];
    Grid<N> dp;
    for (int i = 0; i < gridsize; ++i) {
        for (int j = 0; j < gridsize; ++j) {
            for (int k = 0; k < gridsize; ++k) {
                for (int l = 0; l < gridsize; ++l) {
                    dp.grid[i][j][k][l] = -1;
                }
            }
        }
    }
//    memset(dp.grid, -1, sizeof(dp.grid));
    position start1 = position(0, 0);
    position start2 = position(gridsize - 1, gridsize -1);
    return get_max<N>(start1, start2, dp, grid, gridsize);
}

//int main() {
//    int testcases;
//    cin >> testcases;
//    for (int i = 0; i < testcases; i++) {
//        int gridsize;
//        cin >> gridsize;
//        int **grid;
//        for (int i = 0; i < gridsize; i++) {
//            for (int j = 0; j < gridsize; j++) {
//                int val;
//                cin >> val;
//                grid[i][j] = val;
//            }
//        }
//        cout << findMaxTraversal(grid, gridsize - 1) << endl;
//    }
//}

int main() {
    Grid2D<4> test_a = { {0, 5, 0, 10, 5, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1} };

    Grid2D<3> test_b = { {2, 1, 0, 2, 2, 0, 1, 2, 0} };

    int a_res = 26;
    int b_res = 10;
    ll x = findMaxTraversal<3>(test_b, 3);
    cout << x << endl;
}