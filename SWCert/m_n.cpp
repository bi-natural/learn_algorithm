#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Test>
void test(Test t, int n, int m)
{
    clock_t begin = clock();
    t(n, m);
    clock_t end = clock();
    cout << (end-begin)/double(CLOCKS_PER_SEC) << " sec" << endl;
}

int expect_cases(int n, int m) {
    if (n == m) { return 1; }
    if (m == 1) { return n; }
    return expect_cases(n - 1, m - 1) + expect_cases(n - 1, m);
}

void printOut(vector<int>& A) {
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << ", ";
    }
    cout << endl;
}

void pick_m_n(int n, vector<int>& picked, int toPick) {
    if (toPick <= 0) { printOut(picked); return; }

    int smallest = picked.empty() ? 0 : picked.back() + 1;

    for (int next = smallest; next < n; ++next) {
        picked.push_back(next);
        pick_m_n(n, picked, toPick - 1);
        picked.pop_back();
    }
}

void t_pick_m_n(int n, int m) {
    vector<int> picked;

    cout << "expece_case(" << n << ", " << m << ") = " << expect_cases(n, m) << endl;
    picked.clear();
    pick_m_n(n, picked, m);

}

int main()
{
    ios_base::sync_with_stdio(false);

    test(t_pick_m_n, 4, 2);
}