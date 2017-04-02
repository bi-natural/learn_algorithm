#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N   50007
#define MAX_MOD	10007

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

int CASE; 
int N;
int A[MAX_N];

INT64 D[MAX_N];
INT64 DSUM2[MAX_N];
INT64 C[MAX_N];

void precalc_D1(int n)
{
	D[0] = 1;
	D[1] = 1;
	D[2] = 4;
	
#ifdef DEBUG
	printf("Indx = ");
	for (int i = 3; i <= 10; ++i) {
		printf("%10d", i);
	}
	printf("\n");
#endif
	for (int i = 3; i <= n; ++i) {
		D[i] = (((4 * D[i-1] % MAX_MOD) + MAX_MOD) - D[i-2]) % MAX_MOD;
	}
#ifdef DEBUG
	printf("D[i] = ");
	for (int i = 3; i <= 10; ++i)
		printf("%10d", D[i]);
	printf("\n");
#endif
}

void precalc_C1(int n)
{
	DSUM2[1] = 0;
 	for (int i = 1; i <= n; ++i) {
		DSUM2[i] = DSUM2[i-1] + 2*D[i];
		DSUM2[i] %= MAX_MOD;		
	}
		
	for (int i = 3; i <= n; ++i) {
		C[i] = i * (D[i] + DSUM2[i-1]);
		C[i] %= MAX_MOD;
	}

#ifdef DEBUG
	printf("C[i] = ");
	for (int i = 3; i <= 10; ++i)
		printf("%10d", C[i]);
	printf("\n");
#endif
}

void precalc()
{
	precalc_D1(MAX_N);
	precalc_C1(MAX_N);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\connect.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	precalc();
	
	scanf("%d", &CASE);
	
	for (int t = 1; t <= CASE; ++t) {
		scanf("%d", &N)	;
		
		printf("%lld %lld\n", D[N], C[N]);		
	}
	return 0;
}

