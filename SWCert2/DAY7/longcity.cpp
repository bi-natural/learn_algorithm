/*
 * 가장먼 도시
 *
 --
 도시의 도로 정보가 주어졌을 때, 거리가 가장 먼 두 도시 사이의 거리를 구하는 프로그램을 작성하시오.
 
 <입력>
  입력의 첫 줄에 도시의 수 N이 주어진다. (1 ≤ N ≤ 300) 그리고 다음 N개의 줄에 도로의 정보를 
  나타내는 음이 아닌 정수 N개가 공백으로 구분되어 주어진다. i+1번째 줄에서 j번째로 주어지는 
  수는 i번 도시에서 j번 도시로 가는 도로의 길이를 의미하며, 이 수는 1,000,000 보다 크지 않다. 
  i+1번째 줄에서 i번째 수는 항상 0이다.
 -- 
 
 모든 정점들의 거리를 구할 수 있는 Floyd-Warshall 알고리즘을 사용한다.
 
	for (int k = 1; k <= V; ++k) 
		for (int i = 1; i <= V; ++i) 
			for (int j = 1; j <= V; ++j) 
	 			D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
  
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_V = 300;
const INT64 MAX_C = 1000000000000ll;

int V;
INT64 edges[MAX_V+9][MAX_V+9];

/* Floyd Warshall
 *
 * [i]lj]
 * 
 * [k] 생략
 * i ~ j : i에서 j까지 가는 거리중에 최소 
 */ 
INT64 D[MAX_V+9][MAX_V+9];

INT64 LONG_CITY()
{
	memset(D, -1, sizeof(D));
	
	/* init value */
	for (int i = 1;  i <= V; ++i)
		for (int j = 1; j <= V; ++j) {
			D[i][j] = edges[i][j];
		}

	/* run Floyd Warshall */
	for (int k = 1; k <= V; ++k) {
		for (int i = 1; i <= V; ++i) 
			for (int j = 1; j <= V; ++j) {
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
#ifdef DEBUG
				printf("iteration: %d %d %d\n", k, i, j);
				for (int ii = 1; ii <= V; ++ii) {
					for (int jj = 1; jj <= V; ++jj) {
						printf("%d ", D[ii][jj]);
					}
					printf("\n");
				}
#endif
			}
	}
	
	INT64 result = 0;
	for (int i = 1; i <= V; ++i) 
		for (int j = 1; j <= V; ++j) 
			result = max(result, D[i][j]);
			
	return result;

}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\longcity.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d", &V);	
	
	for (int i = 1; i <= V; ++i) {
		for (int j = 1; j <= V; ++j) {
			scanf("%lld", &edges[i][j]);
		}
	}
	
	INT64 result = LONG_CITY();
	printf("%lld\n", result);
	return 0;
}
