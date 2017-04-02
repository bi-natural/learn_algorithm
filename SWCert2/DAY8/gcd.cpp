/*
 * 최대공약수가 1이 되는 것
 --
 어떤 수열 S가 주어진다. 수열 S에서 한 개 이상 원소를 선택했을 때, 
 선택한 수 혹은 수들의 최대공약수가 1이 되는 것의 개수를 구하는 프로그램을 작성하시오.
 
 <입력>
 첫 번째 줄에 수열의 크기 N이 주어진다. (1 ≤ N ≤ 100)
 두 번째 줄부터 N개의 줄에 걸쳐 수열의 각 원소 Si가 주어진다. 
 어떤 두 원소가 같을 수 있다. (1 ≤ Si ≤ 100,000) 
 --
 */ 
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N         107
#define MAX_S      100007
#define MAX_MOD  10000003

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

int CASE; 
int N;
int A[MAX_N];

/*
 --
 D[i][x] = 1번째 수부터 i번째 수까지 수를 선택했을 때, gcd가 x가 되는 경우의 수. 
          (i번째 수가 반드시 포함)

 D[0][0] = 1
 D[i][gcd(x,A[i])] <- D[j][x]	(j < i)

 --
 */
int d[MAX_N][MAX_S];
vector<int> cdList[MAX_S];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int GCD()
{
	int ans = 0;
	
	memset(d, 0, sizeof(d));
	
	/*
	 * !!
	 * 각수의 모든 공약수를 구한다. 
	 * !!
	 */ 
	for (int i = 1; i < MAX_S; ++i) {
		for (int j = 1; j*j <= i; ++j)  {
			if ((i%j) == 0) {
				/*
				 * j*j이내 까지만 검사하므로 i/j 까지 한번더 넣어줘야 한다. (j*j != i) 
				 */
				cdList[i].push_back(j);
				if (j*j != i)
					cdList[i].push_back(i/j);
			}
		}
	}
	
#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i <= N; ++i)
		printf("%3d", A[i]);
	printf("\n");
#endif	
	/* 경우의 수를 구한다. */
	for (int i = 1; i <= N; ++i)  {
		d[i][A[i]] = 1;
		
		for (int j = 1; j < i; ++j) {
			/* 지금껏 나온 공약수들을 활용하여 다음 1로 나눠지는 공약수를 구한다. */ 
			for (int k = 0; k < cdList[A[j]].size(); ++k) {
				int t = cdList[A[j]][k];
				int g = gcd(t, A[i]);
				
#ifdef DEBUG
				printf(" iter(%d,%d) gcd(t=%d, Ai=%d)\n", i, j, t, A[i]);
#endif				
				d[i][g] += d[j][t];
				d[i][g] %= MAX_MOD;
			}
		}
		
		ans += d[i][1];
		ans %= MAX_MOD;
	}
	
	return ans;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\gcd.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", A + i);
		
	int result = GCD();
	printf("%d\n", result);
	return 0;
}

