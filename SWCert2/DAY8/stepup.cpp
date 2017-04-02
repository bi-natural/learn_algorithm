#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N        100007
#define MAX_MODE 1000000007

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

int CASE; 
int N;
int A[MAX_N];

struct MAT2 {
	INT64 d[2][2];
	
	MAT2() { 
		d[0][0] = 1ll; 
		d[0][1] = 1ll; 
		d[1][0] = 1ll; 		
		d[1][1] = 0ll; 		
	}
	
	MAT2(const INT64& a00, const INT64& a01, const INT64& a10, const INT64& a11) {
		d[0][0] = a00; 
		d[0][1] = a01; 
		d[1][0] = a10; 		
		d[1][1] = a11; 				
	}
	
	MAT2 operator*(const MAT2& rhs) {
		MAT2 result;
		
		result.d[0][0] = (d[0][0] * rhs.d[0][0]) % MAX_MODE + 
			(d[0][1] * rhs.d[1][0]) % MAX_MODE;
		result.d[0][1] = (d[0][0] * rhs.d[0][1]) % MAX_MODE + 
			(d[0][1] * rhs.d[1][1]) % MAX_MODE;
		result.d[1][0] = (d[1][0] * rhs.d[0][0]) % MAX_MODE + 
			(d[1][1] * rhs.d[1][0]) % MAX_MODE;
		result.d[1][1] = (d[1][0] * rhs.d[0][1]) % MAX_MODE + 
			(d[1][1] * rhs.d[1][1]) % MAX_MODE;
		
		result.d[0][0] %= MAX_MODE;
		result.d[0][1] %= MAX_MODE;
		result.d[1][0] %= MAX_MODE;
		result.d[1][1] %= MAX_MODE;
		
		return result;
	}

	void print(){ 
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j)
				printf("%5d", d[i][j]);
			printf("\n");
		}
	}
};

MAT2 MULTI(const MAT2& a, int n)
{
	if (n == 1)		
		return a;
	
	MAT2 b = MULTI(a, n/2);
	
	b = b * b;
	if (n%2)
		b = b * a;
	
#ifdef DEBUG1
	printf("MULTI_N = %d\n", n);
	b.print();
#endif

	return b;
}

/*  
 * K = [ 1 1 ; 1 0 ]
 *
 *      K^(n-2) * [ F(2) F(1) ]
 * 
 */

INT64 STEPUP(int n)
{
#ifdef DEBUG
	printf("Input = %d\n", n);
#endif
	if (n < 2)
		return (INT64) n;
	
	MAT2 a(1ll, 1ll, 1ll, 0ll);
	MAT2 multi = MULTI(a, n-1);

#ifdef DEBUG
	printf(" A^%d \n", n-1);
	multi.print();
#endif	
	return (multi.d[0][0] + multi.d[0][1]) % MAX_MODE;
}

INT64 STEPUP2(int n)
{
#ifdef DEBUG
	printf("Input = %d\n", n);
#endif
	if (n < 2)
		return (INT64) n;
	
	MAT2 a(1ll, 1ll, 1ll, 0ll);
	MAT2 multi = MULTI(a, n);

#ifdef DEBUG
	printf(" A^%d \n", n);
	multi.print();
#endif	
	return (multi.d[1][0] + multi.d[1][1]) % MAX_MODE;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\stepup.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);

	INT64 result = STEPUP(N);
	printf("%lld\n", result);
	
#ifdef DEBUG
	printf(" ---------------------------- \n");
	for (int i = 2; i <= 10; ++i) {
		INT64 result1 = STEPUP(i);
		INT64 result2 = STEPUP2(i);
		printf("%lld %lld\n", result1, result2);
	}
#endif
	return 0;
}

