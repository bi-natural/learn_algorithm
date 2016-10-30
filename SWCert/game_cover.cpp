#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

char board[20][20];

const int coverType[4][3][2] = { 
    { { 0, 0}, {1, 0}, {0, 1} }, // |-
    { { 0, 0}, {0, 1}, {1, 1} }, // -|
    { { 0, 0}, {1, 0}, {1, 1} }, // L
    { { 0, 0}, {1, 0}, {1, -1} } 
};

struct position {
    int x, y;
};

bool do_cover(const int& X, const int& Y, const int& x, const int& y, const int& type) 
{
    bool setterable = false;

    for (int i = 0; i < 3; i++) {
        int nx = x + coverType[type][i][0];
        int ny = y + coverType[type][i][1];

        if (nx < 0 || nx >= X || ny < 0 || ny >= Y)
            return setterable;
        if (board[nx][ny] != '.')
            return setterable;
    }

    for (int i = 0; i < 3; i++) {
        int nx = x + coverType[type][i][0];
        int ny = y + coverType[type][i][1];

        board[nx][ny] = 'o';
    }
    return true;
}

void undo_cover(const int& X, const int& Y, const int& x, const int& y, const int& type) 
{
    for (int i = 0; i < 3; i++) {
        int nx = x + coverType[type][i][0];
        int ny = y + coverType[type][i][1];

        board[nx][ny] = '.';
    }
}

int run_algorithm(const int& X, const int& Y)
{
    position findFirstFree = { -1, -1 };

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (board[x][y] == '.') {
                findFirstFree.x = x;
                findFirstFree.y = y;
                break;
            }
        }
        if (findFirstFree.x != -1) 
        break;
    }

    if (findFirstFree.x == -1) { return 1; }

    int result = 0;
    for (int i = 0; i < 4; i++) {
        if (do_cover(X, Y, findFirstFree.x, findFirstFree.y, i))
        {
            result += run_algorithm(X, Y);
            undo_cover(X, Y, findFirstFree.x, findFirstFree.y, i);
        }
    }

    return result;
}

int main()
{
    clock_t begin = clock();

    ios_base::sync_with_stdio(false);
    freopen("data/game_cover.dat", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int X, Y;

        cin >> X >> Y;

        for (int x = 0; x < X; x++)
            for (int y = 0; y < Y; y++) {
                cin >> board[x][y];
            }


        int left_space = 0;
        
        for (int x = 0; x < X; x++) 
            for (int y = 0; y < Y; y++)
                if (board[x][y] == '.') 
                    left_space++;

        cout << "DEBUG: left_space " << left_space << endl;

        if (left_space%3)
            cout << 0 << endl;
        else {
            int result = run_algorithm(X, Y);

            for (int x = 0; x < X; x++) {
                for (int y = 0; y < Y; y++) {
                    cout << board[x][y];
                }
                cout << endl;
            }


            cout << result << endl;
        }
    }

    clock_t end = clock();
    cout << (end - begin)/double(CLOCKS_PER_SEC) << " sec" << endl;
}