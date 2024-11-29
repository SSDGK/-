#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Prim
{
	int head[500001];
	int next[500001];
	int to[500001];
	int weight[500001];
	int cnt;


	int where[5001];//i号点在heap中的where[i]位置,-1表示还未进过堆，-2表示已经弹出过
	pair<int, int> heap[5001];
	int heapSize;

	int tv;
	long long tw;
	int nodeCnt;

	void build(int n, int m)
	{
		for (int i = 1; i <= n; i++)
		{
			where[i] = -1;
		}
		for (int i = 0; i <= 2 * m; i++)
		{
			head[i] = next[i] = to[i] = weight[i] = 0;
		}
		heapSize = 0;
		cnt = 1;
		nodeCnt = 0;
	}
	void addLine(int a, int b, int w)
	{
		next[cnt] = head[a];
		to[cnt] = b;
		weight[cnt] = w;
		head[a] = cnt++;
	}
	void swapc(int i, int j)
	{
		if (i == j)return;
		int a = heap[i].first;
		int b = heap[j].first;
		where[a] = j;
		where[b] = i;
		auto tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}
	void heapify(int i)//向下调整
	{
		int l = i * 2 + 1;
		while (l < heapSize)
		{
			int minn = l + 1 == heapSize ? l : (heap[l].second < heap[l + 1].second ? l : l + 1);
			minn = heap[i].second < heap[minn].second ? i : minn;
			if (minn == i)break;
			swapc(i, minn);
			i = minn;
			l = i * 2 + 1;
		}
	}
	void heapInsert(int i)//向上调整
	{
		int fa = (i - 1) / 2;
		while (heap[fa].second > heap[i].second)
		{
			swapc(fa, i);
			i = fa;
			fa = (i - 1) / 2;
		}
	}
	void pop()
	{
		tv = heap[0].first;
		tw = heap[0].second;
		swapc(0, --heapSize);
		heapify(0);
		where[tv] = -2;
		nodeCnt++;
	}

	void addOr(int ei)
	{
		int v = to[ei];
		int w = weight[ei];
		if (where[v] == -1)
		{
			heap[heapSize] = { v,w };
			where[v] = heapSize++;
			heapInsert(where[v]);
		}
		else if (where[v] >= 0)
		{
			if (w < heap[where[v]].second)
			{
				heap[where[v]].second = w;
				heapInsert(where[v]);
			}
		}
	}

public:
	long long MST(int n, int m, vector<vector<int>>& lines)
	{
		build(n, m);
		for (auto& line : lines)
		{
			addLine(line[0], line[1], line[2]);
			addLine(line[1], line[0], line[2]);
		}
		where[1] = -2;
		nodeCnt = 1;
		for (int i = head[1]; i > 0; i = next[i])
		{
			addOr(i);
		}
		long long ans = 0;
		while (heapSize > 0)
		{
			pop();
			ans += tw;
			for (int i = head[tv]; i > 0; i = next[i])
			{
				addOr(i);
			}
		}
		return nodeCnt == n ? ans : -1;
	}
};

vector<vector<int>> relations;
int main()
{
	int n, m;
	cin >> n >> m;
	relations.resize(m);
	int x, y, k;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> k;
		relations[i] = { x,y,k };
	}
	long long ans;
	auto solution = new Prim;
	ans = solution->MST(n, m, relations);
	if (ans == -1)cout << "orz";
	else cout << ans;
}