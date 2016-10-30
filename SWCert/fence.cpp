#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

int findMaxRec_BF(const vector<int>& v) 
{
    int ret = 0;
    
    for (int left = 0; left < v.size(); ++left) {
        int min_h = v[left];
        for (int right = left; right < v.size(); ++right) {
            min_h = min(min_h, v[right]);
            ret = max(ret, min_h*(right-left+1));
        }
    }
    return ret;
}

int findMaxRec_DC(const vector<int>& v, int left, int right)
{
    if (left == right) { return v[left]; }

    int mid = left + (right - left) / 2;

    int ret = max ( findMaxRec_DC(v, left, mid), findMaxRec_DC(v, mid+1, right) );

    int to_1 = mid, to_N = mid + 1;
    int min_h = min(v[to_1], v[to_N]);
    int width = 2;
    
    ret = max ( min_h * width, ret);
    while (to_1 != left || to_N != right) {        
        if (to_1 == left) { 
            min_h = min(min_h, v[++to_N]);
        }
        else if (to_N == right) {
            min_h = min(min_h, v[--to_1]);
        }
        else if (v[to_1] < v[to_N]) {
            min_h = min(min_h, v[++to_N]);
        }
        else {
            min_h = min(min_h, v[--to_1]);
        }

        ret = max(ret, min_h * (++width));
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("data/fence.dat", "r", stdin);

    cin >> N;
    cin.ignore(1, '\n');
    for (int i = 0; i < N; i++) {
        int fn;
        cin >> fn;

        vector<int> v;
        for (int j = 0; j < fn; j++) {
            int n1;

            cin >> n1;
            v.push_back(n1);
        }

        int result = findMaxRec_BF(v);

        cout << '#' << i+1 << " " << result << endl;

        result = findMaxRec_DC(v, 0, v.size() -1);

        cout << '#' << i+1 << " " << result << endl;

    }
}
