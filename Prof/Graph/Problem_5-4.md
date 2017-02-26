## 임계 경로

- N개의 공정과 M개의 작업
- 간선의 가중치는 결과물이 간선을 지날 때 걸리는 시간
- 한 공정에서 작업을 시작하기 위해서는 이전에 필요한 작업 결과물을 다 받은 상황에서 시작할 수 있음.
- 1번 공정에서 작업을 시작할 때 N번 공정에서 작업을 완료하는 최소 시간을 구하라.

### 분석

- DAG(Directed Acyclic Graph)
- 위상정렬(Topological Sort)

## 위상정렬

1. In-degree가 0인 정점을 찾는다. (dependency가 없는 정점)
2. 찾은 정점을 출력하고 해당 정점에서 나가는 정점과 간선을 삭제한다.
3. 그래프에 정점이 없을 때까지 수행
4. [참고] 복잡도는 O (V + E)

```
  /* a -> b : c */
  for (...) {
    v[a].push_back(b);
    in[b]++;

    from[b].push_back(a);
    from_v[b].push_back(c);    
  }
  :

  vector<int> order;
  queue<int> que;

  que.push(...);   /* In-degree 가 0인 것들을 넣어준다. */

  while (!que.empty()) {
    int q = que.top(); que.pop();

    order.push_back(q);
    for (int i = 0; i < v[q].size(); ++i) {
      int t = v[q][i];

      if (--in[t] == 0)
        que.push(t);
    }
  }
```

## 최대 dependency 찾기

1. 위상정렬된 순서대로 정점을 visit한다.
2. Vist하면서 들어오는 정점의 값 + 간선 값이 최대값을 해당정점의 값으로 업데이트

```
  for (int i = 0; i < N; ++i) {
    int n = order[i];

    for (int j = 0; j < from[n].size(); ++j) {
      int t = from[n][j], v = from_v[n][j];

      D[n] = max(D[n], D[t] + v);
    }
    D[n] = min(D[n], INF);
  }
```
