## 최저 공통 조상

- N개의 정점으로 이루어진 rooted tree.
- 서로 다른 두 정점의 **최저 공통조상(LCA)** 를 구하는 질의 Q개가 주어진다.
- 모든 질의를 시간내에 해결하는 프로그램 작성

```{mermaid}
graph TD
 1 --> 2
 1 --> 3
 2 --> 4
 2 --> 5
 3 --> 7
 5 --> 6
```

## 알고리즘

1. 깊이계산 : bfs로 깊이를 계산한다.
2. lca(a, b)
   - depth가 깊은 것을 depth가 같아질 때까지 올린다.
   - 같아졌으면 depth(0)까지 올리면서 parent가 같아질때 까지 올린다. (함께)

```
  int lca(int a, int b)
  {
    if (dep[a] < dep[b])
      swap(a, b);

    for (int i = 0; i < 17; ++i)
      if ((1 << i) & (dep[a]-dep[b]))
        a = parent[a][i];

    if (a == b)
      return a;

    for (int i = 17; i--;)
      if (parent[a][i] != parent[b][i]) {
        a = parent[a][i];
        b = parent[b][i];
      }

    return parent[a][0];
  }
```
