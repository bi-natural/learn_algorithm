/*
 * 보이스카우트
 *
 --
뉴 잉글랜드의 보이 스카우트 단체는 매년 스카우트 올림픽을 개최한다. 
각 스카우트 팀에게 임무를 배정하고 완료 점수를 통해 승자를 가린다. 
대회가 끝나고 나서는 모두 승자를 위해 밤새 기타를 치며 스카우트 노래를 부른다.

올해는 Maine에 있는 아름다운 숲에서 올림픽을 개최했다. 이번에 각 팀에게 주어진 
임무는 매우 어렵다. 각 팀은 숲 안에 있는 나무 하나를 정해서 시작점으로 삼는다. 
그리고 다른 나무를 향해서 직진하고, 다음 나무에 도착하면 또 다른 나무를 향해서 직진한다. 
위와 같은 방법으로 나무 사이를 이동할 때 가장 많은 개수의 나무를 거친 팀이 승리하게 된다. 
단, 다음 나무로 이동할 때에 반시계 방향으로 돌아야만 한다. 즉, 나무에 도착했을 때에 
다음 나무로 가기 위해서는 왼쪽으로 180도 미만으로 회전할 수 있다는 뜻이다. 또한, 각 팀은 
마지막에 처음 나무로 돌아와야 하는데, 이 때 자신이 두번째로 들렀던 나무도 여전히 왼쪽으로 
180도 미만으로 회전해서 갈 수 있어야 한다. 추가로 지나간 경로를 그렸을 때 단순 다각형을 
구성해야 한다.

스카우트 팀들은 올림픽에 노트북을 들고오지 않았기 때문에 승리하기 위해서 어떤 경로로 
가야 승리할 수 있는 지 계산할 수 없다. 그래서 당신에게 승리하기 위해서 이동할 수 있는 
최대 나무 개수를 구해달라고 요청했다.

Maine의 아름다운 숲에 있는 나무 개수 N과 각 나무의 위치가 2차원 좌표로 주어졌을 때, 
항상 왼쪽으로 회전하며 이동할 때 지날 수 있는 나무 개수의 최대값을 구하여라.

<입력>
 첫 번째 줄에는 나무의 개수 N(3≤N≤100)이 주어진다. 다음 
 N개의 줄에 걸쳐서 각 나무의 좌표 x,y(?106≤x,y≤106)이 주어진다. 
 각 좌표는 소수점 이하 최대 2자리까지 주어진다. 어떠한 세 나무도 한 직선 위에 존재하지 않음이 보장된다.

<힌트>
 N이 작다. O(N^3) 정도 알고리즘이 있으면 된다. (DP)
 DP를 사용하되, 제약조건은 CCW 방향으로만 된 다음 점(나무)들을 선택해야 한다.
  
 --
 */ 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 107

using namespace std;

typedef long long INT64;

struct POINT {
	INT64 x, y;
	
	POINT() { }
	POINT(INT64 a, INT64 b) : x(a), y(b) { }

	INT64 norm2() const {
		return x*x + y*y;
	}
	
	INT64 DP(const POINT& b) const {
		return (x * b.x + y * b.y);
	}	

	INT64 CP(const POINT& b) const {
		return (x * b.y - b.x * y);
	}	
};

int CCW(POINT a, POINT b, POINT c) {
	POINT ab(b.x - a.x, b.y - a.y);
	POINT ac(c.x - a.x, c.y - a.y);
	
	INT64 value = ab.CP(ac);
	
	if (value > 0ll)
		return 1;
	else if (value < 0ll)
		return -1;
	else
		return 0;
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

void MAKE_CCW()
{
	sort(A + 2, A + N + 1, cmp_Theta);
	
#ifdef DEBUG	
#define PI 3.141592

	for (int i = 1; i <= N; ++i) {
		POINT p(A[i].x - A[1].x, A[i].y - A[1].y);
		
		printf(" (%lld, %lld) - (%lld, %lld) : ", A[1].x, A[1].y, A[i].x, A[i].y);
		printf(" (%3lld, %3lld) = %.5f\n", p.x, p.y, atan2((double)p.y, (double)p.x) * 180/PI);
	}
	printf("\n");
#endif
}

/*
 * D[i][j] : 시작점에서 시작하여 i번 노드를 찍고 j로 끝났을 떄 만나는 나무의 최대 개수
 * 
 */
int D[MAX_N][MAX_N];

int BOYSCOUT()
{
	MAKE_CCW();
		
	memset(D, 0, sizeof(D));

    for (int i = 2; i <= N; ++i) 
		D[1][i] = 2;
    
    for (int i = 1; i < N; ++i) 
		for (int j = i+1; j <= N; ++j) 
			if (D[i][j] > 0) {  
		        for (int k = j+1; k <= N; ++k) {
				 	if (CCW(A[i],A[j],A[k]) >= 0)
        		    	D[j][k] = max(D[j][k], D[i][j]+1);		        	
				}
    		}	
    		
    int result = 0;
    for (int i = 2; i < N; ++i) 
		for (int j = i+1; j <= N; ++j) 
			if (CCW(A[i], A[j], A[1]) >= 0)
        		result = max(result, D[i][j]);
        		
    return result;	
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\boyscout.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);

	int idx = 1;	
	for (int i = 1; i <= N; ++i) {
		double a, b;
		POINT& p = A[i];
		
		scanf("%lf %lf", &a, &b);
		p.x = (INT64) (a * 100);
		p.y = (INT64) (b * 100);
		
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

	int result = BOYSCOUT();
	printf("%d\n", result);
	return 0;
}

