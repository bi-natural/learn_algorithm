# 동맹의 동맹은 동맹

서로소 집합 (disjoint-set).
  - N개의 원소가 있으며, M개의 집합이 있음.
  - 각 원소는 하나의 집합에 반드시 속하며
  - 서로 다른 두 집합 p, q에 대해 p와 q는 서로 소 (교집합이 없음)

## 서로소 집합에서 연산

  - Union(e1, e2)
  - Find(e)

## 연산

  - 초기화
    모든 정점(Vertex)의 대표 정점값을 자기 자신으로 한다.
  - Find(e)
    e에 대한 대표 정점값을 리턴한다.
  - Union(e1, e2)
    e1의 대표 정점값을 e2의 대표 정점값으로 바꾼다.
  - 경로 압축 { Path Compression } (Find, Union에서 경로를 압축한다.)
    * Find(e) { return (e->대표값 == e) ? e : e->대표값 = Find(e->대표값) ;  }
    * Union에서 대표정점값을 Find(e)한 값으로 대표 정점을 변경한다.

## Codes

  void init()
  {
    parent = new int[N+1];

    for (int i = 1; i <= N; ++i)
      parent[i] = i;    
  }

  int find(int n)
  {
    if (parent[n] == n)
      return n;
    else
      return parent[n] = find(parent[n]);
  }

  void union(int e1, int e2)
  {
    int p = find(e1), q = find(e2);

    if (p != q)
    {
        parent[q] = p;
    }
  }
