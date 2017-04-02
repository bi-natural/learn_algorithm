/*
 * 점의 위치 
 * 
 --
 이차원 평면에서 점 N개로 이루어진 다각형이 주어진다.
 그리고 평면위의 점 P1, P2가 주어졌을때 점 P1, P2가 다각형의 외부에 있는지, 
 내부에 있는지 판별하는 프로그램을 작성하시오.

 점 P1, P2 는 주어진 다각형의 선분 위에 존재하지는 않는다.
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
POINT points[MAX_N];

bool between(INT64 a, INT64 b, INT64 c)
{
	if (a > b) swap(a, b);
	return (a <= c && c <= b);
}

/*
 * a, b, c 세 점이 한 직선상에 있다.  
 */
bool on_the_line(const POINT& a, const POINT& b, const POINT& c)
{
	/* 세점이 평행한 경우 */
	if (CCW(a, b, c) == 0) {
		int ccw1 = c.CCW(a);
		int ccw2 = c.CCW(b);

		/* c에서 볼때 a, b 까지의 CCW가 서로 엇갈릴 때 */ 
		return (ccw1 * ccw2 < 0);
	}
	return false;
}

/*
 * a,b 라인과 c,d라인이 교차한다. 
 *
 * 1) a, b 라인에 대해 c, d 가 모두 다른 방향(한쪽이 CCW이면 다른 한쪽은 CW)
 * 2) c, d 라인에 대해 a, b 역시 모두 다른 방향 
 *
 * 두 조건을 만족하면 평행하거나 교차하는 경우를 제외하고는 모두 교차한다. 
 */
bool intersect_TowLines(const POINT&a, const POINT& b, const POINT& c, const POINT& d)
{
	int ccw_ab = CCW(a, b, c) * CCW(a, b, d);
	int ccw_cd = CCW(c, d, a) * CCW(c, d, b);
	
	if (ccw_ab == 0 && ccw_cd == 0) {
		/* ab 라인과 cd 라인이 평행함 */
		return false; 
	}
	return (ccw_ab <= 0 && ccw_cd <= 0);
}

int InOrOut(POINT t)
{
#ifdef DEBUG
	printf(" -- Input t = (%lld, %lld)\n", t.x, t.y);
#endif

	/* virtually add first on to Last position */
	points[N+1].x = points[1].x, points[N+1].y = points[1].y;
	
	/* 가상의 점을 ( 1000000007ll, t.y + 1 )로 하면 
	   1) 어떤 점과도 일치하지 않는다. 
	   2) 어떤 선분과도 일치하지 않는다.
	*/ 
	POINT MaxT(1000000007ll, t.y + 1);
	int cross_points = 0;
	
	for (int i = 1; i < N; ++i) {
#ifdef DEBUG
			printf(" !! Tested with points i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif			
		
		/* 점이 일치하는  경우 */
		if (points[i] == t || points[i+1] == t) {
#ifdef DEBUG
			printf(" !! Matched with points i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif			
			return 1;
		}
		
		/* 
		 * 점(t)가 선분(points[i],points[i+1])위에 있는 경우 
		 * 
		 * 1. 서로다른 점 3개로 이루어진 2개의 직선이 평행하다면 한점은 중간에 있음.
		 * 2. 점(t)를 기준으로 각각 points[i], points[i+1]의 CCW를 구했는데 방향이 반대이면 t는 중간에 있다. 
		 */

		if (on_the_line(points[i], points[i+1], t)) {
#ifdef DEBUG
			printf(" !! Matched On The Line i = (%lld, %lld) j = (%lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
#endif						
			return 1;
		}
				 
		/* 점(t)에서 우측 최대값까지의 직선(T)에 대해 점의 y값이 선분의 사이값에 있는 경우에 대해 체크 */ 
		if (between(points[i].y, points[i+1].y, t.y)) 
		{
			bool pti = on_the_line(t, MaxT, points[i]);
			bool ptj = on_the_line(t, MaxT, points[i+1]);
			
			/* 직선(T)와    두점이 모두 만나는 경우 : 교차점으로 카운트하지 않음. */
			if (pti && ptj) 
				continue;		
			
			/* 직선(T)와    한점이 만나는 경우 : 교차점으로 카운트하지 않음. */	
			if (pti || ptj)
				continue;
			
			/* 직선(T)와    선이 교차하는 경우 */
			if (intersect_TowLines(t, MaxT, points[i], points[i+1])) {				
#ifdef DEBUG
				printf(" !! Check Intersec Line 1 (%lld, %lld, %lld, %lld) Test = (%lld, %lld, %lld, %lld)\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y, t.x, t.y, MaxT.x, MaxT.y);
#endif
				cross_points ++;	
			}
			
			/* 적선(T)와    선이 교차하지 않는 경우 */ 
		}
	}
	
	/* 교차점이 홀수이면 안에 있음 */ 
	return (cross_points % 2);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\inner.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		POINT& v = points[i];
		scanf("%lld %lld", &v.x, &v.y);
	}
	
	for (int i = 1; i <= 2; ++i) {
		POINT test;
		scanf("%lld %lld", &test.x, &test.y);
		
		int result = InOrOut(test);
		printf("%s\n", result ? "in" : "out");		
	}
	
	return 0;
}

