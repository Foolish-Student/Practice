//自己写一个vector
//用来练习函数模板和运算符重载
#include<iostream>
#include<cstring>
using namespace std;
//定义一个模板，以免写过多的函数
template<typename T>
class Vector
{
private:
	//用来存储元素
	T* m_word;
	//用来记录元素个数
	int m_count;
	//用来记录内存
	int m_storage;
public:
	//三个构造函数用来初始化  一个带参两个不带参
	Vector();
	Vector(const int,const T&);
	Vector(const T&);
	//重载[]
	int& operator[](const int&);
	//重载=
	const Vector<T>& operator=(const Vector<T>&);
	//push_back,在末尾插入一个元素
	void push_back(const T&);
	//pop_back,返回并删除末尾的元素
	T pop_black();
	//流输出
	template<typename T1>
	friend ostream& operator<<(ostream&,const Vector<T1>&);
	//析构函数
	~Vector();
};
//实现构造函数的初始化
template<typename T>
Vector<T>::Vector()
{
	//分配16个字节
	this->m_storage = 16;
	//长度为0
	this->m_count = 0;
	//开辟内存
	this->m_word = new T[sizeof(T)*m_storage];
}
//带参构造
template<typename T>
Vector<T>::Vector(const int count,const T& temp):m_storage(16)
{
	//刷新数据
	this->m_count = count;
	this->m_storage = m_storage+count;
	//分配内存
	this->m_word = new T[m_storage];
	//开始赋值
	for (int i = 0; i < m_count; i++)
	{
		memcpy(&m_word[i], &temp, sizeof(T));
	}
}
//重载构造
template<typename T>
Vector<T>::Vector(const T& word)
{
	//判断是否自己赋值自己，word是否为空
	if (this == &word||&word==NULL)
	{
		//分配16个字节
		this->m_storage = 16;
		//长度为0
		this->m_count = 0;
		//开辟内存
		this->m_word = new T[m_storage];
	}
	else
	{
		//释放内存
		delete[] this->m_word;
		//刷新数据
		this->m_storage = word.m_storage;
		this->m_count = word.m_count;
		memccpy(this->m_word, word.m_word);
	}
}
//重载[]
template <typename T>
int& Vector<T>::operator[](const int& temp)
{
	//判断数组角标是否越界，越界 给出警告提示
	if (temp < this->m_storage && temp >= 0)
	{
		return this->m_word[temp];
	}
	else
	{
		cerr << "数组角标越界" << endl;
	}
}
//重载=
template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& temp)
{
	//判断是否相同
	if (this == &temp)
		return *this;
	//判断m_word是否有数据
	if (this->m_word != NULL)
	{
		//释放空间
		delete[] m_word;
		m_word = NULL;
	}
	//刷新数据
	this->m_count = temp.m_count;
	this->m_storage = temp.m_storage;
	//分配内存
	this->m_word = new T[m_storage];
	memcpy(this->m_word, temp.m_word, sizeof(T) * temp.m_count);
}
//实在在末尾插入一个元素
template<typename T>
void Vector<T>::push_back(const T& num)
{
	//先判断数组是否为空
	if (this->m_word == NULL)
	{
		//赋初值,分配内存
		this->m_storage = 16;
		this->m_count = 0;
		this->m_word = new T[m_storage];
	}
	//判断数组是否已满
	if (this->m_count == this->m_storage)
	{
		//扩容
		this->m_storage = this->m_storage * 2 + 1;
		T* newword = new T[m_storage];
		memcpy(newword, this->m_word, sizeof(T) * this->m_count);
		delete[] this->m_word;
		this->m_word = newword;
	}
	//赋值
	m_word[m_count++] = num;
}
//实现返回并删除末尾的元素
template<typename T>
T Vector<T>::pop_black()
{
	//记录最后一个数
	int temp = this->m_word[m_count - 1];
	//如果数组只有一个元素直接赋值空
	if (this->m_count == 1)
	{
		delete[] this->m_word;
		this->m_word = NULL;
		this->m_count = 0;
		return temp;
	}
	//如果数组没有元素给出警告
	if (this->m_word == NULL)
	{
		cerr << "数据错误" << endl;
	}
	//刷新数据
	this->m_count--;
	this->m_storage--;
	
	//重新分配空间
	T* newword = new T[m_storage];
	//复制并释放内存
	memcpy(newword, this->m_word, sizeof(T) * this->m_count);
	delete[] this->m_word;
	this->m_word = newword;
	return temp;
}
//流输出 重载<<
template<typename T>
ostream& operator<<(ostream& out, const Vector<T>& num)
{
	//循环输出
	for (int i = 0; i < num.m_count; i++)
	{
		out << num.m_word[i] << ",";
	}
	out << endl;
	return out;
}
//析构函数用来释放内存
template<typename T>
Vector<T>::~Vector()
{
	delete[] this->m_word;
}
int main()
{
	//以下为测试数据
	Vector<int> vec(20,1);
	Vector<double> vec1(1, 5.1);
	vec.push_back(20);
	vec.pop_black();
	cout << vec << endl;
	cout << vec1 << endl;
	return 0;
}