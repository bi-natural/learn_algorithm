/*
 * 단순다각형의 넓이
 * 
 --
 이차원 평면에 점 N개로 이루어진 단순 다각형이 주어진다. 이때 이 다각형이 평면에서 
 차지하는 면적을 구해보자. 다각형의 면적은 반드시 0보다 크다.

 <입력>
 첫째 줄에 다각형을 이루는 점의 갯수 (1≤N≤100,000) 이 주어지고,
 둘째 줄 부터 N개의 점의 정수 좌표(109≤x,y≤109)가 입력으로 주어진다.
 다각형의 좌표는 시계 방향 또는 반시계 방향 순서로 주어진다.
 --
 */ 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;

struct POINT {
	INT64 x, y;
	
	POINT() { }
	POINT(INT64 a, INT64 b) : x(a), y(b) { }

	bool operator==(const POINT& other) {
		return (x == other.x && y == other.y);	
	}
	
	INT64 norm2() const {
		return x*x + y*y;
	}
	
	INT64 DP(const POINT& b) const {
		return (x * b.x + y * b.y);
	}	

	INT64 CP(const POINT& b) const {
		return (x * b.y - b.x * y);
	}	
	
	int CCW(const POINT& other) const {
		INT64 value = CP(other);
		
		if (value > 0ll)
			return 1;
		else if (value < 0ll)
			return -1;
		else
			return 0;
	}
};

int CCW(POINT a, POINT b, POINT c) {
	POINT ab(b.x - a.x, b.y - a.y);
	POINT ac(c.x - a.x, c.y - a.y);
	
	return ab.CCW(ac);	
}

int CASE; 
int N;
POINT V[MAX_N];

INT64 ABS(INT64 a) {
	if (a < 0ll) return -a;
	return a;
}

INT64 ABS(INT64 a, INT64 b) {
	if (a < b) swap(a, b);
	return (a - b);
}

double AREA()
{
	/* add one */
	V[N+1].x = V[1].x;
	V[N+1].y = V[1].y;

	INT64 sum1 = 0, sum2 = 0;
	
	for (int i = 1; i <= N; ++i)
		sum1 += V[i].x * V[i+1].y;
	
	for (int i = 2; i <= N+1; ++i)
		sum2 += V[i].x * V[i-1].y;
		
	return (double)(ABS(sum1, sum2)) / 2.0;
}

INT64 AREA2()
{
	/* add one */
	V[N+1].x = V[1].x;
	V[N+1].y = V[1].y;

	INT64 sum1 = 0, sum2 = 0;
	
	for (int i = 1; i <= N; ++i)
		sum1 += V[i].x * V[i+1].y;
	
	for (int i = 2; i <= N+1; ++i)
		sum2 += V[i].x * V[i-1].y;
		
	return ABS(sum1, sum2);
}

INT64 AREA3()
{
	/* add one */
	INT64 area = 0ll;
	
	for (int i = 1; i < N; ++i)
		area += V[i].CP(V[i+1]);
	
	area += V[N].CP(V[1]);
	return ABS(area);
}

int main()
{
#ifdef DEBUG
	freopen("input\\crossproduct.txt", "r", stdin);
	freopen("output\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		POINT& v = V[i];
		scanf("%lld %lld", &v.x, &v.y);
	}
		
	INT64 result2 = AREA2();
	INT64 result3 = AREA3();
	// printf("%lld.%d\n", result2/2, (result2%2ll) ?  5 : 0);
	printf("%lld.%d\n", result3/2, (result3%2ll) ?  5 : 0);
	return 0;
}

