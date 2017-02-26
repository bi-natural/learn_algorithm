## 가장 먼 도시

- N개의 정점이 있는 방향성 완전(?) 그래프
- 어떤 두 정점 사이의 거리를 두 정점사이의 최단 거리라고 정의
- 가장 먼 두 정점 사이의 거리를 구하라.

### Floyd-Warshall Algorithm

- 일종의 동적계획법
- D[k][i][j] : i번 정점에서 j번 정점으로 가는 경로 중간에 있는 정점의 번호가 k번 이하를 포함할 경우, i번 정점에서 j번 정점으로 가는 최단 거리
- D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j]);

```
  w[i][j] = i번 정점에서 j번 정점으로 가는 간선의 길이

  for (int k = 1; k <= N; ++k)
    for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j) {
        w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
      }
```

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>

- 시간복잡도는 O ($N^3$)
