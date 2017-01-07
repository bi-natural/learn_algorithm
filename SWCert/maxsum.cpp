#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

template <typename Test>
void test (Test t, vector<int>& A)
{
    const clock_t begin = clock();
    t(A);
    const clock_t end = clock();
    cout << (end-begin)/double(CLOCKS_PER_SEC) << " sec\n";
}

const int MIN = numeric_limits<int>::min();

/*
 *  sum [0..N ~ i..N]
 */
int n2_sum(const vector<int>& A) {
    int N = A.size(), ret = MIN;

    for (int i = 0; i < N; ++i) {
        int sum = 0;
        for (int j = i; j < N; ++j) {
            sum += A[j];
            ret = max(ret, sum);
        }
    }
    return ret;
}

int devide_and_conqure(vector<int>& A, int lo, int hi) {
    if (lo == hi) return A[lo];

    int mid = (lo + hi) / 2;
    int left = MIN, right = MIN, sum = 0;

    for (int i = mid; i >= lo; --i) {
        sum += A[i];
        left = max(left, sum);
    }

    sum = 0;
    for (int i = mid+1; i <= hi; ++i) {
        sum += A[i];
        right = max(right, sum);
    }

    return max(left + right, max(devide_and_conqure(A, lo, mid), devide_and_conqure(A, mid+1, hi)));
}

void t_devide_and_conqure(vector<int>& A) {
    int n = devide_and_conqure(A, 0, A.size()-1);

    cout << "devide_and_conqure" << " = " << n << endl;
}


/*
 * maxA[0]  = A[0]
 *   :
 * maxAt[i] = max( 0, maxAt[i]) + A[i]
 */
int dp(vector<int>& A) {
    int N = A.size(), ret = MIN, pSum = 0;

    for (int i = 0; i < N; ++i) {
        pSum = max( 0, pSum ) + A[i];
        ret = max(pSum, ret);
    }
    return ret;
}

void t_dp(vector<int>& A) {
    int n = dp(A);

    cout << "dp" << " = " << n << endl;
}


int main()
{
    ios_base::sync_with_stdio(false);

    int va[] = { -7, 4, -3, 6, 3, -8, 3, 4 };
    vector<int> v(va, va + sizeof(va)/sizeof(int));

    test(t_devide_and_conqure, v);
    test(t_dp, v);
}
