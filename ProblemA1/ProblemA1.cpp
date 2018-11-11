#include <stdio.h>
#define max(a,b) (a>b? a:b)
int B, N;

int boat[9] = { 0 };
int V[9];
int D[100001] = { 0 };
int sum[100001] = { 0 };
int max_val;

int DFS(int finish_index, int search_index) {
	int ret = 0;
	int flag = 0;
	if (finish_index >= N) {
		for (int i = 0; i < B; i++) {
			if (!V[i]) {
				ret += boat[i];
			}
		}
		return ret;
	}
	if (search_index >= N) {
		
		for (int i = 0; i < B; i++) {
			if (!V[i] && sum[search_index] - sum[finish_index] <= boat[i]) {
				V[i] = 1;
				ret = max(ret, DFS(search_index, search_index));
				V[i] = 0;
			}
		}
		return ret;
	}
	

	for (int i = 0; i < B; i++) {
		if (!V[i] && sum[search_index] - sum[finish_index] <= boat[i]) {
			flag = 1;
			V[i] = 1;
			ret = max(DFS(search_index, search_index+1), ret);
			V[i] = 0;
		}
	}
	if (flag) {
		ret = max(DFS(finish_index, search_index + 1), ret);
	}
	else {
		return 0;
	}
	return ret;
}

int main(void)
{
	scanf("%d %d", &B, &N);
	for (int i = 0; i < B; i++) {
		scanf("%d", &boat[i]);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &D[i]);
		sum[i] = sum[i - 1] + D[i];
	}
	printf("%d\n",DFS(0,1));

	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
