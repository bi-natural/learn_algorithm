#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <strings.h>
#include <vector>

using namespace std;

int get_empty() {
    return 0;
}

int get_fullset(int bit_nr) {
    return (1<<bit_nr) - 1;
}

int insert_set(int& set_, int p) {
    return set_ | (1<<p);
}

int delete_set(int& set_, int p) {
    return set_ & ~(1<<p);
}

int toggle_set(int& set_, int p) {
    return set_ ^ (1<<p);
}

bool hit_set(int& set_, int p) {
    return static_cast<bool>(set_ & (1<<p)); 
}

int union_set(int& a, int& b) {
    return a | b;
}

int intersection_set(int& a, int& b) {
    return a & b;
}

int differ_set(int& a, int& b) {
    return a & ~b;
}

int sym_differ_set(int& a, int& b) {
    return a ^ b;
}

int count_bit8(unsigned char a)
{
    static vector<int> cache(256, -1);

    if (a == 0) return 0;

    int& n = cache[a];
    if (n == -1) {
        n = (a % 2) + count_bit8(a / 2);
    }
    return n;
}

int count_bit16(unsigned short a)
{
    static vector<int> cache(256*256, -1);

    if (a == 0) return 0;

    int& n = cache[a];
    if (n == -1) {
        n = (a % 2) + count_bit16(a / 2);
    }
    return n;
}

int count_bits(int& a) {
    int result = count_bit8((unsigned char) (a & 0xFF));
    result += count_bit8((unsigned char) ((a >> 8) & 0xFF));
    result += count_bit8((unsigned char) ((a >> 16) & 0xFF));
    result += count_bit8((unsigned char) ((a >> 24) & 0xFF));
    
    return result;
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

int only1_bit(int a) {
    return (remove_lo_bit(a) == 0);
}

vector<int> subsets(int a) {
    vector<int> ret;

    for (int s = a; s; s = ((s-1) & a)) {
        ret.push_back(s);
    }
    return ret;
}

string printBits(int a) {
    int lo = lo_bit_n(a);
    int hi = hi_bit_n(a);

 //cout << "lo: " << lo << ",  hi: " << hi << endl;
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

int main()
{
    int a = 39;  // 10,0111
    vector<int> s_a = subsets(a);

    string s = printBits(a);
    cout << s << endl;
    for (int i = 0; i < s_a.size(); ++i) {
        cout << printBits(s_a[i]) << ", ";
    }
    cout << endl;
}