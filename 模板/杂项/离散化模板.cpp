#include <iostream>
using namespace std;
int arr[maxn];
int frontier[maxn];

int ranking(int goal, int l, int r)
{
	if (l == r)return l;
	int mid = (l + r) / 2;
	if (goal <= frontier[mid])
	{
		return ranking(goal, l, mid);
	}
	else
	{
		return ranking(goal, mid + 1, r);
	}
}

int main()
{
	int n, ans = 0, temp;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		frontier[i] = arr[i];
	}
	sort(frontier + 1, frontier + n + 1);
	int size = 1;
	for (int i = 1; i <= n; i++)
	{
		if (frontier[size] == frontier[i])continue;
		else
		{
			frontier[++size] = frontier[i];
		}
	}
}