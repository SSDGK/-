#include <iostream>
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

int read()
{
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch>'9')
	{
		if (ch == '-')w = -1;
		ch = getchar();
	}

	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + (ch - '0');
		ch = getchar();
	}
	return x * w;
}

void write(int x)
{
	if (x < 0)
	{
		x = -x;
		putchar('-');
	}
	static int sta[35];
	int top = 0;
	do
	{
		sta[top++] = x % 10;
		x /= 10;
	} while (x);
	
	while (top)
	{
		putchar(sta[--top] + 48);
	}
}
