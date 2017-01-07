#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int CeilIndex(const int v[], int l, int r, int key) {
    while (r-l > 1) {
        int m = l + (r-l)/2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

int binsearch(const int A[], int n, int x) {
    int lo = -1, hi = n;

    while (lo+1 < hi) {
        int mid = (lo + hi) / 2;
        if (A[mid] < x)
            lo = mid;
        else
            hi = mid;
    }
    return hi;
}

struct cmp {
    bool operator()(const int& a, const int& b) { return a > b; }
};

int main()
{
    int A[] = { 1, 2, 3, 4, 5};
    int B[] = { 1, 2, 4, 5};
    printf("binsearch(A, 5, 3) = %d\n", binsearch(A, 5, 3));
    printf("binsearch(B, 4, 5) = %d\n", binsearch(B, 4, 5));

    printf("CeilIndex(A, -1, 5, 3) = %d\n", CeilIndex(A, -1, 5, 3));
    printf("CeilIndex(B, -1, 4, 3) = %d\n", CeilIndex(B, -1, 4, 3));


    /* priority_queue */
    int C[] = { 3, 2, 4, 1, 5 };

    priority_queue<int, vector<int>, cmp> pq;

    for (int i = 0; i < sizeof(C)/sizeof(int); ++i) {
        pq.push(C[i]);
    }
    printf("pq.top() = %d\n", pq.top());
    pq.pop();
    printf("pq.top() = %d\n", pq.top());
    pq.push(-1);
    printf("pq.top() = %d\n", pq.top());

    /* set, multiset */
    int D[] = { 3, 2, 4, 1, 5, 7};
    set<int> set;

    for (int i = 0; i < sizeof(D)/sizeof(int); ++i) {
        set.insert(D[i]);
    }
    printf("set.top() = %d\n", *(set.begin()));
    set.erase(set.begin());
    printf("set.top() = %d\n", *(set.begin()));
    set.insert(-1);
    printf("set.top() = %d\n", *(set.begin()));
    printf("set.lower_bound(2) = %d\n", *(set.lower_bound(2)));
    printf("set.lower_bound(6) = %d\n", *(set.lower_bound(6)));
    printf("set.upper_bound(6) = %d\n", *(set.upper_bound(6)));
    return 0;
}
