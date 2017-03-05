## Week 1

### Commonly-used notations in the theory of algorithms

- Big Theta:  $\Theta(N^2)$
  - asymptotic order of growth
- Big Oh : $O(N^2)$
  - upper bound
- Big Omega : $\Omega(N^2)$
  - lower bound
- $\tild N^2$

ex)  3-Sum problem.

  - upper bound: $O(N^2logN)$
    - sort : $O(N log N)$
    - $n * n * log n$


### Memory

| type | bytes |
| ---- | ----- |
| bool | 1 |
| byte | 1 |
| char | 2 |
| int  | 4 |
| float | 4 |
| long long | 8 |
| double | 8 |

| type | bytes |
| ---- | ----- | 
| char[]  | $2N + 24$ |
| int[]  | $4N + 24$ |
| double[]  | $8N + 24$ |
