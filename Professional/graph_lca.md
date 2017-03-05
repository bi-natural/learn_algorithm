## 최저 공통 조상(Least Common Anchestor)

- rooted tree여야 한다
- 서로 다른 두 정점에서의 최저공통조상(LCA).

1. 1 이상 N이하인 모든 i에 대해 $parent[i][0]$에 i번 정점의 부모정점을 대입
```
for (int i = 0; i < N; ++i)
  parent[i][0] = $parent_of_node[i]$
```
2. 부모들의 부모들을 업데이트 한다.

```
for (int k = 1; i < 17; ++k)
  for (int i = 1; i <= N; ++i)
    parent[i][k] = parent[parent[i][k-1]][k-1]
```

시간/공간복잡도 $O(N lg N)$

- 깊이 계산(depth)

```
queue<int> q;
q.push(1);
while (!q.empty()) {
  int x = q.front(); q.pop();
  for (int i = 0; i < node[x].size(); ++i) {
    int t = node[x][i];
    depth[t] = depth[x]+1;
    q.push(t);
  }
}
```

최저 공통 조상

1. a번 정점의 깊이가  b번 정점의 깊이보다 얕지 않다고 가정
2. a번의 깊이가 b번 정점의 깊이와 같아지도록 a번 정점을 위로 올린다.
  (이때, a번의 정점을 위로 올려도 $lca(a, b)$는 변하지 않는다.)
3. 만약 a = b 라면 $lca(a, b) = a$
4. a번 정점과 b번 정점이 같지 않을떄까지 위로 올린다.
5. $lca(a, b) = parent[a][0]$

```
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int i = 0; i < 17; ++i)
      if ((1 << i) & (depth[a] - depth[b]))
        a = parent[a][i];
    if (a == b) return a;
    for (int i = 17; i--; )
      if (parent[a][i] != parent[b][i]) {
        a = parent[a][i];
        b = parent[b][i];
      }
    return parent[a][0];
}
```
