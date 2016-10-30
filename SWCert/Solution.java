/////////////////////////////////////////////////////////
// SDS SW Certificate
// Problem : 그림자 (Professional)
// Author  : SW Competency Development TF
// Copyright(c) 2016 Samsung SDS Co. ltd.
// All rights reserved. / Confidential
// 본 문서를 SDS 직원이 아닌 외부인에게 공유하거나
// 외부 사이트 등 공중에 게시하는 행위를 절대 금합니다.
/////////////////////////////////////////////////////////

import java.io.FileInputStream;
import java.util.LinkedList;
import java.util.Scanner;

public class Solution {
	static int Answer;
	static int M, N;
	
	// 지원자의 월급
	static int[] S = new int[20];
	
	// 지원자의 악기 연주 정보
	static int[][] P = new int[24][20];
	
	// 악기별 연주가능한 지원자가 있는지 여부
	static int[] C = new int[24];
	
	// 솔루션 저장 리스트
	static LinkedList<Integer> list = new LinkedList<Integer>();
	
	
	public static void main(String[] args) throws Exception {
		
		/*
		 * 아래의 메소드 호출은 앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다. 여러분이
		 * 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후, 이 코드를 프로그램의 처음 부분에
		 * 추가하면 이후 입력을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다. 따라서 테스트를 수행할 때에는 아래
		 * 주석을 지우고 이 메소드를 사용하셔도 좋습니다. 단, 채점을 위해 코드를 제출하실 때에는 반드시 이 메소드를 지우거나 주석
		 * 처리 하셔야 합니다.
		 */
		System.setIn(new FileInputStream("sample_input.txt"));

		/*
		 * 표준입력 System.in 으로부터 스캐너를 만들어 데이터를 읽어옵니다.
		 */
		Scanner sc = new Scanner(System.in);

		/*
		 * 테스트 케이스의 수를 입력 받습니다.
		 */
		int T = sc.nextInt();
		
		/*
		 * T 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
		 */
		for(int test_case = 1; test_case <= T; ++test_case) {
			// 지원자의 수
			N = sc.nextInt();
			
			// 악기의 수
			M = sc.nextInt();
			
			// 지원자의 월급
			for(int i = 0; i < N; i++) {
				S[i] = sc.nextInt();
			}
			
			// 지원자의 악기 연주 정보
			for(int i = 0; i < M; i++) {
				for(int j = 0; j < N; j++) {
					P[i][j] = sc.nextInt();
				}
			}
			
			/*
			* 
			* 이곳에 여러분의 코드를 작성합니다.
			* 테스트 케이스 개수 T만큼 각각의 결과가 Answer로 최종 출력 됩니다.
			* 
			*/
			Answer = Integer.MAX_VALUE;
			list.clear();
			
			for(int i = 0; i < 2; i++) {
				if(i == 1) {
					list.add(0);
				}
				
				backtrack(0, i, 0);
				
				if(i == 1) {
					list.removeLast();
				}
			}
			
			
			/* 결과 값 출력 */
			System.out.println("#" + test_case + " " + Answer);
		}
	}
	
	// pos : 연주자 번호, val : 채용여부, cost : 현재까지 계산된 코스트
	public static void backtrack(int pos, int val, int cost) {
		int totalCost = cost;
		
		if(val == 1) {
			totalCost += S[pos];
		}
		
		if(pos == N - 1) {
			int covered = 0;
			
			for(int i = 0; i < M; i++) {
				C[i] = 0;
			}
			
			// 모든 악기에 대해서 가능한 연주자가 한 명 이상인지를 판단
			// 리스트에 현재까지 저장된 연주자 정보를 가저옴
			for(int i : list) {
				
				for(int j = 0; j < M; j++) {
					// i 연주자가 j 악기를 연주할 수 있는 경우
					if(P[j][i] == 1 && C[j] == 0) {
						covered ++;
						C[j] = 1;
					}
				}
			}
			
			// 모든 악기에 대해 가능한 연주자가 한 명 이상이고
			// 계산된 비용이 현재까지 찾아낸 해보다 작을 경우 저장
			if(covered == M && totalCost < Answer) {
				Answer = totalCost;
			}
			
			return;
		}
		
		// 계산된 비용이 현재까지 찾은 최적해보다 클 경우 더 이상 하위의 경우는 탐색하지 않아도 된다. 
		if(totalCost > Answer) {
			return;
		}
		
		// 채용/채용 하지 않음 두 가지의 경우가 있다.
		for(int i = 0; i < 2; i++) {
			// 채용일 경우 연주자 번호을 리스트에 저장
			if(i == 1) {
				list.add(pos + 1);
			}
			
			// 다음 연주자로 재귀호출
			backtrack(pos + 1, i, totalCost);
			
			// 앞에서 저장된 연주자 번호를 리스트에서 제거
			if(i == 1) {
				list.removeLast();
			}
		}
	}
}
