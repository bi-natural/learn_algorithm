#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int CASE;
int N;

struct Position {
    long vx, xy;
    long day;
};

vector<Position> princeWay;
vector<Position> princessWay;

int main()
{
    freopen("data/messenger.dat", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        Position p;

        scanf("%d\n", &N);
        princeWay.clear();
        princessWay.clear();
        for (int i = 0; i < N; ++i) {
            scanf("%d %d\n", &(P.vx), &(P.vy));
            princeWay.push_back(P);
        }

        for (int i = 0; i < N; ++i) {
            scanf("%d %d\n", &(P.vx), &(P.vy));
            princessWay.push_back(P);
        }

        princeWay[0].day = 1;
        princessay[0].day = 1;
        for (int i = 1; i < N; ++i) {
            princeWay[i].day = max(abs(princeWay[i].vx, princeWay[i-1].vx), abs(princeWay[i].vy, princeWay[i-1].vy));
            princessWay[i].day = max(abs(princessWay[i].vx, princessWay[i-1].vx), abs(princessWay[i].vy, princessWay[i-1].vy));
        }

        
    }
}