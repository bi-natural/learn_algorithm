
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

const int MAX_N = 10000000;

using namespace std;

int CASE;
int N, HI, LO;

int precalc[MAX_N+1];

void eratosthenes() {
    precalc[0] = precalc[1] = -1;

    for (int i = 2; i <= MAX_N; ++i)
        precalc[i] = i;

    int sqrtN = int(sqrt(MAX_N));

    for (int i = 2; i <= sqrtN; ++i) {
        if (precalc[i] == i) {
            for (int j = i*i; j <= MAX_N; j += i) {
                precalc[j] = i;
            }
        }
    }
}

vector<int> getFactor(int n)
{
    vector<int> result;

    while (n > 1) {
        result.push_back(precalc[n]);
        n = n / precalc[n];
    }
    return result;
}

int factors[MAX_N+1];

void getFactorNumbers() 
{
    memset(factors, 0, sizeof(factors));

    for (int div = 1; div <= MAX_N; ++div) {
        for (int m = div; m <= MAX_N; m += div) {
            factors[m] ++;
        }
    }
}

int findPassword()
{
    int result = 0;

    for (int i = LO; i <= HI; ++i) {
        if (factors[i] == N)
            result++;
    }
    return result;
}

int main()
{
    freopen("data/password.dat", "r", stdin);
    
    getFactorNumbers();
    
    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d %d\n", &N, &LO, &HI);

    

        int result = findPassword();
        printf("#%d %d\n", t, result);
    }
}