//https://www.luogu.com.cn/problem/P3740
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100001
int rounds[maxn];
int poster[maxn << 2];
bool verify[maxn];

int ranking(int goal, int l, int r)
{
	int mid = (l + r) / 2;
	if (goal == rounds[mid]) return mid;
	if (goal < rounds[mid]) return ranking(goal, l, mid);
	if (goal > rounds[mid]) return ranking(goal, mid + 1, r);
}

void lazy(int i, int jobv)
{
	poster[i] = jobv;
}

void down(int i)
{
	if (poster[i] != 0)
	{
		lazy(i << 1, poster[i]);
		lazy(i << 1 | 1, poster[i]);//发左发右
		poster[i] = 0;//父节点懒信息清空
	}
}

void update(int jobl, int jobr, int jobv, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//如果目标范围完全覆盖当前范围
	{
		lazy(i, jobv);
		return;
	}
	int mid = (l + r) / 2;
	down(i);
	if (jobl <= mid)//左节点在目标范围中
	{
		update(jobl, jobr, jobv, l, mid, i << 1);
	}
	if (jobr > mid)//右节点在目标范围中
	{
		update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
	}
}

void build(int l, int r, int i)
{
	poster[i] = 0;
	if (l == r)
	{
		return;
	}
	else
	{
		int mid = (l + r) >> 1;
		build(l, mid, i << 1);
		build(mid + 1, r, i << 1 | 1);
	}
}


int query(int l, int r, int i)
{
	if (l == r)
	{
		if (poster[i] == 0) return 0;
		if (verify[poster[i]])return 0;
		verify[poster[i]] = true;
		return 1;
	}
	int mid = (l + r) >> 1;
	int ans = 0;
	down(i);
	ans += query(l, mid, i << 1);
	ans += query(mid + 1, r, i << 1 | 1);
	return ans;
}

int main()
{
	int n, m, templ, tempr;
	cin >> n >> m;
	int* pos = new int[m * 4];
	for (int i = 1; i <= m; i++)
	{
		cin >> templ >> tempr;
		pos[i * 2 - 1] = templ;
		rounds[i * 2 - 1] = templ;
		pos[i * 2] = tempr;
		rounds[i * 2] = tempr;
		verify[i] = false;
	}


	int size = 2 * m;
	rounds[++size] = n;
	sort(rounds + 1, rounds + size + 1);
	int j = 1;
	for (int i = 2; i <= size; i++)
	{
		if (rounds[j] != rounds[i])
		{
			rounds[++j] = rounds[i];
		}
	}
	size = j;
	for (int i = 1; i < j; i++)
	{
		if (rounds[i + 1] - rounds[i] > 1)
		{
			rounds[++size] = rounds[i] + 1;
		}
	}
	sort(rounds + 1, rounds + size + 1);

	build(1, size, 1);
	for (int i = 1; i <= m; i++)
	{
		int l = pos[i * 2 - 1], r = pos[i * 2];
		if (l > n)continue;
		if (r > n) r = n;
		update(ranking(l, 1, size), ranking(r, 1, size), i, 1, size, 1);
	}
	cout << query(1, size, 1);
}