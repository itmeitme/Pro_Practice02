#include <iostream>
using namespace std;

typedef struct boat
{
	int cap;
	bool visit;
};

int upper_bound(int* arr, int N, int val)
{
	int s = 0;
	int e = N - 1;
	int m;

	while (s >= e)
	{
		m = (s + e) / 2;
		if (arr[m] <= val)
			s = m + 1;
		else
			e = m;
	}
	return e + 1;
}

int boarding(boat &b, int* arr, int N, int eidx)
{
	if (b.visit == true)
		return -1;
	else
	{
		b.visit = true;
		return upper_bound(arr, N, arr[eidx] + b.cap) - 1;
	}
}


int main()
{
	int B, N;
	cin >> B >> N;

	boat* barr = new boat[B];
	int* arr = new int[N];

	for (int i = 0; i < B; i++)
	{
		cin >> barr[i].cap;
		barr[i].visit = false;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
		if (i > 0)
			arr[i] += arr[i - 1];
	}




	
	return 0;
}

