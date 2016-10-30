#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> c(a.size() + b.size() + 1, 0);

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i+j] += (a[i] * b[j]);
        }
    }

    for (int i = 0; i < c.size()-1; ++i) {
        int div = c[i] / 10;

        c[i] = c[i] % 10;
        c[i+1] += div;
    }

    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
        
    return c;
}

int main() 
{
    ios_base::sync_with_stdio(false);

    const int va[] = { 4, 3, 2, 1 };
    const int vb[] = { 8, 7, 6, 5 };

    vector<int> a(va, va + sizeof(va)/sizeof(int));
    vector<int> b(vb, vb + sizeof(vb)/sizeof(int));

    vector<int> c = multiply(a, b);

    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    cout << endl;
}