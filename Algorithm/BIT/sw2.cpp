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

    void delta(int k, int v) {
        for (; k <= size; k += LSB(k)) ptree[k] -= v;
    }

    void dump(int n) {
        for (int i = 0; i < n; ++i) {
            printf(" %d", sum(i));
        }
        printf("\n");
    }
};

void printA(int ins[], int N)
{
    printf("A[i] :");
    for (int i = 0; i < N; ++i) {
        printf(" %d", ins[i]);
    }
    printf("\n");
}

int CASE, N, K;

/*
 (0) * A0
 (A0) * A1
 (A0 + A1) * A2
 (A0 + A1 + A2) * A3
    :
 (A0 + .... + A(n-1)) * A(n)


 -->
      A0 * (A1 + A2 + A3 .. + A(n))
      A1 * (     A2 + A3 .. + A(n))
      A2 * (          A3 .. + A(n))
        :
      A(n-1) * (              A(n))

  (0) * A0
  (A0) * A1
  (A0 + A1) * A2
  (A0 + A1 + A2) * A3
  (       0       ) * A4
  (                 A4) * A5
  (                 A4 + A5) * A6
         :
  (                 A4 +  ..   A(i-2)) * A(i-1)
  (      0                             ) * A(i)
  (                                  A(i)) * A(i+1)
  (                                  A(i) + A(i+1)) * A(i+2)
         :
  (                                  A(i) ... + A(n-1)) * A(n)


 -->
    A0 * (A1 + A2 + A3                    )
    A1 * (     A2 + A3                    )
    A2 * (          A3                    )
    A3 * (           0                    )
    A4 * (              A5 + ...... A(i-1))
    A5 * (                  A6 + .. A(i-1))
    :
    Ai * (               A(i+1) + .. A(n) )
    :
    A(n-1) * (                       A(n) )


    최초
    A4 === 0,
        - A0 * A[4..n]
        - A1 * A[4..n]
        - A2 * A[4..n]
        = (A[0..2]) * (A[4..n])

    A(i) === 0,
        - A(4) * A[i..n]
        - A(5) * A[i..n]
          :
        - A(i-2) ...

        = (A[4..(i-2)]) * (A[i..n])

 */

int main()
{
    int ins[200];
    BIT bit(200);
    BIT sbit(200);
    int pos[100];

    freopen("sw12.txt", "r", stdin);
    scanf("%d", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &ins[i]);
            bit.update(i+1, ins[i]);
        }

        for (int i = 1; i <= N; ++i) {
            sbit.update(i, ins[i-1] * bit.sum(i-1));
        }

        printA(ins, N);
        printf("B[i] :"); bit.dump(N);
        printf("C[i] :"); sbit.dump(N+1);

        for (int i = N-1; i >= N-K; --i) {
            pos[i-(N-K)] = i;
        }
        printA(pos, K);

        for (int i = 0; i < K; ++i) {
            printf("delta: pos = %d , ins = %d, sum = %d --> %d\n", pos[i], ins[pos[i]], bit.sum(pos[i]), ins[pos[i]] * bit.sum(pos[i]));
            sbit.delta(pos[i]+1, ins[pos[i]] * bit.sum(pos[i]));
            printf("C[i] :"); sbit.dump(N+1);
        }

        int curSUM = sbit.sum(N);

        printf("Current SUM is %d\n", curSUM);
        for (int i = 0; i < K; ++i) {
            for (int j = pos[i]; j > 1; --j) {
                printf("update: pos = %d , ins = %d, sum = %d --> %d\n", j, ins[j], bit.sum(j), ins[j] * bit.sum(j));
                sbit.update(j+1, ins[j] * bit.sum(j));  /* Restore */
                printf("C[i] : (back %d) ", j+1); sbit.dump(N+1);
                printf("delta: pos = %d , ins = %d, sum = %d --> %d\n", j-1, ins[j-1], bit.sum(j-1), ins[j-1] * bit.sum(j-1));
                sbit.delta(j, ins[j-1] * bit.sum(j-1));  /* delta */
                printf("C[i] : (prev %d) ", j); sbit.dump(N+1);

                if (sbit.sum(N) < curSUM) {
                    printf("New curSUM : %d --> %d\n", curSUM, sbit.sum(N));
                    curSUM = sbit.sum(N);
                }
                else {
                    /* Restore */
                    printf("SSUM is larger than curSUM....& restore delta\n");
                    sbit.update(j, ins[j-1] * bit.sum(j-1));
                    sbit.delta(j+1, ins[j] * bit.sum(j));
                    break;
                }
            }
        }
    }

    return 0;
}
