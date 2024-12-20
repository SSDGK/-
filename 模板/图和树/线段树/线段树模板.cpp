#include <iostream>
using namespace std;
#define maxn 1000001
long long arr[maxn];
long long sum[maxn << 2];
long long add[maxn << 2];
int ope[maxn][4];

void lazy(int i, long long jobv, int size)
{
	sum[i] += jobv * size;
	add[i] += jobv;
}

void up(int i)
{
	sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void down(int i, int ln, int rn)
{
	if (add[i] != 0)
	{
		lazy(i << 1, add[i], ln);
		lazy(i << 1 | 1, add[i], rn);//发左发右
		add[i] = 0;//父节点懒信息清空
	}

}

void build(int l, int r, int i)
{
	if (l == r)sum[i] = arr[l];
	else
	{
		int mid = (l + r) >> 1;
		build(l, mid, i << 1);
		build(mid + 1, r, i << 1 | 1);
		up(i);
	}
	add[i] = 0;
}

void addnum(int jobl, int jobr, long long jobv, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//如果目标范围完全覆盖当前范围
	{
		lazy(i, jobv, r - l + 1);
	}
	else
	{
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);//懒信息向下传递
		if (jobl <= mid)//左结点在目标范围中
		{
			addnum(jobl, jobr, jobv, l, mid, i << 1);
		}
		if (jobr > mid)//右节点在目标范围中
		{
			addnum(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
		}
		up(i);
	}
}

long long query(int jobl, int jobr, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//如果目标范围完全覆盖当前范围
	{
		return sum[i];
	}
	int mid = (l + r) >> 1;
	down(i, mid - l + 1, r - mid);//懒信息向下传递
	long long ans = 0;
	if (jobl <= mid)//左节点在目标范围中
	{
		ans += query(jobl, jobr, l, mid, i << 1);
	}
	if (jobr > mid)//右节点在目标范围中
	{
		ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
	}
	return ans;
}

int main()
{
	int n, m, temp;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)cin >> arr[i];
	for (int i = 0; i < m; i++)
	{
		cin >> temp;
		ope[i][0] = temp;
		if (temp == 1)
		{
			for (int j = 1; j < 4; j++)
			{
				cin >> ope[i][j];
			}
		}
		else if (temp == 2)
		{
			for (int j = 1; j < 3; j++)
			{
				cin >> ope[i][j];
			}
		}
		else
		{
			cout << "ERROR";
			return 0;
		}
	}
	build(1, n, 1);
	for (int i = 0; i < m; i++)
	{
		temp = ope[i][0];
		if (temp == 1)
		{
			addnum(ope[i][1], ope[i][2], ope[i][3], 1, n, 1);
		}
		else if (temp == 2)
		{
			cout << query(ope[i][1], ope[i][2], 1, n, 1) << endl;
		}
		else
		{
			cout << "ERROR";
			return 0;
		}
	}
}
