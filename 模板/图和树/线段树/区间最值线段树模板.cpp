#include <iostream>
#include <climits>
using namespace std;

#define maxn 1000001
long long LOWEST = LLONG_MIN;
int arr[maxn];
long long sum[maxn << 2];
long long maxnum[maxn << 2];
long long semaxn[maxn << 2];
int maxcnt[maxn << 2];

long long maxadd[maxn << 2];
long long otheradd[maxn << 2];

long long maxHistory[maxn << 2];
long long maxaddTop[maxn << 2];// 最大值达到过的最大提升幅度(懒更新信息)
long long otheraddTop[maxn << 2];// 除最大值以外的其他数字，达到过的最大提升幅度(懒更新信息)

int ope[maxn][4];


// maxAddv   : 最大值增加多少
// otherAddv : 其他数增加多少
// maxUpv    : 最大值达到过的最大提升幅度
// otherUpv  : 其他数达到过的最大提升幅度

void lazy(int i, int size, long long maxAddv, long long otherAddv, long long maxUpv, long long otherUpv) {
	maxHistory[i] = max(maxHistory[i], maxnum[i] + maxUpv);
	maxaddTop[i] = max(maxaddTop[i], maxadd[i] + maxUpv);
	otheraddTop[i] = max(otheraddTop[i], otheradd[i] + otherUpv);

	sum[i] += maxAddv * maxcnt[i] + otherAddv * (size - maxcnt[i]);
	maxnum[i] += maxAddv;
	semaxn[i] += semaxn[i] == LOWEST ? 0 : otherAddv;

	maxadd[i] += maxAddv;
	otheradd[i] += otherAddv;
}

void up(int i)
{
	int l = i << 1;
	int r = i << 1 | 1;
	sum[i] = sum[l] + sum[r];
	maxnum[i] = max(maxnum[l], maxnum[r]);
	if (maxnum[l] > maxnum[r])
	{
		semaxn[i] = max(maxnum[r], semaxn[l]);
		maxcnt[i] = maxcnt[l];
	}
	else if (maxnum[l] < maxnum[r])
	{
		semaxn[i] = max(maxnum[l], semaxn[r]);
		maxcnt[i] = maxcnt[r];
	}
	else
	{
		semaxn[i] = max(semaxn[l], semaxn[r]);
		maxcnt[i] = maxcnt[l] + maxcnt[r];
	}
	maxHistory[i] = max(maxHistory[l], maxHistory[r]);
}

void down(int i, int ln, int rn)
{
	int l = i << 1;
	int r = i << 1 | 1;
	long long tmp = max(maxnum[l], maxnum[r]);

	if (maxnum[l] == tmp)
	{
		lazy(l, ln, maxadd[i], otheradd[i], maxaddTop[i], otheraddTop[i]);
	}
	else
	{
		lazy(l, ln, otheradd[i], otheradd[i], otheraddTop[i], otheraddTop[i]);
	}

	if (maxnum[r] == tmp)
	{
		lazy(r, rn, maxadd[i], otheradd[i], maxaddTop[i], otheraddTop[i]);
	}
	else
	{
		lazy(r, rn, otheradd[i], otheradd[i], otheraddTop[i], otheraddTop[i]);
	}
	maxadd[i] = otheradd[i] = maxaddTop[i] = otheraddTop[i] = 0;
}

void setMin(int jobl, int jobr, long jobv, int l, int r, int i) {
	if (jobv >= maxnum[i]) {
		return;
	}
	if (jobl <= l && r <= jobr && semaxn[i] < jobv) {
		lazy(i, r - l + 1, jobv - maxnum[i], 0, jobv - maxnum[i], 0);
	}
	else {
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);
		if (jobl <= mid) {
			setMin(jobl, jobr, jobv, l, mid, i << 1);
		}
		if (jobr > mid) {
			setMin(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
		}
		up(i);
	}
}

void addnum(int jobl, int jobr, long long jobv, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//如果目标范围完全覆盖当前范围
	{
		lazy(i, r - l + 1, jobv, jobv, jobv, jobv);
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

long long querySum(int jobl, int jobr, int l, int r, int i)
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
		ans += querySum(jobl, jobr, l, mid, i << 1);
	}
	if (jobr > mid)//右节点在目标范围中
	{
		ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
	}
	return ans;
}

long long queryMax(int jobl, int jobr, int l, int r, int i) {
	if (jobl <= l && r <= jobr) {
		return maxnum[i];
	}
	else {
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);
		long long ans = LLONG_MIN;
		if (jobl <= mid) {
			ans = max(ans, queryMax(jobl, jobr, l, mid, i << 1));
		}
		if (jobr > mid) {
			ans = max(ans, queryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
		}
		return ans;
	}
}

long long queryHistoryMax(int jobl, int jobr, int l, int r, int i) {
	if (jobl <= l && r <= jobr) {
		return maxHistory[i];
	}
	else {
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);
		long long ans = LLONG_MIN;
		if (jobl <= mid) {
			ans = max(ans, queryHistoryMax(jobl, jobr, l, mid, i << 1));
		}
		if (jobr > mid) {
			ans = max(ans, queryHistoryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
		}
		return ans;
	}
}

void build(int l, int r, int i)
{
	if (l == r)
	{
		sum[i] = arr[l];
		maxnum[i] = arr[l];
		maxHistory[i] = arr[l];
		semaxn[i] = LOWEST;
		maxcnt[i] = 1;
	}
	else
	{
		int mid = (l + r) >> 1;
		build(l, mid, i << 1);
		build(mid + 1, r, i << 1 | 1);
		up(i);
	}
	maxadd[i] = otheradd[i] = maxaddTop[i] = otheraddTop[i] = 0;
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
		if (temp == 1 || temp == 2)
		{
			for (int j = 1; j < 4; j++)
			{
				cin >> ope[i][j];
			}
		}
		else if (temp == 3 || temp == 4 || temp == 5)
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
			setMin(ope[i][1], ope[i][2], ope[i][3], 1, n, 1);
		}
		else if (temp == 3)
		{
			cout << querySum(ope[i][1], ope[i][2], 1, n, 1) << endl;
		}
		else if (temp == 4)
		{
			cout << queryMax(ope[i][1], ope[i][2], 1, n, 1) << endl;
		}
		else if (temp == 5)
		{
			cout << queryHistoryMax(ope[i][1], ope[i][2], 1, n, 1) << endl;
		}
		else
		{
			cout << "ERROR";
			return 0;
		}
	}
}