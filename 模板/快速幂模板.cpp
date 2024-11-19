#include <iostream>
#include <vector>
using namespace std;

long long qpow(int ta, int b)
{
	long long ans = 1, a = ta;
	while (b)
	{
		if (b & 1) ans *= a;
		b >>= 1;
		a = a * a;
	}
	return ans;
}
int main()
{
	int a, b;
	cin >> a >> b;
	cout << qpow(a, b) << endl << pow(a, b);
}