/*斐波那契数列dp*/

#include<iostream>
#include<algorithm>
using namespace std;
int num[100000];
int main()
{
	num[0] = 0;
	num[1] = 1;
	int n;
	cin >> n;
	for (int i = 2; i < n; i++) {
		num[i] = num[i - 2] + num[i - 1];
	}
	cout << num[n - 1];
	return 0;
}



/*斐波那契数列普通递归*/

#include<iostream>
#include<algorithm>
using namespace std;
int fac(int num) {
	if (num == 1||num == 2) {
		return 1;
	}
	if (num > 2) {
		return fac(num - 1) + fac(num - 2);
	}
	return 0;
}
int main()
{
	int n;
	cin >> n;
	cout << fac(n);
	return 0;
};



/*斐波那契数列记忆优化递归*/
#include<iostream>
#include<algorithm>
using namespace std;
int a[10000];
int fac(int num) {
	if (num == 1 || num == 2) {
		a[num] = 1;
		return 1;
	}
	if (a[num]) {
		return a[num];
	}
	a[num] = fac(num - 1) + fac(num - 2);
	return a[num];
}
int main() 
{
	int n;
	cin >> n;
	cout << fac(n);
}