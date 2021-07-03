/*
可以被重载的运算符包括所有C的运算符:
二元运算符      +(加)、-(减)、*(乘)、/(除)、%(取模);
逻辑运算符      ||(逻辑或)、&&(逻辑与)、!(逻辑非);
一元运算符      +(正)、-(负)、*(指针)、&(取地址)、++(自增)、--(自减);
位运算符        |(按位与)、&(按位或)、~(按位取反)、^(按位异或)、<<(左移)、>>(右移);
赋值运算符       =、+=、 -=、 *=、 /=、 %=、 &=、|=、 ^=、 <<=、 >>=;
内存声明与释放   new、delete、new[]、delete[];
其他运算符       ()(函数调用)、->(成员访问)、->*(成员指针访问)、,(逗号)、[](下标);
*/
#include<iostream>
using namespace std;
using std::ostream;
class heavy
{
private:
	//存储一个数字
	int m_num;
public:
	//构造函数默认值为0
	heavy():m_num(0){}
	//构造函数的赋值
	heavy(int num):m_num(num){}
	//成员函数重载+号
	//函数格式： 返回类型 + operator + 符号 (参数类型)
	//参数=操作数-1
	const heavy operator+(const heavy& num)
	{
		//两个参数相加，返回新的对象
		heavy temp = (this->m_num + num.m_num);
		return temp;
	}
	//友元函数重载-号
	//函数格式： friend + 返回类型 + 符号 （参数类型）
	//参数=操作数
	friend const heavy operator-(const heavy&, const heavy&);
	//流重载<<号
	friend  ostream& operator <<(ostream& out, heavy& temp)
	{
		out << temp.m_num;
		return out;
	}
	//用来输出m_num来判断函数重载是否成功
	void show()
	{
		cout << m_num;
	}
	//析构函数
	~heavy() {};
};
//为了区分代码 我把友元函数重载的实现写到了外面
const heavy operator-(const heavy& num1, const heavy& num2)
{
	//两个参数相减，返回新的对象
	heavy temp = (num1.m_num - num2.m_num);
	return temp;
}
int main()
{
	//定义三个数，来测试写的函数
	heavy int1(1024);
	heavy int2(2048);
	heavy int3;
	//成员函数重载实现原理：int3=int1.operator+(int2)   int2可以改成常量
	int3 = int1 + int2;
	cout <<"成员函数重载+号"<<endl<< "int3 = int1 + int2 =";
	//输出
	int3.show();
	cout << endl << "***************************" << endl;
	//友元函数重载实现原理：int3 = int1.m_num - int2.m_num
	int3 = int1 - int2;
	cout << "友元函数重载-号"<<endl<<"int3 = int1 - int2 =";
	int3.show();
	cout << endl << "***************************" << endl;
	int3 = int1 + 1024;
	cout << "流重载<<号"<<endl<<"int3 = int1 + 1024 =";
	cout << int3;
	return 0;
}
/*
运算符声明成类成员还是声明独立友元函数建议准则:
1.C+ +规定，赋值运算符=、数组下标运算符[]、函数调用运算符()、成员访问运算符->在重载时必须声明为类的成员函数.
2.流运算符<<、>>.类型转换运算符不能定义为类的成员函数，只能是友元函数.
3.一元运算符和复合赋值运算符重载时，一般声明类的成员函数.
4.二元运算符在运算符重载时，一般声明为友元函数.
注意：
1.对于很多运算符重载来说，可以选择使用成员函数或非成员函数来实现运算符重载，一般来说，非成员函数应该是友元函数，这样才能直接访问私有数据.
2.在定义运算符是，必须选择其中的一种格式，而不能同时选择这两种格式，同时定义这两种格式将被视为二义性错误，导致编译错误.
3.那么哪种格式最好呢？对于某些运算符来说，成员函数是唯一合法的解释，在其他情况下，这两种格式没有太大的区别.有时，根据类的设计，使用非成员函数可能更好（尤其是为类定义转换时）.
*/
