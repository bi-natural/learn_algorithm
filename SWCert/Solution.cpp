/////////////////////////////////////////////////////////
// SDS SW Certificate
// Problem : 그림자 (Professional)
// Author  : SW Competency Development TF
// Copyright(c) 2016 Samsung SDS Co. ltd.
// All rights reserved. / Confidential
// 본 문서를 SDS 직원이 아닌 외부인에게 공유하거나
// 외부 사이트 등 공중에 게시하는 행위를 절대 금합니다.
/////////////////////////////////////////////////////////
#include <cstdio>

int Answer;
int M, N;
int S[20];
int P[24][20];
int C[24];

int List[20], nList; // 뽑을 사람의 번호 모음

void backtrack(int pos, int val, int cost) {
	int totalCost = cost;

	if (val == 1) {
		totalCost += S[pos];
	}

	// 모든 연주자를 반영한 경우
	if (pos == N - 1) {
		// 커버하는 악기의 개수
		int covered = 0;

		for (int i = 0; i < M; i++) {
			C[i] = 0;
		}

		for (int i = 0; i < nList; i++) {
			for (int j = 0; j < M; j++) {
				if (P[j][List[i]] == 1 && C[j] == 0) {
					covered++;
					C[j] = 1;
				}
			}
		}

		// 악기 M개를 모두 커버하고 월급의 총 합이 최소이면 갱신함.
		if (covered == M && totalCost < Answer) {
			Answer = totalCost;
		}

		return;
	}

	if (totalCost > Answer) {
		return;
	}

	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			List[nList++] = pos + 1;
		}

		backtrack(pos + 1, i, totalCost);

		if (i == 1) {
			nList--;
		}
	}
}


int Main() {

	int test_case, T;

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {
		// 지원자의 수 N, 악기의 수 M
		scanf("%d %d", &N, &M);

		// 지원자의 월급
		for (int i = 0; i < N; i++) {
			scanf("%d", &S[i]);
		}

		// 지원자의 악기 연주 정보
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &P[i][j]);
			}
		}

		/*
		*
		* 이곳에 여러분의 코드를 작성합니다.
		* 테스트 케이스 개수 T만큼 각각의 결과가 Answer로 최종 출력 됩니다.
		*
		*/
		Answer = 99999999;
		nList = 0;

		for (int i = 0; i < 2; i++) {
			if (i == 1) {
				List[nList++] = 0;
			}

			backtrack(0, i, 0);

			if (i == 1) {
				nList--;
			}
		}


		/* 결과 값 출력 */
		printf("#%d %d\n", test_case, Answer);
	}

	return 0;
}

