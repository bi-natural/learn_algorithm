/* matching */

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 10;
const int MAX_DAYS = 10;
int CASE;
int N, M, K;

double f[MAX_N+1][MAX_N+1];

vector<int> link[MAX_N + 1];

double ali[MAX_N + 1][MAX_N + 1][MAX_DAYS + 1];
double noa[MAX_N + 1][MAX_N + 1][MAX_DAYS + 1];

#if 0
double result[MAX_N + 1][MAX_DAYS + 1];

struct tree {
	int day;
	int node;
	double probility;
	vector<tree> children;

	void set_root(int n) {
		this->day = 1;
		this->node = n;
		this->probility = 1.0;
		children.clear();
	}

	void extend_day() {

	}

	bool add_child(int n, int child, double p) {
		if (node == n) {
			tree t;

			t.day = this->day + 1;
			t.node = child;
			t.probility = this->probility * p;
			children.push_back(t);
			return true;
		}
		else {
			for (int i = 0; i < children.size(); ++i) {
				if (add_child(n, child, p))
					return true;
			}
			return false;
		}
	}

	void delete_children() {
		for (int i = 0; i < children.size(); ++i) {
			children[i].delete_children();
		}
	}
};

tree ali_tree, noa_tree;

double t2()
{
	/* matching possilbity */
	double result_f = 0.0;
	double last_possibility = 0.0;
	int last_meet_cities = 0;

	ali[1][1] = 1.0;
	noa[N][1] = 1.0;

	for (int d = 1; d < M; ++d) {
		double ali_f = 0.0, noa_f = 0.0;

		for (int j = 1; j <= N; ++j) {
			ali_f += ali[j][d];
			noa_f += noa[j][d];
		}

		printf("[%d] ali = %.03f\n", d, ali_f);
		printf("[%d] noa = %.03f\n", d, noa_f);


		/* find d+1 day ; ali/noa travel city */
		for (int j = 1; j <= N; ++j) {
			if (ali[j][d] > 0.0) {
				for (int k = 0; k < link[j].size(); ++k) {
					int& next = link[j][k];

					ali[next][d + 1] += ali[j][d] * f[j][next];
				}
			}

			if (noa[j][d] > 0.0) {
				for (int k = 0; k < link[j].size(); ++k) {
					int& next = link[j][k];

					noa[next][d + 1] += noa[j][d] * f[j][next];
				}
			}
		}


		/* d+1 met ? */
		double meet_possibility = 0.0;
		int meet_cities = 0;

		for (int j = 1; j <= N; ++j) {
			if (ali[j][d + 1] > 0.0 && noa[j][d + 1] > 0.0) {

				meet_possibility += (ali[j][d + 1] * noa[j][d + 1]);

				printf("%d meet at %d (%.3f, %.3f) = %.3f\n", d + 1, j, ali[j][d + 1], noa[j][d + 1], (ali[j][d + 1] * noa[j][d + 1]));

				meet_cities++;
			}
		}

		if (meet_cities > 0) {
			result_f += (meet_possibility - last_possibility / (double)meet_cities);
		}
		last_possibility = meet_possibility;

		printf("%d meet_cities = %d\n", d+1, meet_cities);
		printf("%d meet_possib = %.03f\n", d+1, meet_possibility);
		printf("%d reuslt = %.03f\n", d+1, result_f);
	}

	return result_f;
}

