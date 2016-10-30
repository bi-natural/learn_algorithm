#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 100000;
const int MAX_Q = 200000;

int CASE;
int N, Q; 

struct FanwickTree {
    int max_idx;
    long long tree[MAX_N+1];
    long long values[MAX_N+1];

    void init(int n) { 
        max_idx = n + 1; 
        memset(tree, 0, sizeof(tree));
        memset(values, 0, sizeof(values));
    }

    void setInitValues(long long v[], const int& n) {
        for (int i = 0; i < n; ++i) {
            values[i] = v[i];
            addValue(i, v[i]);
        }
    }

    long long getValue(int pos) {
        ++pos;
        return tree[pos];
    }

    void addValue(int pos, long long v) {
        ++pos;
        // printf("ADD: %d %lld\n", pos, v);
        while (pos < max_idx) {
            tree[pos] += v;
            // printf("UPDATE: %d %lld\n", pos, tree[pos]);
            pos += (pos & -pos);
        }
    }

    long long getSum(int pos)
    {
        ++pos;
        long long ret = 0ll;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos-1);
        }
        return ret;
    }

    long long getRangeSum(int pos1, int pos2)
    {
        if (pos1 > pos2) {
            swap(pos1, pos2);
        }
        
        if (pos1 == 0) 
            return getSum(pos2);

        return getSum(pos2) - getSum(pos1-1);
    }

    void updateValue(int pos, long long v)
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
};

long long NV[MAX_N+1];
FanwickTree tree;

int main()
{
    freopen("data/psum1.txt", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d", &N, &Q);

        memset(NV, 0, sizeof(NV));
        tree.init(N);

        for (int i = 0; i < N; ++i) {
            NV[i] = i+1;
        }

        tree.setInitValues(NV, N);
        // tree.dumpTree();

        long long ret = 0ll;

        for (int i = 0; i < Q; ++i) {
            int d[3];

            scanf("%d %d %d", &d[0], &d[1], &d[2]);
            if (d[0] == 0) {
                tree.updateValue(d[1]-1, (long long) d[2]);
                tree.dumpTree();
            }
            else if (d[0] == 1) {
                long long this_sum = ( tree.getRangeSum(d[1]-1, d[2]-1) % 1000000007ll );
                ret += this_sum;
                printf("  SUM: [%d..%d] %lld -> %lld\n", d[1]-1, d[2]-1, this_sum, ret);
            }
        }
        // printf("\n");
        printf("#%d: %d\n", t, (int) (ret % (1000000007ll)));
    }

    return 0;
}