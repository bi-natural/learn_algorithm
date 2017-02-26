## KMP Algorithm

KMP(Knuth-Morris-Pratt) Alogrithm

### 아이디어: 매칭에 실패했을 때 성공한 부분을 다시 이용
 - 이미 비교한 부분을 다시 비교하지 않는다.
 - 오른쪽으로 최대한 많이 이동한다.
 - 단, 매칭이 될 수 있는 부분을 놓치지 않는다.

### 실패함수(failure function)
  - 정의: f(i)는 P[1, i]에서 가장 긴 접두어 = 접미사 길이

    * PMT(Partial Match Table)

  | i |  P[i]  | 접두사이면서 접미사인 최대 문자열 | f(i) |
  | - | - | - | - |
  | 1 | a | (없음) | 0 |
  | 2 | ab | (없음) | 0 |
  | 3 | aba | a | 1 |
  | 4 | abaa | a | 1 |
  | 5 | abaab | ab | 2 |
  | 6 | abaaba | aba | 3 |

  - 정의에 의해서, $ 0 <= f(i) < i $

  | i | 1 | 2 | 3 | 4 | 5 | 6 |
  | -- | -- | --| --| --| -- | -- |  
  | P[i] | a | b | a | a | b | a |
  | f(i) | 0 | 0 | 1 | 1 | 2 | 3 |

  - 의미
    - P를 왼쪽부터 오른쪽으로 T와 비교해 나갈때, i+1 번째 위치에서 틀린 글자가 나왔다면 i번째 글자까지는 맞음.
    - 따라서, 비교가 끝난 위치에서 처음부터 f(i)글자가 일치함
    - P를 오른쪽으로 $i - f(i)$ 만큼 이동할 수 있다.
    - 이보다 작게 이동할 경우, 첫 글자부터 틀리다는 것을 알 수 있다.

### 어떻게 실패함수를 빠르게 만드는가 ?

  - Brute Force : O($m^3$)

  - O($m$) : 수학적 귀납법에 의한 이용
    - $f(1) = 0$ 는 자명함
    - $f(1) .... f(i)$까지 모두 구하고 $f(i+1)$을 구해본다.
      - $f(i)$의 값을 이용하여 $P[f(i)+1]$ 과 $P[i+1]$이 같으면 $f(i+1)$값은 $f(i)$보다 1이 더 길어진 것. $f(i+1) = f(i) + 1$
      - $P[f(i)+1]$ 과 $P[i+1]$이 같지 않으면, 다음 번에 긴 것을 찾아야 하는데 $P[1, f(i)]$와 $P[i-f(i)+1, i]$가 일치하기 때문에, $P[1,f(i)]$의 접두사와 일치하는 $P[i-f(i)+1, i]$의 접미사중에 가장 긴것은 $P[1,f(f(i))]$.
      - 고로, 다음 번 긴것인 $f(f(i))$를 이용하여 $P[f(f(i))+1]$과 $P[i+1]$면 $f(i+1) = f(f(i)) + 1$
      - 이와 같은 과정을 반복하고, 최종적으로 $P[1]$과 $P[i+1]$을 비교하여 같으면 1, 틀리면 0

### Codes

```c++

  vector<int> getFailureFunction(const string& P)
  {
    int m = P.size();
    vector<int> pi(m, 0);

    int begin = 1, matched = 0;
    while (begin + matched < m) {
      if (P[begin + matched] == P[matched]) {
        ++matched;
        pi[begin+matched-1] = matched;
      }
      else if (matched == 0) {
        begin++;
      }
      else {
        begin += matched - pi[matched-1];
        matched = pi[matched-1];
      }
    }

    return pi;
  }

```      

| i |  P[i]  | 접두사이면서 접미사인 최대 문자열 | pi(i) |
| - | - | - | - |
| 0 | a | (초기값) | 0 |
| 1 | ab | begin = 1, matched = 0 : $(P[1] != P[0] \&\& matched == 0) -> begin ++$  | 0 |
| 2 | aba | begin = 2, matched = 0 : $(P[2] == P[0]) -> a, ++matched, pi(2) = 1$ | 1 |
| 3 | abaa | begin = 2, matched = 1 : $(P[3] != P[1] \&\& matched != 0) -> begin = 2 + 1 - pi(0) = 3, matched = pi(0) = 0$,  |  |
|   |   | begin = 3, matched = 0 : $(P[3] == P[0]) -> a, ++matched, pi(3) = 1$  | 1 |
| 4 | abaab | begin = 3, matched = 1 : $(P[4] == P[1]), ab, ++matched, pi(4) = 2$ | 2 |
| 5 | abaaba | begin = 3, matched = 2 : aba, $(P[5] == P[2]), aba, ++matched, pi(5) = 3$ | 3 |
