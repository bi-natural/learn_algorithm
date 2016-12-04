#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

template <typename Test>
long long test (Test t, int A[], int left, int right)
{
    const clock_t begin = clock();
    long long result = t(A, left, right);
    const clock_t end = clock();
    std::cout << (end-begin)/double(CLOCKS_PER_SEC) << " sec\n";
    return result;
}

const int MAX_TREE = 100000;

struct FenwickTree1 {
    vector<int> tree;

    FenwickTree1(int n) : tree(n+1) {}

    int sum(int pos) {
        ++pos;
        int ret = 0;
        for (; pos > 0; pos &= (pos-1)) {
            ret += tree[pos];
        }
        return ret;
    }

    void add(int pos, int val) {
        ++pos;
        for (; pos < tree.size(); pos += (pos & -pos)) {
            tree[pos] += val;
        }
    }

    void dumpTree() {
        printf("DUMP: ");
        for (int i = 0; i < tree.size(); ++i) {
            printf("(%d, %d) ", i, tree[i]);
        }
        printf("\n");
    }
};

struct FenwickTree2 {
    int tree[MAX_TREE+1];
    int size;

    void init(int _size) {
        size = _size + 1;
        memset(tree, 0, sizeof(tree));
    }

    int sum(int pos) {
        ++pos;
        int ret = 0;
        for (; pos > 0; pos &= (pos-1)) {
            ret += tree[pos];
        }
        return ret;
    }

    void add(int pos, int val) {
        ++pos;
        for (; pos < size; pos += (pos & -pos)) {
            tree[pos] += val;
        }
    }

    void dumpTree() {
        printf("DUMP: ");
        for (int i = 0; i < size; ++i) {
            printf("(%d, %d) ", i, tree[i]);
        }
        printf("\n");
    }

#if 0
    void updateValue(int pos, int v)
    {
        // printf("UPD: v[%d] -> (%lld -> %lld)\n", pos, values[pos], v);
        addValue(pos, v - values[pos]);
        values[pos] = v;
    }

    void dumpTree() {
        printf("DUMP: ");
        for (int i = 0; i < max_idx-1; ++i) {
            printf("v[%d]=%lld ", i, values[i]);
        }
        printf("\n      ");
        for (int i = 0; i < max_idx; ++i) {
            printf("s[%d]=%lld ", i, tree[i]);
        }
        printf("\n");
    }
#endif
};

const int MAX_N = 5000;
int CASE, N;
int input[MAX_N];

long long countMoves1(int A[], int left, int right)
{
    FenwickTree1 tree(MAX_TREE);
    //tree.dumpTree();

    long long ret = 0;
    for (int i = left; i <= right; ++i) {
        long long lt_count = tree.sum(MAX_TREE - 1) - tree.sum(A[i]);
        // printf("before A[%d] = %d : %lld\n", i, A[i], lt_count);
        ret += lt_count;
        tree.add(A[i], 1);
    }

    return ret;
}

FenwickTree2 tree;

long long countMoves2(int A[], int left, int right)
{
    tree.init(MAX_TREE);
    //tree.dumpTree();

    long long ret = 0;
    for (int i = left; i <= right; ++i) {
        long long lt_count = tree.sum(MAX_TREE - 1) - tree.sum(A[i]);
        // printf("before A[%d] = %d : %lld\n", i, A[i], lt_count);
        ret += lt_count;
        tree.add(A[i], 1);
    }

    return ret;
}

long long countMoves3(int A[], int left, int right)
{
    long long ret = 0;
    for (int i = left; i <= right; ++i) {
        long long lt_count = tree.sum(MAX_TREE - 1) - tree.sum(A[i]);
        // printf("before A[%d] = %d : %lld\n", i, A[i], lt_count);
        ret += lt_count;
    }

    return ret;
}

long long countMoves_mergeSort(int A[], int left, int right)
{
    if (left == right) return 0ll;

    int mid = (left + right) / 2;

    long long ret = countMoves_mergeSort(A, left, mid) + countMoves_mergeSort(A, mid+1, right);

    vector<int> tmp(right - left + 1);
    int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;

    while (leftIndex <= mid || rightIndex <= right) {
        if (leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
            tmp[tmpIndex++] = A[leftIndex++];
        }
        else {
            ret += mid - leftIndex + 1;
            tmp[tmpIndex++] = A[rightIndex++];
        }
    }

    for (int i = 0; i < tmp.size(); ++i) {
        A[left + i] = tmp[i];
    }

    return ret;
}

int main()
{
    freopen("data/count_inversion.txt", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d", &N);

        memset(input, 0, sizeof(input));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &input[i]);
        }

        //long long result = countMoves(input, 0, N);
        //long long result = countMoves_mergeSort(input, 0, N-1);
        printf("#%d %lld\n", t, test(countMoves1, input, 0, N-1));
        printf("#%d %lld\n", t, test(countMoves2, input, 0, N-1));
        printf("#%d %lld\n", t, test(countMoves3, input, 0, N-1));
        printf("#%d %lld\n", t, test(countMoves_mergeSort, input, 0, N-1));

        //long long result2 = test(countMoves_mergeSort, input, 0, N-1);
        //printf("#%d %lld\n", t, result2);
    }
}
