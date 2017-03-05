## 네트워크 용량 문제

Ford-Fulkerson's algorithms

- flow network : 가중 그래프
  - s : source (출발지)
  - t : sink (목적지)
- flow 속성
  - c(u, v) : u에서 v로 가는 용량
  - f(u, v) : u에서 v로 실제로 흐르는 유량

  - 용량 제한 : $0 \le f(u, v) \le c(u, v)$
  - 대칭성: $f(u, v) = -f(v, u)$
  - 유량 보전: $\sum_{u,v \in V} f(u, v) = 0$

Maxium flow : 얼마나 많은 양을 보낼 수 있을까?

*Cut* $\chi$ : 소스(s)와 목적지(t)의 노드들을 그래프를 쪼개는 것. 네트워크를 연결하는 간선(edge)들의 없앴을 때 분리되어 partition 되는 간선들의 집합.

  - $f(\chi)$ : 순방향 edge들의 총량에서 역방향 edge들의 용량을 제외한 것.
  - $c(\chi)$ : 순방향으로 나가는 edge들의 총 용량
