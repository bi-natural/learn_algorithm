#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Test> 
void test (Test t)
{
    const clock_t begin = clock();
    t();
    const clock_t end = clock();
    cout << (end-begin)/double(CLOCKS_PER_SEC) << " sec\n";
}

/* https://ko.wikipedia.org/wiki/%EC%B5%9C%EB%8C%80%EA%B3%B5%EC%95%BD%EC%88%98 */
int gcd(int a, int b)
{
    if (a < b) swap(b, a);

    while (b > 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void t_gcd() {
    int a = 12345;
    int b = 234;

    int c = gcd(a, b);
    cout << "gcd(" << a << "," << b << ")" << " = " << c << endl;
}

/* lcdm(a,b) = (a*b) / gcd(a,b) */
int lcm(int a, int b)
{
    return a*(b / gcd(a, b));
}

void t_lcm() {
    int a = 12345;
    int b = 234;

    int c = lcm(a, b);
    cout << "lcm(" << a << "," << b << ")" << " = " << c << endl;
}

long long binomial(int n, int k)
{
    if (n == k) return 1;
    if (k == 1) return n; 
    return binomial(n-1, k-1) + binomial(n-1, k);
}

void t_binomial() {
    long long a = 30LL;
    long long b = 15LL;

    long long c = binomial(a, b);
    cout << "binomial(" << a << "," << b << ")" << " = " << c << endl;
}

long long cache[1000][1000] = {0LL,};

long long binomial2(int n, int k)
{
    if (cache[n][k] != 0LL)
        return cache[n][k];
    if (n == k) return (cache[n][k] = 1);
    if (k == 1) return (cache[n][k] = n); 
    return (cache[n][k] = binomial2(n-1, k-1) + binomial2(n-1, k));
}

void t_binomial2() {
    long long a = 30LL;
    long long b = 15LL;

    long long c = binomial2(a, b);
    cout << "binomial2(" << a << "," << b << ")" << " = " << c << endl;
}

/* number factorization */
vector<int> factor(int n)
{
    if (n == 1) return vector<int>(1, 1);

    vector<int> result;
    for (int div = 2; n > 1; ++div) {
        while (n % div == 0) {
            result.push_back(div);
            n /= div;
        }
    }
    return result;
}

void t_factor() {
    int a = 123454;

    vector<int> b = factor(a); 
    cout << "factor(" << a << ")" << " = " ;
    for (size_t i = 0; i < b.size(); i++)
        cout << b[i] << ",";
    cout << endl;
}
int main()
{
    test(t_gcd);
    test(t_lcm);
    test(t_binomial);
    test(t_binomial2);
    test(t_factor);
}