#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int CASE;
int N, K, M, L;
vector<int> NV;
vector<int> MV;

int bitCount(int a) {
    if (a == 0) return 0;
    return a%2 + bitCount(a/2);
}

int differ_set(int a, int b) {
    return a & ~b;
}

int get_fullset(int bit_nr) {
    return (1<<bit_nr) - 1;
}

int union_set(int a, int b) {
    return a | b;
}

bool hit_set(int set_, int p) {
    return static_cast<bool>(set_ & (1<<p)); 
}

int lo_bit(int a) {
    return -a & a;
    // -a = ~a + 1
    // a & (~a + 1)
}

int lo_bit_n(int a) {
    return ffs(lo_bit(a));
}

int remove_lo_bit(int a) {
    return a & (a - 1);
    // return a & (-a & a);
    // return a & (a - 1);
    // -a = ~a + 1
}

/* http://graphics.stanford.edu/~seander/bithacks.html */
int hi_bit(int a) {
    unsigned int x = a;

    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return(x & ~(x >> 1));
}

int hi_bit_n(int a) {
    return ffs(hi_bit(a));
}

string printBits(int a) {
    int lo = lo_bit_n(a);
    int hi = hi_bit_n(a);

    vector<char> buf;
    
    for (int i = 0; i < lo-1; ++i) 
        buf.push_back('0');

    a >>= (lo-1);
    for (int i = lo; i <= hi; ++i, a >>= 1) {
        buf.push_back(a & 1 ? '1' : '0');
    }
    reverse(buf.begin(), buf.end());

    return string(buf.begin(), buf.end());
}

string printBits(int a, int M) {
    int lo = lo_bit_n(a);
    int hi = hi_bit_n(a);

    vector<char> buf;
    
    for (int i = 0; i < lo-1; ++i) 
        buf.push_back('0');

    a >>= (lo-1);
    for (int i = lo ? lo : 1 ; i <= M; ++i, a >>= 1) {
        buf.push_back(a & 1 ? '1' : '0');
    }
    reverse(buf.begin(), buf.end());

    return string(buf.begin(), buf.end());
}

int findMin()
{
    int fullset_ = get_fullset(N);
    int set_ = 0;   // start from empty
    int result = 0;
    int nothing = 0;

cout << "N=" << N << endl;
for (int i = 0; i < N; ++i)
    cout << printBits(NV[i], N) << endl;

cout << "M=" << M << endl;
for (int i = 0; i < M; ++i)
    cout << printBits(MV[i], N) << endl;    

    for (result = 0; result < M; ++result) {
        int _mset = differ_set(MV[result], set_);
        int _pset = differ_set(fullset_, set_);

        for (int i = 0; i < N; ++i) {
            if (hit_set(_mset, i)) {
                _pset = differ_set(_pset, NV[i]);
            }
        }
cout << "D:" << result << " " << printBits(set_, N) << " " << printBits(_mset, N) << " " << printBits(_pset, N) << endl;

        if (_pset == 0) {
            nothing ++;
            continue;
        }
        set_ = union_set(set_, _pset);
cout << "  " << printBits(set_, N) << endl;
        if (bitCount(set_) >= K)
            return (result - nothing + 1);
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("data/graduation.dat", "r", stdin);

    cin >> CASE;
    for (int t = 1; t <= CASE; ++t) {
        cin >> N >> K >> M >> L;

        NV.clear();
        MV.clear();
        for (int i = 0; i < N; ++i) {
            int a, b, set_;
            cin >> a;
             
            set_ = 0;
            for (int j = 0; j < a; ++j) {
                cin >> b;
                set_ |= (1 << b);
            }
            NV.push_back(set_);
        }

        for (int i = 0; i < M; ++i) {
            int a, b, set_;
            cin >> a;
             
            set_ = 0;
            for (int j = 0; j < a; ++j) {
                cin >> b;
                set_ |= (1 << b);
            }
            MV.push_back(set_);
        }

        int result = findMin();

        if (result > 0)
            cout << "#" << t << " " << result << endl;
        else
            cout << "#" << t << " " << "IMPOSSIBLE" << endl; 
    }
}