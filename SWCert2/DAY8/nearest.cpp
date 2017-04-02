/*
 * 가장 가까운 두점 
 --
2차원 평면상에 n개의 점이 주어졌을 때, 이 점들 중 가장 가까운 두 점을 구하는 프로그램을 작성하시오.

<입력> 
첫째 줄에 자연수 n(2≤n≤500,000)이 주어진다. 다음 n개의 줄에는 차례로 각 점의 
x,y좌표가 주어진다. 각각의 좌표는 절댓값이 10,000을 넘지 않는 정수이다.
 --
 
 
 좌표를 공간분할하여 계산한 값을 다시 병합할때 이전에 구한 최소값(distance)내에 있는 좌표들만을
 골라서 병합비교하면서 최소값을 업데이트한다.
 이때, 다른 쪽에 있는 좌표들도 최대 8개를 넘지 않는다.  
 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N	500007
#define INF     100000000

using namespace std;

typedef long long INT64;

struct POINT {
	int x, y;
};

int CASE; 
int N;
POINT A[MAX_N];

bool sort_X(const POINT& lhs, const POINT& rhs) {
	return lhs.x < rhs.x;
}

bool sort_Y(const POINT& lhs, const POINT& rhs) {
	return lhs.y < rhs.y;
}

int getDist2(const POINT& a, const POINT& b)
{
	int x = a.x - b.x;
	int y = a.y - b.y;
	
	return x*x + y*y;	
}

#define SQR(a) ((a)*(a))

int NEAREST2(int s, int e)
{
	if (e - s < 5) {
		int ret = getDist2(A[s], A[s+1]);
		
		for (int i = s; i < e; ++i)
			for (int j = i+1; j <= e; ++j)
				ret = min(ret, getDist2(A[i], A[j]));

		return ret;
	}
	
	int mid = (s + e) >> 1;
	int lmax = A[mid].x + 1;
	
	int d1 = NEAREST2(s, mid);
	int d2 = NEAREST2(mid+1, e);
	int d  = min(d1, d2);
	
	vector<POINT> v1, v2;
	for (int i = s; i <= mid; ++i) if (SQR(A[i].x - lmax) <= d) {
		v1.push_back(A[i]);
	}
	
	for (int i = mid+1; i <= e; ++i) if (SQR(A[i].x - lmax) <= d) {
		v2.push_back(A[i]);
	}
	
	sort(v1.begin(), v1.end(), sort_Y);
	sort(v2.begin(), v2.end(), sort_Y);
	
	int ret = d;
	
	for (int i = 0, j = 0; i < v1.size(); ++i) {
		while (j < v2.size() && SQR(v1[i].y - v2[j].y) > d) 
			j++;
			
		for (int k = j; k < j + 8 && k < v2.size(); ++k) 
			ret = min(ret, getDist2(v1[i], v2[k]));
	}
	
	return ret;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\nearest.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &A[i].x, &A[i].y);
	}
	
	sort(A + 1, A + N + 1, sort_X);
	
	int result = NEAREST2(1, N);
	printf("%d\n", result);
	return 0;
}