double t1()
{
	/* matching possilbity */
	double result_f = 0.0;

	ali[1][1] = 1.0;
	noa[N][1] = 1.0;

	for (int d = 2; d <= M; ++d) {
		for (int j = 1; j <= N; ++j) {
			for (int i = 0; i < link[j].size(); ++i) {	/* �ִ� 3�� */
				for (int k = 0; k < link[j].size(); ++k) { /* �ִ� 3�� */
					if (i != k) {

					}
				}
			}
		}
	}

	for (int d = 2; d <= M; ++d) {
		for (int j = 1; j <= N; ++j) {
			for (int i = 1; i <= N; ++i) {
				if (f[i][j] > 0.0) {
					/* exclude the same start */
					if (ali[i][d - 1] > 0.0 && noa[i][d - 1] > 0.0) {
						printf("ali: d[%d] <prune> %d -> %d\n", d, i, j);
						printf("noa: d[%d] <prune> %d -> %d\n", d, i, j);
						continue;
					}

					/* update ali travel */
					if (ali[i][d - 1] > 0.0) {
						printf("ali: d[%d] %d -> %d (%.03f)\n", d, i, j, ali[i][d - 1] * f[i][j]);
						ali[j][d] += (ali[i][d - 1] * f[i][j]);
					}

					/* update noa travel */
					if (noa[i][d - 1] > 0.0) {
						printf("noa: d[%d] %d -> %d (%.03f)\n", d, i, j, noa[i][d - 1] * f[i][j]);
						noa[j][d] += (noa[i][d - 1] * f[i][j]);
					}
				}
			}

			if (ali[j][d] > 0.0 && noa[j][d] > 0.0) {
				result[j][d] = (ali[j][d] * noa[j][d]);
			}
		}
	}

#if 0
	/* cacl possiblity */
	ali[1][1] = 1.0;

	for (int d = 2; d <= M; ++d) {
		for (int j = 1; j <= N; ++j) {
			for (int z = 1; z <= N; ++z) {

				if (ali[z][d - 1] > 0.0 && f[z][j] > 0.0) {
					ali[j][d] += (ali[z][d - 1] * f[z][j]);
				}


			}
		}
	}
#endif

	printf("ali:\n");
	for (int d = 1; d <= M; ++d) {
		printf("day %d: ", d);
		for (int j = 1; j <= N; ++j) {
			printf("%.03f ", ali[j][d]);
		}
		printf("\n");
	}

#if 0
	noa[N][1] = 1.0;

	for (int d = 2; d <= M; ++d) {
		for (int j = 1; j <= N; ++j) {
			for (int z = 1; z <= N; ++z) {
				if (noa[z][d - 1] > 0.0 && f[z][j] > 0.0) {
					noa[j][d] += (noa[z][d - 1] * f[z][j]);
				}
			}
		}
	}

#endif
	printf("noa:\n");
	for (int d = 1; d <= M; ++d) {
		printf("day %d: ", d);
		for (int j = 1; j <= N; ++j) {
			printf("%.03f ", noa[j][d]);
		}
		printf("\n");
	}





#if 0
	for (int d = 2; d <= M; ++d) {
		for (int j = 1; j <= N; ++j) {

			if (ali[j][d] > 0.0 && noa[j][d] > 0.0) {
				result[j][d] = (ali[j][d] * noa[j][d]);

				for (int z = 1; z <= N; ++z) {
					if (f[z][j] > 0.0 && result[z][d - 1] > 0.0) {
						result[j][d] -= (f[z][j] * result[z][d - 1]);
					}
				}

				result_f += result[j][d];
			}
		}
	}
#endif

	printf("possilbity:\n");
	for (int d = 1; d <= M; ++d) {
		printf("day %d: ", d);
		for (int j = 1; j <= N; ++j) {
			printf("%.03f ", result[j][d]);
			result_f += result[j][d];
		}
		printf("\n");
	}


	return result_f;
}

void t3()
{
	ali_tree.set_root(1);
	noa_tree.set_root(N);

}

#endif

struct dayLog {
	double val[MAX_N + 1][MAX_N + 1];
};

dayLog ali_p[2];
dayLog noa_p[2];

double t4()
{
	/* matching possilbity */
	double result_f = 0.0;

	for (int j = 1; j <= N; ++j) {
		for (int k = 0; k <= N; ++k) {
			ali_p[1].val[j][k] = 0.0;
			noa_p[1].val[j][k] = 0.0;
		}
	}

	ali_p[1].val[1][0] = 1.0;	/* sum */
	ali_p[1].val[1][1] = 1.0;
	noa_p[1].val[N][0] = 1.0;	/* sum */
	noa_p[1].val[N][N] = 1.0;

	for (int d = 1; d < M; ++d) {
		int now = d % 2;
		int tomorrow = (d + 1) % 2;

		/* init tommorow */
		for (int j = 1; j <= N; ++j) {
			for (int k = 0; k <= N; ++k) {
				ali_p[tomorrow].val[j][k] = 0.0;
				noa_p[tomorrow].val[j][k] = 0.0;
			}
		}

		/* find d++ day ; ali/noa travel city */
		for (int j = 1; j <= N; ++j) {

			if (ali_p[now].val[j][0] > 0.0) {
				for (int k = 0; k < link[j].size(); ++k) {
					int& next = link[j][k];

					ali_p[tomorrow].val[next][j] = ali_p[now].val[j][0] * f[j][next];
					ali_p[tomorrow].val[next][0] += ali_p[tomorrow].val[next][j];
				}
			}

			if (noa_p[now].val[j][0] > 0.0) {
				for (int k = 0; k < link[j].size(); ++k) {
					int& next = link[j][k];

					noa_p[tomorrow].val[next][j] = noa_p[now].val[j][0] * f[j][next];
					noa_p[tomorrow].val[next][0] += noa_p[tomorrow].val[next][j];
				}
			}

		}

#if 1
		/* print output */
		double a = 0.0;
		double b = 0.0;
		printf("ali: day %d\n", d+1);
		for (int j = 1; j <= N; ++j) {
			if (ali_p[tomorrow].val[j][0] > 0.0) {
				a += ali_p[tomorrow].val[j][0];
				printf(" City %d: [%.03f] ", j, ali_p[tomorrow].val[j][0]);
				for (int k = 1; k <= N; ++k) {
					printf("(%d, %.03f) ", k, ali_p[tomorrow].val[j][k]);
				}
				printf("\n");
			}
		}
//		if (a != 1.0) { printf("a--> %.03f\n", a); }

		printf("noa: day %d\n", d+1);
		for (int j = 1; j <= N; ++j) {
			if (noa_p[tomorrow].val[j][0] > 0.0) {
				b += noa_p[tomorrow].val[j][0];
				printf(" City %d: [%.03f] ", j, noa_p[tomorrow].val[j][0]);
				for (int k = 1; k <= N; ++k) {
					printf("(%d, %.03f) ", k, noa_p[tomorrow].val[j][k]);
				}
				printf("\n");
			}
		}
//		if (b != 1.0) { printf("b--> %.03f\n", b); }

#endif

		/* calculate meet_possibility */
		printf("day %d\n", d+1);
		for (int j = 1; j <= N; ++j) {
			if (ali_p[tomorrow].val[j][0] > 0.0 && noa_p[tomorrow].val[j][0] > 0.0) {
				for (int k = 1; k <= N; ++k) {
					double ap = ali_p[tomorrow].val[j][k];

					if (ap > 0.0) {
						for (int z = 1; z <= N; ++z) {
							if (z != k && noa_p[tomorrow].val[j][z] > 0.0) {
								printf("-- matched at %d : ali (%d) - noa (%d) = %.03f\n", j, k, z, ap * noa_p[tomorrow].val[j][z]);
								result_f += (ap * noa_p[tomorrow].val[j][z]);
							}
						}
					}
				}
			}
		}
	}

	return result_f;
}

