#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int CASE;
int N, P, L;

ostringstream oss;


long long precalc_len[51];

void precalc(int x) {
    precalc_len[0] = 1; 

    for (int i = 1; i < x; ++i) {
        precalc_len[i] = 2 + (2 * precalc_len[i-1]);
    }    
}

void makeString(string seed, int generation)
{
    if (generation == N) {
        oss << seed;
        return;
    } 

    for (int i = 0; i < seed.size(); ++i) {
        if (seed[i] == 'X') {
            makeString(string("X+YF"), generation+1);
        }
        else if (seed[i] == 'Y') {
            makeString(string("FX-Y"), generation+1);
        }
        else {
            oss << seed[i];
        }
    }
}

int position;

void skipString(string seed, int generation) 
{
    if (generation == N) {
        for (int i = 0; ( position+i >= P && position+i < P+L) && i < seed.size(); i++) 
            oss << seed[i];
        position += seed.size();

        return;
    }

    for (int i = 0; i < seed.size(); ++i) {
        if (seed[i] == 'X') {
            skipString(string("X+YF"), generation+1);
        }
        else if (seed[i] == 'Y') {
            skipString(string("FX-Y"), generation+1);
        }
        else {
            if (position >= P && position < (P+L))
                oss << seed[i];
            position++;
        }
            
    }
}

char kthCharactor(string seed, int generation, int kth) 
{
    if (generation == 0) {
        // assert(kth < seed.size());
        return seed[kth];
    }

    for (int i = 0; i < seed.size(); ++i) {
        if (seed[i] == 'X') {
            if (kth >= precalc_len[generation])
                kth -= precalc_len[generation];
            else
                return kthCharactor(string("X+YF"), generation-1, kth);
        }
        else if (seed[i] == 'Y') {
            if (kth >= precalc_len[generation])
                kth -= precalc_len[generation];
            else
                return kthCharactor(string("FX-Y"), generation-1, kth);
        }
        else {
            if (kth > 0)
                kth--;
            else
                return seed[i];
        }            
    }
}

void skipString2(string seed)
{
    for (int i = P-1; i < P+L-1; ++i) {
        oss << kthCharactor(seed, N, i);
    }
}

int main()
{
    freopen("data/curve.dat", "r", stdin);
    scanf("%d\n", &CASE);

    precalc(50);

    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d %d\n", &N, &P, &L);

        oss.str("");
        position = 1;
        skipString2(string("FX"));
        string result = oss.str();

        printf("#%d len = %lld %s\n", t, precalc_len[N] + 1, result.c_str());
    }
    return 0;
}