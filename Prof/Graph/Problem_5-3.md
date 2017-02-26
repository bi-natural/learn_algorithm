## 군사 도로망

- N개의 정점과 M개의 간선 그래프
- 원래 있던 간선을 없앨수도 있고, 새로 만들수도 있는 정보 K개가 주어짐
- 최종적으로 그래프를 트리로 만들 때 필요한 최소 비용

### 최소 신장 트리 (Minimum Spanning Tree)

- Prim's Algorithm

- Kruskal's Algorithm

### Kruskal Algorithm

1. 간선을 이루는 비용에 대해서 오름차순으로 Sorting 한다.
2. 맨 앞쪽에 있는 (비용이 적은 간선) 값으로 Tree에 추가를 고려한다.
3. 추가하려고 할 때 싸이클이 생기면 추가하지 않는다.
4. 싸이클이 추가하지 않은 간선을 계속 추가한다.

- sort

```
  bool compare(const edge& a, const edge& b);

  sort(edge.begin(), edge.end(), compare);
```

- 싸이클을 이루지는지 체크 (disjoint-set)

```
  bool isCyclic(int e1, int e2)
  {
      return find(e1) == find(e2);
  }
```
