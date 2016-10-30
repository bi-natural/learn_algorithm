#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;  // cases

bool beFriend[100][100] = { false, };

template <typename Test>
void test(Test t) {
    clock_t begin = clock();
    t();
    clock_t end = clock();
    cout << (end - begin)/double(CLOCKS_PER_SEC) << " sec" << endl;
}

int found_all_pairs(bool *taken, int S)
{
    int firstFree = -1;

    for (int i = 0; i < S; i++) {
        if (!taken[i]) {
            firstFree = i;
            break;
        }
    }

    if (firstFree == -1) return 1;

    int ret = 0;

    for (int pairWith = firstFree+1; pairWith < S; ++pairWith) {
        if (!taken[pairWith] && beFriend[firstFree][pairWith]) {
            taken[firstFree] = taken[pairWith] = true;
            ret += found_all_pairs(taken, S);
            taken[firstFree] = taken[pairWith] = false;
        } 
    }
    return ret;
}

void make_pair(int S)
{
    bool* pairs = new bool[S];  

    for (int i = 0; i < S; i++)
        pairs[i] = false;

    int n = found_all_pairs(pairs, S);
    cout << n << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    freopen("data/picnic.dat", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int student, friends;

        cin >> student >> friends;

        for (int j  = 0; j < 100; j++) 
            for (int z = 0; z < 100; z++)
                beFriend[j][z] = false;

        for (int j = 0; j < friends; ++j)  {
            int a, b;

            cin >> a >> b;
            beFriend[a][b] = true;
            beFriend[b][a] = true;
        }

        make_pair(student);
    }
}