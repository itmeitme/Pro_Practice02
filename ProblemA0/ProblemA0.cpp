#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

#define MAX 5000

typedef struct pos
{
	int x;
	int y;
	int cost;
}pos;

bool operator>(pos d1, pos d2);
pos out();
int cal_cost(int*map, int*cost, int row, int col, pos s, pos e);

int dir[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };
priority_queue<pos, vector<pos>, greater<pos>> que;


int main(void)
{
	int row, col, num;
	scanf("%d %d", &row, &col);

	int* map = new int[row*col];
	int* cost = new int[row*col];
	for (int r = 0; r < row; r++)
		for (int c = 0; c < col; c++)
			scanf("%d", &map[r*col + c]);
	
	cin >> num;
	pos* arr = new pos[num + 1];
	arr[0].x = 0, arr[0].y = 0;
	for (int i = 1; i <= num; i++)
	{
		scanf("%d %d", &arr[i].y, &arr[i].x);
		arr[i].y -= 1;
		arr[i].x -= 1;
	}

	int sum = 0;
	int tmp = 0;

	int t = 0;
	for (int i = 1; i <= num; i++)
		sum += cal_cost(map, cost, row, col, arr[i - 1], arr[i]);
	sum += map[0];

	printf("%d\n",sum);

	delete[] map;
	delete[] cost;
	delete[] arr;

	return 0;
}


bool operator>(pos d1, pos d2)
{
	return d1.cost > d2.cost;
}


pos out()
{
	pos tmp = que.top();
	que.pop();
	return tmp;
}

int cal_cost(int*map, int*cost, int row, int col, pos s, pos e)
{
	memset(cost, -1, sizeof(int)*row*col);
	cost[s.y*col + s.x] = 0;

	pos tmp = { s.x, s.y, 0 };
	que.push(tmp);

	while (!que.empty())
	{
		pos cur = out();
		if (cur.x == e.x && cur.y == e.y)
			break;

		int x = cur.x, y = cur.y;
		int nx = 0, ny = 0;

		for (int i = 0; i < 4; i++)
		{
			if (i == 1 || i == 3)
				if (x > 0 && x < col - 1)
					continue;
			nx = x + dir[i][0];
			ny = y + dir[i][1];

			if (nx >= 0 && nx < col && ny >= 0 && ny < row)
				if (cost[ny*col + nx] == -1 || cost[y*col + x] + map[ny*col + nx] < cost[ny*col + nx])
				{
					if (cost[ny*col + nx] > MAX)
						continue;
					cost[ny*col + nx] = cost[y*col + x] + map[ny*col + nx];
					pos tmp = { nx,ny,cost[ny*col + nx] };
					que.push(tmp);
				}
				else
					continue;
			else
				continue;
		}
	}
	while (que.size())
		que.pop();

	return cost[e.y*col + e.x];
}