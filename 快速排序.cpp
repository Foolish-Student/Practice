//练习快速排序
#include<iostream>
using namespace std;
void quicksort(int*, int, int);
int main()
{
	int a[] = { 45,9984,21,45,326,4,86,47 };
	//测量出数组的长度
	int len = sizeof(a) / sizeof(int);
	//输出排序前的顺利
	cout << "排序前：";
	for (int i : a)
	{
		cout << i <<" ";
	}
	cout << endl;
	quicksort(a, 0, len - 1);
	cout << "排序后：";
	for (int i : a)
	{
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
void quicksort(int* a, int l, int r)
{
	//判断一下边界
	if (l < r)
	{
		//记录我们排序的第一个数字，并把左右边界记录下来
		int temp = a[l], left = l, right = r;
		while (left < right)
		{
			//从右往左搜索，找到比temp大的数字，并且左边界小于右边界
			while (left < right && a[right] >= temp)
				right--;
			//如果左边界小于右边界，就证明不是因为边界问题而退出的循环
			//是找到了比temp小的值，直接和第一个数字做交换，第一个数字已经记录下来了
			if (left < right)
				a[left++] = a[right];//left向右移动
			//同理
			while (left < right && a[left] < temp)
				left++;
			if (left < right)
				a[right--] = a[left];
		}
		//循环结束了left的位置就是最开始最左边数字的位置，直接赋值
		a[left] = temp;
		//递归，把左边的分成一个部分，右边的分成一个部分进行排序
		quicksort(a, l, left - 1);
		quicksort(a, left + 1, r);
	}
}
