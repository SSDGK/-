#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

#define maxn 50
int indexcnt = 0;
int maxi = 0;
string pretree;
string midtree;
int n;
char tree[maxn << 2];

void gettree(int i, int lp, int rp, int lm, int rm)
{
	if (indexcnt >= n || lp > rp || lm > rm)return;
	indexcnt++;
	maxi = max(maxi, i);
	char cur = pretree[lp];
	tree[i] = cur;
	int loc = midtree.find(cur);
	int leftsize = loc - lm;
	gettree(i << 1, lp + 1, lp + leftsize, lm, loc - 1);
	gettree(i << 1 | 1, lp + leftsize + 1, rp, loc + 1, rm);
}

void PrintTree()
{
	queue<int> nodeq;
	nodeq.push(1);
	while (!nodeq.empty())
	{
		int i = nodeq.front();
		nodeq.pop();
		cout << tree[i];
		if (tree[i << 1] != 0)
		{
			nodeq.push(i << 1);
		}
		if (tree[i << 1 | 1] != 0)
		{
			nodeq.push(i << 1 | 1);
		}
	}
}

int max2(int x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return (x + 1) >> 1;
}


int main()
{
	cin >> n;
	cin >> pretree >> midtree;
	gettree(1, 0, n - 1, 0, n - 1);
	int size = 0;
	int mm = max2(maxi);
	while (mm)
	{
		mm >>= 1;
		size++;
	}
	cout << size;
}
