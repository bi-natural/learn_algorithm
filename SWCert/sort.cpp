#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int descending(const int& a, const int& b) { return a > b; }

int main()
{
    vector<int> v;

    for (int i = 0; i < 100; i++) {
        int n = rand() % 1000 + 1;

        v.push_back(n);
    }

    ios_base::sync_with_stdio(false);

    sort(v.begin(), v.end());
    for (int i = 0; i < 100; i++) {
        cout << v[i] << ", ";
    }
    cout << endl;

    sort(v.begin(), v.end(), descending);
    for (int i = 0; i < 100; i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}
