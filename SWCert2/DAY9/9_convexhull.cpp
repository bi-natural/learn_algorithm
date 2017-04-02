/*
 * Convex Hull 구하기 
 *
 --
 2차원 평면에 N개의 점이 주어졌을 때, 이들 중 몇 개의 점을 골라 볼록 다각형을 만드는데, 
 나머지 모든 점을 내부에 포함하도록 할 수 있다. 
 이를 볼록 껍질 (Convex Hull) 이라 한다.
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;

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

POINT A[MAX_N];

bool cmp_Theta(const POINT& lhs, const POINT& rhs) {
	int ccw = CCW(A[1], lhs, rhs);
	
	if (ccw > 0) return true;
	if (ccw == 0) {
		POINT l(lhs.x - A[1].x, lhs.y - A[1].y);
		POINT r(rhs.x - A[1].x, rhs.y - A[1].y);
		
		return (l.norm2() < r.norm2());
	}

	return false;
}

#define PI 3.141592

bool cmp_Theta2(const POINT& lhs, const POINT& rhs) {
	double ld = atan2(lhs.y - A[1].y, lhs.x - A[1].x) * 180.0 / PI;
	double rd = atan2(rhs.y - A[1].y, rhs.x - A[1].x) * 180.0 / PI;

	return (ld < rd);
}

void CHOOSE_BASE() 
{
	int idx = 1;	
	for (int i = 1; i <= N; ++i) {
		POINT& p = A[i];
		
		if (p.y < A[idx].y) {
			idx = i;
		} else if (p.y == A[idx].y && p.x > A[idx].x) {
			idx = i;
		}
	}

	if (idx != 1)
		swap(A[idx], A[1]);

#ifdef DEBUG
	printf(" Base Point Set to A[1] = (%lld, %lld)\n", A[1].x, A[1].y);
#endif	
}

void MAKE_CCW()
{
	CHOOSE_BASE();
	
	sort(A + 2, A + N + 1, cmp_Theta);
	
#ifdef DEBUG	
	for (int i = 1; i <= N; ++i) {
		POINT p(A[i].x - A[1].x, A[i].y - A[1].y);
		
		printf(" (%lld, %lld) - (%lld, %lld) : ", A[1].x, A[1].y, A[i].x, A[i].y);
		printf(" (%3lld, %3lld) = %.5f\n", p.x, p.y, atan2((double)p.y, (double)p.x) * 180/PI);
	}
	printf("\n");
#endif
}

vector<int> CONVEXHULL3()
{
	vector<int> rs;	
	
	MAKE_CCW();
	rs.push_back(1);
	for (int current = 2; current <= N; ++current) {
		if (rs.size() > 1 && CCW(A[rs[rs.size()-2]],A[rs[rs.size()-1]], A[current]) <= 0)
			rs.pop_back();
		rs.push_back(current);
	}
	return rs;
}

vector<int> CONVEXHULL()
{
	vector<int> result;
	stack<int> pts;
	int last;
	
	MAKE_CCW();

	pts.push(1);
	last = 2;
	
	/* virtually add A[1] to N+1 position */
	A[N+1].x = A[1].x;
	A[N+1].y = A[1].y;
	
	for (int current = last+1; current <= N+1; ++current) {
		if (pts.empty()) 
			break;
			
		int top = pts.top();
#ifdef DEBUG
		int ccw = CCW(A[top], A[last], A[current]);
		printf(" -- CCW (%lld, %lld) (%lld, %lld) (%lld, %lld) = %d\n", A[top].x, A[top].y, A[last].x, A[last].y, A[current].x, A[current].y, ccw);
#endif
		while (CCW(A[top], A[last], A[current]) <= 0) {
			/* 중간의 A[last]를 버린다. */ 
			last = top;
#ifdef DEBUG
			printf(" !! pop %d\n", last);
#endif			
			pts.pop();
			
			/* 새로운 top 참조 */ 
			if (pts.empty())
				break;

			top = pts.top(); 
#ifdef DEBUG
			ccw = CCW(A[top], A[last], A[current]);
			printf(" ++ CCW (%lld, %lld) (%lld, %lld) (%lld, %lld) = %d\n", A[top].x, A[top].y, A[last].x, A[last].y, A[current].x, A[current].y, ccw);
#endif					
		}
		
#ifdef DEBUG
		printf(" !! push %d\n", last);
#endif
		pts.push(last);
		last = current;
	}
		
	while (!pts.empty()) {
		result.push_back(pts.top());
		pts.pop();
	}
	
	return result;
}

vector<int> CONVEXHULL2()
{
	vector<int> result;
	stack<int> pts;
	int last;
	
	MAKE_CCW();

	pts.push(1);
	last = 2;
	
	/* virtually add A[1] to N+1 position */
	A[N+1].x = A[1].x;
	A[N+1].y = A[1].y;
	
	for (int current = last+1; current <= N+1; ++current) {
		if (pts.empty()) 
			break;
			
		int top = pts.top();
#ifdef DEBUG
		int ccw = CCW(A[top], A[last], A[current]);
		printf(" -- CCW (%lld, %lld) (%lld, %lld) (%lld, %lld) = %d\n", A[top].x, A[top].y, A[last].x, A[last].y, A[current].x, A[current].y, ccw);
#endif
		while (CCW(A[top], A[last], A[current]) <= 0) {
			/* 중간의 A[last]를 버린다. */ 
			last = top;
#ifdef DEBUG
			printf(" !! pop %d\n", last);
#endif			
			pts.pop();
			
			/* 새로운 top 참조 */ 
			if (pts.empty())
				break;

			top = pts.top(); 
#ifdef DEBUG
			ccw = CCW(A[top], A[last], A[current]);
			printf(" ++ CCW (%lld, %lld) (%lld, %lld) (%lld, %lld) = %d\n", A[top].x, A[top].y, A[last].x, A[last].y, A[current].x, A[current].y, ccw);
#endif					
		}
		
#ifdef DEBUG
		printf(" !! push %d\n", last);
#endif
		pts.push(last);
		last = current;
	}
		
	while (!pts.empty()) {
		result.push_back(pts.top());
		pts.pop();
	}
	
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\convexhull.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		POINT& p = A[i];	
		scanf("%lld %lld", &p.x, &p.y);
	}

	vector<int> result = CONVEXHULL();
	
#ifdef DEBUG
	for (int i = 0; i < result.size(); ++i)
		printf("%3d ", result[i]);
	printf("\n");
#endif

	printf("%d\n", result.size());
	return 0;
}

