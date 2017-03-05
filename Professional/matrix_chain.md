## Matrix chain multiplication

$D[i][j]$ = 행렬의 곱셉을 계산하는데 필요한 최소 연산 개수

초기값: $D[i][i] = 0$, for $ 1 \le i \le n$
최종값: $D[1][n]$

$D[i][j] = min(D[i][j], D[i][k] + D[k+1][j] + a[i] \times a[k+1] \times a[j+1] )$

for $i \le k \lt j$


memorization 기법

```
int cache[N+1][N+1];

int DP(int s, int e) {
  int& ret = cache[s][e];

  if (ret != -1) return ret;
  if (s == e) return ret = 0;
  ret = MAX_INT;
  for (int k = s; k < e; ++k) {
    int v = DP(s, k) + DP(k+1, e) + A[s] * A[k+1] * A[e+1];
    ret = min(ret, v);
  }
  return ret;
}
```
