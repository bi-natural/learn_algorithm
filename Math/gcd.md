## GCD(Greatest Common Divisor) 최대공약수

- $gcd(a, b)$ = a, b를 동시에 나눌 수 있는 정수중에 가장 큰 정수 (최소 공약수는 1)
    - $gcd(a, b)$ = a $if b = 0 or a = b$
    - $gcd(a, b) = gcd(b, a%b)$ , $if a > b$

- 시간복잡도는 $항상 log(max(a, b))$
  - a % b 값은 항상 a / 2 보다 작다.
    - b < (a/2)이면 b로 나눈 나머지값은 *b* 보다 작다. (예: gcd(7, 2) = gcd(2, 7%2))
    - b > (a/2)이면 b로 나눈 나머지값은 *a - b* 보다 작다. (예: gcd(7, 5) = gcd(5, 7%5))
