#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;

const int MAX_N = 300000;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N;
int A[MAX_N+9];
int D[MAX_N+9]; int DP;

int LIS()
{
	D[0] = A[1];
	DP = 1;
	
	for (int i = 2; i <= N; ++i) {
		if (D[DP-1] < A[i]) {
			D[DP++] = A[i];
		}
		else {
			int* idx = std::lower_bound(D, D + DP, A[i]);
#ifdef DEBUG
			printf("*idx = %d\n", *idx);
#endif
			*idx = A[i];
		}
#ifdef DEBUG
		printf("%d : ");
		for (int j = 0; j < DP; ++j) 
			printf("%3d", D[j]);
		printf("\n");
#endif
	}
	return DP;
}

int main(int argc, char** argv) 
{
#ifdef DEBUG
	freopen("D:\\temp\\lis.txt", "r", stdin);
	freopen("D:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i) {
		scanf("%d", A + i);
	}
	
	int result = LIS();
	
	printf("%d\n", result);
	return 0;
}
