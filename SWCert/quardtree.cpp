#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

const int MAX_SIZE = 20;

char decompressed[MAX_SIZE][MAX_SIZE];

vector<char> flip_over_uncompress(vector<char>::iterator& iter)
{
    char head = *iter++;

    if (head == 'b' || head == 'w') {
        return vector<char>(1, head);
    }

    vector<char> q1 = flip_over_uncompress(iter);
    vector<char> q2 = flip_over_uncompress(iter);
    vector<char> q3 = flip_over_uncompress(iter);
    vector<char> q4 = flip_over_uncompress(iter);

    vector<char>result;

    result.push_back('x');
    result.insert(result.end(), q3.begin(), q3.end());
    result.insert(result.end(), q4.begin(), q4.end());
    result.insert(result.end(), q1.begin(), q1.end());
    result.insert(result.end(), q2.begin(), q2.end());

    return result;
}

void flip_bottom_up(int size)
{
    for (int y = 0; y < size/2; y++) {
        for (int x = 0; x < size; x++) {
            swap(decompressed[y][x], decompressed[size-y-1][x]);
        }
    }
}

int findSize(vector<char>::iterator& iter, const vector<char>::iterator& end)
{
    if (iter == end)
        return 0;

    char head = *iter++;

    if (head == 'w' || head == 'b') {
        return 1;
    }
    else if (head == 'x') {
        int max_v = -1;

        for (int i = 0; i < 4; i++) {
            int n = findSize(iter, end);

            max_v = max(max_v, n);
        }

        return 2*max_v;
    }
    else {
        return 0;
    }
}

void decode(vector<char>::iterator& iter, const vector<char>::const_iterator& end, int x, int y, const int& size)
{
    char head = *iter++;

    if (head == 'b' || head == 'w') {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                decompressed[y+i][x+j] = (head == 'b') ? 'b' : 'w';
            }
        }
        return;
    }
    else {
        int half = size/2;

        decode(iter, end, x, y, half);
        decode(iter, end, x+half, y, half);
        decode(iter, end, x, y+half, half);
        decode(iter, end, x+half, y+half, half);
    }
}

vector<char> encode(int x, int y, const int& size)
{
    if (size <= 1) {
        return vector<char>(1, decompressed[y][x]);
    }

    int half = size/2;

    vector<char> q1 = encode(x, y, half);
    vector<char> q2 = encode(x + half, y, half);
    vector<char> q3 = encode(x, y+half, half);
    vector<char> q4 = encode(x+half, y+half, half);

    if (q1[0] == q2[0] && q1[0] == q3[0] && q1[0] == q4[0])
    {
        return vector<char>(1, q1[0]);
    }

    vector<char> result;

    result.push_back('x');
    result.insert(result.end(), q1.begin(), q1.end());
    result.insert(result.end(), q2.begin(), q2.end());
    result.insert(result.end(), q3.begin(), q3.end());
    result.insert(result.end(), q4.begin(), q4.end());

    return result;
}

int main() 
{
    ios_base::sync_with_stdio(false);

    freopen("data/quardtree.dat", "r", stdin);

    cin >> N;
    cin.ignore(1, '\n');
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);

        vector<char> a(line.begin(), line.end());
        vector<char>::iterator iter = a.begin();

        int n = findSize(iter, a.end());
        cout << "DEBUG: findSize() " << n << endl;

        // vector<char> b = flip_bottom_up(a);
        iter = a.begin();
        decode(iter, a.end(), 0, 0, n);

        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                cout << decompressed[y][x];
            }
            cout << endl;
        }

        vector<char> b = encode(0, 0, n);
        cout << "DEBUG: Original Encode" << endl;
        for (int i = 0; i < b.size(); i++) {
            cout << b[i];
        }
        cout << endl;

        iter = a.begin();
        vector<char> c = flip_over_uncompress(iter);

#if 0
        flip_bottom_up(n);

        vector<char> c = encode(0, 0, n);
#endif
        cout << "DEBUG: After Flip Encode" << endl;
        for (int i = 0; i < c.size(); i++) {
            cout << c[i];
        }
        cout << endl;

#if 0
        cout << "#" << i+1 << " "
        for (int j = 0; j < b.size(); ++j) {
            cout << b[j];
        }
        cout << endl;
#endif
    }
}