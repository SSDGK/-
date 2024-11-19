#include <iostream>
using namespace std;
#define maxn 100000
int cnt;
int leftNode[maxn];
int rightNode[maxn];
long long sum[maxn];
long long add[maxn];
int ope[maxn][4];

void lazy(int i, long long jobv, int size)
{
	sum[i] += jobv * size;
	add[i] += jobv;
}

void up(int i)
{
	sum[i] = sum[leftNode[i]] + sum[rightNode[i]];
}

void down(int i, int ln, int rn)
{
	if (add[i] != 0)
	{
		if (leftNode[i] == 0)
		{
			leftNode[i] = ++cnt;
		}
		lazy(leftNode[i], add[i], ln);
		if (rightNode[i] == 0)
		{
			rightNode[i] = ++cnt;
		}
		lazy(rightNode[i], add[i], rn);//������
		add[i] = 0;//���ڵ�����Ϣ���
	}
}

void addnum(int jobl, int jobr, long long jobv, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//���Ŀ�귶Χ��ȫ���ǵ�ǰ��Χ
	{
		lazy(i, jobv, r - l + 1);
	}
	else
	{
		int mid = (l + r) >> 1;
		down(i, mid - l + 1, r - mid);//����Ϣ���´���
		if (jobl <= mid)//������Ŀ�귶Χ��
		{
			if (leftNode[i] == 0)
			{
				leftNode[i] = ++cnt;
			}
			addnum(jobl, jobr, jobv, l, mid, leftNode[i]);
		}
		if (jobr > mid)//�ҽڵ���Ŀ�귶Χ��
		{
			if (rightNode[i] == 0)
			{
				rightNode[i] = ++cnt;
			}
			addnum(jobl, jobr, jobv, mid + 1, r, rightNode[i]);
		}
		up(i);
	}
}

long long query(int jobl, int jobr, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//���Ŀ�귶Χ��ȫ���ǵ�ǰ��Χ
	{
		if (sum[i] < 0)return 0;
		return sum[i];
	}
	int mid = (l + r) >> 1;
	down(i, mid - l + 1, r - mid);//����Ϣ���´���
	long long ans = 0;
	if (jobl <= mid)//��ڵ���Ŀ�귶Χ��
	{
		if (leftNode[i] != 0)
			ans += query(jobl, jobr, l, mid, leftNode[i]);
	}
	if (jobr > mid)//�ҽڵ���Ŀ�귶Χ��
	{
		if (rightNode[i] != 0)
			ans += query(jobl, jobr, mid + 1, r, rightNode[i]);
	}
	return ans;
}

int main()
{
	int n, m, temp;
	cin >> n >> m;
	cnt = 1;
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
