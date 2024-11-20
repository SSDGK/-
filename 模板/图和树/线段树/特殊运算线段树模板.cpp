#include <iostream>
using namespace std;
#define maxn 200000
int arr[maxn];
int sum[maxn << 2];
int add[maxn << 2];
int ope[maxn][4];

#define Emp 3
int newPlus(int a, int b)
{
	int ai = max(a, b);
	int bi = min(a, b);
	if (ai == 0)
	{
		return 1;
	}
	else if (ai == 1)
	{
		switch (bi)
		{
		case 0:return 2; break;
		case 1:return 3; break;
		}
	}
	else if (ai == 2)
	{
		switch (bi)
		{
		case 0:return 3; break;
		case 1:return 0; break;
		case 2:return 1; break;
		}
	}
	else if (ai == 3)
	{
		return bi;//3��������ִ�����㶼�������������
	}
	return Emp;
}

void lazy(int i, int jobv, int size)
{
	int j = size % 4;
	while (j--)
	{
		sum[i] = newPlus(sum[i], jobv);
	};
	add[i] = newPlus(jobv, add[i]);
}

void up(int i)
{
	sum[i] = newPlus(sum[i << 1], sum[i << 1 | 1]);
}

void down(int i, int ln, int rn)
{
	if (add[i] != Emp)
	{
		lazy(i << 1, add[i], ln);
		lazy(i << 1 | 1, add[i], rn);//������
		add[i] = Emp;//���ڵ�����Ϣ���
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
	add[i] = Emp;
}

void addnum(int jobl, int jobr, int jobv, int l, int r, int i)
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
			addnum(jobl, jobr, jobv, l, mid, i << 1);
		}
		if (jobr > mid)//�ҽڵ���Ŀ�귶Χ��
		{
			addnum(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
		}
		up(i);
	}
}

int query(int jobl, int jobr, int l, int r, int i)
{
	if (l >= jobl && r <= jobr)//���Ŀ�귶Χ��ȫ���ǵ�ǰ��Χ
	{
		return sum[i];
	}
	int mid = (l + r) >> 1;
	down(i, mid - l + 1, r - mid);//����Ϣ���´���
	int ans = Emp;
	if (jobl <= mid)//������Ŀ�귶Χ��
	{
		ans = newPlus(ans, query(jobl, jobr, l, mid, i << 1));
	}
	if (jobr > mid)//�ҽڵ���Ŀ�귶Χ��
	{
		ans = newPlus(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
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
