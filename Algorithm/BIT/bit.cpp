/*
 * BIT(Binary Indexed Tree) = FenwickTree
 *
 * Search / Update : O(n*log n)
 */

#include <cstdio>
#include <cstring>

/* Least Significant Bit */
#define LSB(s) (s & (-s))

class BIT {
    int *ptree, size;

public:
    BIT(int n) {
        size = n;
        ptree = new int[n+1];
        memset(ptree, 0, (size+1) * sizeof(int));
    }

    ~BIT() { delete[] ptree; }

    // returns : sum of the range [1..b]
    int sum(int b) {
        int sum = 0;
        for (; b ; b -= LSB(b)) sum += ptree[b];
        return sum;
    }

    //
    int sum(int a, int b) {
        if (a == 1)
            return sum(b);
        else
            return sum(b) - sum(a-1);
    }

    // updates : update value of the k-th element by v
    void update(int k, int v) {
        for (; k <= size; k += LSB(k)) ptree[k] += v;
    }

};

int main()
{
    BIT bit(20);
    int CASE, N;
    int inputs[100];

    freopen("count_inversion.txt", "r", stdin);
    scanf("%d", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &inputs[i]);
            bit.update(i, inputs[i]);
        }

        printf("sum[1..n-1] : %d\n", bit.sum(N-1));
        printf("sum[2..3] : %d\n", bit.sum(2, 3));
    }
    return 0;
}
