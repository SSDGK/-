#include <iostream>
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int nextArr[1000001];
int n, m;
void buildNext(string s)
{
	if (m == 1)
	{
		nextArr[0] = -1;
		return;
	}
	nextArr[0] = -1;
	nextArr[1] = 0;
	int cn = 0, i = 2;
	while (i <= m)
	{
		if (s[i - 1] == s[cn])
		{
			nextArr[i++] = ++cn;
		}
		else if (cn > 0)
		{
			cn = nextArr[cn];
		}
		else
		{
			nextArr[i++] = 0;
		}
	}
}

void kmp(string s1, string s2)
{
	int i = 0;
	int j = 0;
	if (n == 0 || m == 0)return;
	while (i < n && j < m)
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else if (j > 0)
		{
			j = nextArr[j];
		}
		else
		{
			i++;
		}
		if (j == m)
		{
			cout << i - j + 1 << endl;
			j = nextArr[j];
		}
	}
}
int main()
{
	IOS;
	string s1, s2;
	cin >> s1 >> s2;
	n = s1.size();
	m = s2.size();
	buildNext(s2);
	kmp(s1, s2);
	for (int i = 1; i <= m; i++)
	{
		cout << nextArr[i] << ' ';
	}
}