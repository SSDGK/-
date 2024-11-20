#include <iostream>
using namespace std;

void josephus(int n, int k)
{
	int kids[10000];
	kids[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		kids[i] = 1;
	}
	int i = 1;
	int step = 1;
	int count = 0;
	while (true)
	{
		if (!kids[i])
		{
			i++;
		}
		else if (step == k)
		{
			count++;
			kids[i] = 0;
			cout << i;
			if (count != n)cout << "->";
			step = 1;
		}
		else
		{
			step++;
			i++;
		}

		if (count == n) break;
		if (i == n + 1) i = 0;
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	josephus(n, k);
}