#include <iostream>
#include <vector>
using namespace std;

void sortSolution(vector<int>& nums, int l, int r)
{
	if (l >= r)return;
	srand(time(0));
	int goal = nums[rand() % (r - l + 1) + l];
	int a = l, b = r, i = l;
	while (i <= b)
	{
		if (nums[i] > goal)
		{
			swap(nums[i], nums[b--]);
		}
		else if (nums[i] == goal)
		{
			i++;
		}
		else
		{
			swap(nums[i++], nums[a++]);
		}
	}
	sortSolution(nums, l, a - 1);
	sortSolution(nums, b + 1, r);
}
vector<int> sortArray(vector<int>& nums)
{
	sortSolution(nums, 0, nums.size() - 1);
	return nums;
}

int main()
{
	int n, temp;
	vector<int> nums;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		nums.push_back(temp);
	}
	sortArray(nums);
	for (int i = 0; i < n; i++)
	{
		cout << nums[i] << ' ';
	}
}