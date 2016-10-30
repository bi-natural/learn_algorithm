#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int vi[] = { 1, 2, 3, 4, 5 };
vector<int> v(vi, vi + sizeof(vi)/sizeof(int));

int main()
{
    sort(v.begin(), v.end());

    ios_base::sync_with_stdio(false);
    do {
        for (int i = 0; i < v.size(); i++) 
            cout << v[i] ;
        cout << endl;
    } while(next_permutation(v.begin(), v.end()));
}