#include <iostream>
using namespace std;

int temp[1000];

void SortSolution(int* arr, int n, int m)
{
	int i = 0;
	int a = 0;
	int b = n;
	while (a < n && b < n + m)
	{
		temp[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
	}
	while (a < n)
	{
		temp[i++] = arr[a++];
	}
	while (b < n + m)
	{
		temp[i++] = arr[b++];
	}
	for (int j = 0; j < n + m; j++)
	{
		arr[j] = temp[j];
		cout << arr[j];
		if (j != n + m - 1) cout << " ";
	}
}

int main()
{
	int n, m, num;
	int arr[1000];
	cin >> n >> m;
	for (int i = 0; i < n + m; i++)
	{
		cin >> num;
		arr[i] = num;
	}
	SortSolution(arr, n, m);
}