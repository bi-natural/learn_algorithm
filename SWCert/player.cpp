#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int CASE;
int N;   //   5 <= N <= 20
int M;   //   4 <= M <= 24

vector<int> Payroll;
int canPlay[21][21];
const int INF = 987654321;

bool isFull(int Playable) 
{
    int Full = (1 << M) -1;

    return Full == Playable;
}

int algorithm(int person, int Playable)
{
    if (person == N) {
        if (isFull(Playable)) 
            return 0;
        else
            return INF;
    }

    int sum = INF;
    int nextPlayable = Playable;

    // exclude this persion
    sum = algorithm(person + 1, Playable);

    // include this persion
    for (int i = 0; i < M; ++i) {
        if (canPlay[i][person])
            nextPlayable |= (1 << i);
    }

    if (nextPlayable != Playable)
        sum = min (sum, Payroll[person] + algorithm(person + 1, nextPlayable));
    
    return sum;
}

int findMinPayOchestra()
{
    int Playable = 0;

//    printf("Person: %d\n", N);
//    printf("Instrument: %d\n", M);

    int r = algorithm(0, Playable);
    return r;
}

int main()
{
    freopen("data/player.dat", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d\n", &N, &M);

        Payroll.clear();        
        for (int i = 0; i < N; ++i) {
            int m;
            scanf("%d", &m);
            Payroll.push_back(m);
        }

        memset(canPlay, 0, sizeof(canPlay));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &canPlay[i][j]);
            }
        }

        int result = findMinPayOchestra();

        printf("#%d %d\n", t, result);
    }
}