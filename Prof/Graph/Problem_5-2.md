## 최단 경로

최단거리 알고리즘 (Shortest Path Algorithm)

|    알고리즘    | 제한 조건                   | 음수간선 | 시간복잡도 |
| -----------   | --------------------------- | ------- | --------- |
| BFS           | 시작점 고정, 간선 가중치 동일 | X       | O(V + E) |
| Dijkstra      | 시작점 고정                  | X       | O((V + E) log V) |
| Floyd-Warhall | 없음                         | O       | O(V^3) |
| Bellman Ford  | 시작점 고정, 음수 싸이클 없음 | O        | O (V E) |

### Dijkstra Algorithm

1. 거리 배열을 만들어서 시작점에 0 값을 나머진 무한대 값을 넣는다.
2. 처리하지 않은 정점중에 거리 값이 제일 작은 정점을 고른다.
3. 해당 정점에 연결된 간선들에 대해 인접한 다른 정점의 값을 갱신한다.
4. 2 ~ 3 를 모든 정점에 대해서 처리할 때까지 반복

### 구현

1. 처리하지 않은 정점중에 거리 값이 제일 작은 정점을 구하는 방법 (heap)

### Codes

```
typedef pair<int, int> p;

vector<int> v[MAX_N], e[MAX_N];
vector<int> D(N+1);

void init()
{
  for (int i = 1; i <= M; ++i) {
    int v1, v2, w1;

    scanf("%d%d%d", &v1, &v2, &w);
    v[v1].push_back(v1);
    e[v1].push_back(w1);
    v[v2].push_back(v1);
    e[v2].push_back(w1);
  }
}

void Dijkstra(int s)
{
  prority_queue <p> queue;

  for (int i = 1; i <= N; ++i)
    D[i] = (i == s) ? 0 : INF;  

  queue.push(make_pair<0, 1>);
  while (!queue.empty()) {
    int q = queue.top().second;
    int d = -queue.top().first; /* min-heap */

    queue.pop();
    if (D[q] != d)
      continue;

    for (int i = 0; i < v[q].size(); ++i) {
      int t = v[q][i], v = e[q][i];

      if (D[t] > D[q]+v) {
        D[t] = D[q] + v;
        queue.push(make_pair<-D[t], t>)
      }
    }
  }
}

```
