#include <iostream>
#include <algorithm>
using namespace std;

void SortSolution(int* arr, int n)
{
	int cnt[10];
	int temp[1000];
	int offset = 1;
	while (true)
	{
		fill(cnt, cnt + 10, 0);
		for (int i = 0; i < n; i++)
		{
			cnt[(arr[i] / offset) % 10]++;
		}
		for (int i = 1; i < 10; i++)
		{
			cnt[i] = cnt[i] + cnt[i - 1];
		}
		if (cnt[0] == n) break;
		for (int i = n - 1; i >= 0; i--)
		{
			temp[--cnt[(arr[i] / offset) % 10]] = arr[i];
		}
		for (int i = 0; i < n; i++)
		{
			cout << temp[i];
			if (i != n - 1)cout << " ";
			arr[i] = temp[i];
		}
		cout << endl;
		offset *= 10;
	}
}

int main()
{
	int n, num;
	int arr[1000];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> num;
		arr[i] = num;
	}
	SortSolution(arr, n);
}