struct path {
	int next;
	double p;
};

struct dailyProb {
	double p[MAX_N+1][MAX_N+1];
};

dailyProb ex[2];
vector<path> ali_path;
vector<path> noa_path;

double t5()
{
	/* matching possilbity */
	double result_f = 0.0;

	for (int j = 1; j <= N; ++j) {
		for (int k = 1; k <= N; ++k) {
			ex[1].p[j][k] = 0.0;
		}
	}

	ex[1].p[1][N] = 1.0;
	ex[1].p[1][0] = 1.0;
	ex[1].p[0][N] = 1.0;

	for (int d = 1; d < M; ++d) {
		int now = d % 2;
		int tomorrow = (d + 1) % 2;

		/* init tommorow */
		for (int j = 1; j <= N; ++j) {
			for (int k = 0; k <= N; ++k) {
				ex[tomorrow].p[j][k] = 0.0;
			}
		}

		/* find d++ day ; ali/noa travel city */
		for (int j = 1; j <= N; ++j) {
			for (int k = 1; k <= N; ++k) {
				if (ex[now].p[j][k] > 0.0) {
					/* ali: -> j */
					ali_path.clear();
					noa_path.clear();

					for (int z = 0; z < link[j].size(); ++z) {
						path ali;
						ali.next = link[j][z];
						ali.p = ex[now].p[j][k] * f[j][ali.next];
						printf("day %d: ali %d -> %d : %.03f\n", d+1, j, ali.next, ali.p);
						ali_path.push_back(ali);
					}

					/* noa: -> k */
					for (int z = 0; z < link[k].size(); ++z) {
						path noa;
						noa.next = link[k][z];
						noa.p = ex[now].p[j][k] * f[k][noa.next];
						printf("day %d: noa %d -> %d : %.03f\n", d+1, k, noa.next, noa.p);
						noa_path.push_back(noa);
					}

					for (int z1 = 0; z1 < ali_path.size(); ++z1) {
						path& ali = ali_path[z1];
						for (int z2 = 0; z2 < noa_path.size(); ++z2) {
							path& noa = noa_path[z2];

							if (ali.next == noa.next) {
								/* met !!! */
								printf("day %d: met (%d) -- (ali: %.03f, noa: %.03f) = %.03f\n", d+1, ali.next, ali.p, noa.p, ali.p * noa.p);
								result_f += ali.p * noa.p;
							} else {
								/* not met, go continue */
								printf("day %d: go continue -- (%d, %d, %.03f)\n", d+1, ali.next, noa.next, ali.p * noa.p);
								ex[tomorrow].p[ali.next][noa.next] = ali.p * noa.p;
							}
						}
					}
				}
			}
		}
	}

	return result_f;
}

int main()
{
	freopen("data\\match_travel2.txt", "r", stdin);
	freopen("result.txt", "w", stdout);
	scanf("%d\n", &CASE);

	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d %d\n", &N, &M, &K);

		for (int i = 0; i <= MAX_N; ++i) {
			for (int j = 0; j <= MAX_N; ++j)
				f[i][j] = 0.0;

			link[i].clear();
		}

#if 0
		for (int i = 0; i <= MAX_N; ++i)
			for (int j = 0; i <= MAX_N; ++i)
				for (int d = 0; d <= MAX_DAYS; ++d) {
					ali[i][j][d] = 0.0;
					noa[i][j][d] = 0.0;
			}
#endif

		for (int i = 0; i < K; ++i) {
			int n1, n2;
			double f0;

			scanf("%d %d %lf\n", &n1, &n2, &f0);

			if (f0 > 0.0) {
				f[n1][n2] = f0;
				link[n1].push_back(n2);
			}
		}

#if 0
		printf("possibility:\n");
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				printf("%.03f ", f[i][j]);
			}
			printf("\n");
		}
#endif

		//
		double result_f = t5();

		printf("#%d %.03lf\n", t, result_f);
	}

	return 0;
}
