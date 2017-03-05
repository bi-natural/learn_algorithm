## fibonacci 수

- $ if n = 0, F[n] = 0$
- $ if n = 1, F[n] = 1$
- $ if n \ge 2, F[n] = F[n-1] + F[n-2]$

input ($ 0 \le N \le 10^{12} $), cacl $F[n]$ ?

### linear transformation (선형변환)

*단순 순열 점화식* 을 행렬의 형태로 변환하여 빠르게 푸는 기법.

$
\begin{bmatrix}
F(n) \\
F(n-1)
\end{bmatrix}
=
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}
\begin{bmatrix}
F(n-1) \\
F(n-2)
\end{bmatrix}
$

$
\begin{bmatrix}
F(n) \\
F(n+1)
\end{bmatrix}
=
\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}^{n-1}
\begin{bmatrix}
F(1) \\
F(0)
\end{bmatrix}
=
A^{n-1}
\begin{bmatrix}
1 \\
0
\end{bmatrix}
$
### 답

```
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

const long long BIG_INT = 1000000007;

struct Mat2x2 {
	int m[2][2];

	Mat2x2 operator*(const Mat2x2& other) const {
		Mat2x2 ret = { 0, };

		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j) {
				long long x1 = ((long long)(this->m[i][0]) * (long long)(other.m[0][j])) % BIG_INT;
				long long x2 = ((long long)(this->m[i][1]) * (long long)(other.m[1][j])) % BIG_INT;

				ret.m[i][j] =  (int)((x1 + x2) % BIG_INT);
			}
		return ret;
	}

	void print() {
		std::cout << this->m[0][0] << " " << this->m[0][1] << std::endl; std::cout << this->m[1][0] << " " << this->m[1][1] << std::endl;
	}

};

Mat2x2 I, A;

int fibo(long long n) {
	if (n < 2) return n;

	Mat2x2 now = I, v = A;

	for (long long p = n - 1; p; p >>= 1, v = v*v) {
		if (p % 2)
			now = now * v;
	}

	return now.m[0][0];
}

int main()
{
	I = { 1, 0, 0, 1 };
	A = { 1, 1, 1, 0 };

	for (long long i = 1; i < 100; ++i)
		std::cout << "fibo(" << i << ") = " << fibo(i) << std::endl;
	return 0;
}
```
