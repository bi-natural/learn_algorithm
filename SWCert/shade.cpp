#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int CASE;
int N;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    else gcd(b, a % b);
}

struct Vec {
    long long x, y;
};

Vec minus(const Vec& a, const Vec& b) {
    Vec result;

    if (b.x < a.x) {
        result.x = (a.x - b.x);
        result.y = (a.y - b.y);            
    }
    else {
        result.x = (b.x - a.x);
        result.y = (b.y - a.y);
    }

    if (result.x != 0ll && result.y != 0ll) {
        long long g = gcd(result.x, result.y);

        result.x /= g;
        result.y /= g;
    }
    else if (result.x == 0ll)
        result.y /= abs(result.y);
    else if (result.y == 0ll)
        result.x = 1ll;

    return result;
}

struct Line {
    int idx; 
    Vec v;
};

vector<Vec> NV;
vector<Line> Lines;

int result[1001];

bool gt(const Line& a, const Line& b) {
    if (a.v.x == b.v.x && a.v.y == b.v.y && a.idx == b.idx) return true;

    if (a.v.x < b.v.x) return true;
    else if (a.v.x == b.v.x && a.v.y < b.v.y) return true;
    else if (a.v.x == b.v.x && a.v.y == b.v.y && a.idx < b.idx) return true;

    return false;
}

void print(vector<Line>& lines)
{
    printf("-> %ld\n", lines.size());

    vector<Line>::iterator it = lines.begin();
    for (; it != lines.end(); ++it) {
        printf("(%lld %lld %d) ", it->v.x, it->v.y, it->idx);
    }
    printf("\n");
}

void classify(vector<Line>& lines)
{
    int include_dots = 1;

    for (int i = 0; i < lines.size() - 1; ++i) {
        Line& prev = lines[i];
        Line& next = lines[i+1];

printf("D: (%lld, %lld, %d) (%lld, %lld, %d)\n", prev.v.x, prev.v.y, prev.idx, next.v.x, next.v.y, next.idx);
        if (prev.v.x == next.v.x && prev.v.y == next.v.y) {
            if (prev.idx == next.idx) {
printf("D:   idx is the same (dots = %d)\n", include_dots);
                continue;
            } 
            include_dots++;
printf("D:   idx is not the same (dots = %d)\n", include_dots);            
        }
        else {
            result[N - include_dots] += 2;
printf("D: set result [%d] = %d\n", N - include_dots, result[N-include_dots]);
            include_dots = 1;
        }

    }
    result[N - include_dots] += 2;
printf("E: set result [%d] = %d\n", N - include_dots, result[N-include_dots]);
}

int main()
{
    freopen("data/shade1.dat", "r", stdin);
    scanf("%d\n", &CASE);
    for (int t = 1; t <=5; ++t) {
        scanf("%d\n", &N);

        NV.clear();
        Lines.clear();

        for (int i = 0; i < N; i++) {
            Vec a;

            scanf("%lld %lld\n", &(a.x), &(a.y));
            NV.push_back(a);
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                Line l;
                
                l.v = minus(NV[i], NV[j]);
                l.idx = i;
printf("(%lld %lld %d) ", l.v.x, l.v.y, l.idx);
                Lines.push_back(l);                
            }
        }
        printf("\n");

        sort(Lines.begin(), Lines.end(), gt); 

        print(Lines);

        memset(result, 0, sizeof(result));

        classify(Lines);

        printf("#%d ", t);
        for (int i = 1; i <= N-1; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    return 0;
}