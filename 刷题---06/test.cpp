#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<list>
using namespace std;

//1**********************************和为S的两个数字
void FindTwoNum(int *a,int find,int length)
{
	assert(a);
	assert(length > 0);

	int num1 = 0;
	int num2 = length-1;

	while(num2 > num1)
	{
		if(a[num2] + a[num1] == find)
		{
			cout<<a[num1]<<"+"<<a[num2]<<"="<<find<<endl;
			return;
		}
		else if(a[num2] + a[num1] > find)
			num2--;
		else 
			num1++;
	}
	cout<<"no have"<<endl;
}
void test1()
{
	int a[6] = {1,2,3,4,5,6};
	FindTwoNum(a,7,6);
	int a1[6] = {1,2,3,4,5,6};
	FindTwoNum(a,13,6);
}
//2**********************************和为S的正整数序列
void PrintSequance(int *a,int num1,int num2)
{
	for(int i = num1;i <= num2;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void FindSequance(int *a,int find,int length)
{
	bool IsFind = false;
	int num1 = 0;
	int num2 = 1;
	int sum = a[0]+a[1];
	while(num2 < length && num2 - num1 > 0)
	{
		if(sum == find)
		{
			IsFind = true;
			PrintSequance(a,num1,num2);
			sum-= a[num1];
			num1++;
		}
		if(sum > find)
		{
			sum -= a[num1];
			num1++;
		}
		else
		{
			num2++;
			sum += a[num2];
		}
	}
	if(IsFind == false)
		cout<<"no have"<<endl;
}
void test2()
{
	int a[6] = {1,2,3,4,5,6};
	FindSequance(a,7,6);
	FindSequance(a,9,6);
}
//3***************************翻转单词顺序
//"i am a student" -->  "student a am i"
void Reverse(char *start,char *end)
{
	assert(start);
	assert(end);

	while(start < end)
	{
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
}
void ReverseStr(char *str)
{
	assert(str);

	int length = strlen(str);

	char *start = str;
	char *end = str+length-1;
	Reverse(start,end);

	start = end = str;

	while(*end != '\0')
	{
		if(*start == ' ')
		{
			start++;
			end++;
		}
		else if(*end == ' ' || *end == '\0'){
			Reverse(start,end-1);
			start = end;
		}else
			++end;
	}
	cout<<str<<endl;
}
void test3()
{
	//不小心写成char *str = "i am student";害我找了好长时间的错误，，谨记！！  
	char str[] = "i am student";      
	ReverseStr(str);
}
//4***************************左旋转字符串
//借助上面的Reverse
char *LeftRotate(char *str,int n)
{
	assert(str);
	assert(n > 0);

	int length = strlen(str);

	char *start = str;
	char *end = str+length-1;
	Reverse(start,end);

	char *pos = start+n;

	Reverse(start,pos-1);
	Reverse(pos,end);

	return str;
}
void test4()
{
	char a[] = "abcdef";
	cout<<LeftRotate(a,2);
}
//5***************************n个骰子的点数
//1.递归
void __Probability(int num,int cur,int sum,int *array)
{
	if(cur == 1)
	{
		array[sum-num]++;
	}
	else
	{
		for(int i = 1;i <= 6;++i)
			__Probability(num,cur-1,i+sum,array);
	}
}
void _Probability(int num,int *array)
{
	for(int i = 1;i <= 6;++i)
		__Probability(num,num,i,array);
}
void Probability(int num)
{
	if(num <= 0)
		return;

	int max = 6*num-num+1;
	int *array = new int[max]; //保存点数出现的次数，为什么是6*num-num+1？？
	                                   //如果有2个骰子，可能的点数和是2--12 ==》6*2-2+1
	memset(array,0,max*4);

	_Probability(num,array);

	int total = pow((double)6,num);

	for(int i = num;i <= num*6;++i)
	{
		double radio = (double)array[i-num]/total;
		cout<<i<<":"<<radio<<"%"<<endl;
	}

	delete[] array;
}
//非递归
void Probability_NonR(int num)
{
	if(num <= 0)
		return;

	int max = 6*num+1;

	int *array[2];
	array[0] = new int[max];
	array[1] = new int[max];

	for(int i = 0;i < max;++i)
	{
		array[0][i] = 0;
		array[1][i] = 0;
	}

	int flag = 0;
	for(int i = 1;i <= 6;++i)
		array[0][i] = 1;

	for(int i = 2;i <= num;++i)
	{
		for(int k = 0;k < i;++k)
			array[1 - flag][k] = 0;

		for(int k = i;k <= 6*i;++k)
		{
			array[1 - flag][k] = 0;
			for(int j = 1;j <= k && j <= 6;++j)
				array[1 - flag][k] += array[flag][k-j];
		}
		flag = 1 - flag;
	}
	int total = pow((double)6,num);

	for(int i = num;i <= num*6;++i)
	{
		double radio = (double)array[flag][i]/total;
		cout<<i<<":"<<radio<<"%"<<endl;
	}

	delete[] array[0];
	delete[] array[1];
}
void test5()
{
	Probability(2);
	Probability_NonR(2);
}
//6***************************圆圈中剩下的数字
int LastNumber(int n,int m)
{
	assert(m > 0);
	assert(n >= 0);

	list<int> li;
	for(int i = 0;i < n;++i)
		li.push_back(i);

	list<int>::iterator it = li.begin();

	while(li.size() > 1)
	{
		int count = 0;
		while(count < m-1)
		{
			if(it == li.end()) //如果遇到头结点,越过头结点
				it = li.begin();

			it++;
			count++;
		}

		if(it == li.end()) //如果遇到头结点
		{
			it = li.begin();
		}
		list<int>::iterator tmp = it;

		it++;
		if(it == li.end()) //如果遇到头结点
			it = li.begin();

		li.erase(tmp);
	}
	return *it;
}
//用循环，时间复杂度是O(n)//数学的魅力呀！！
int LastNumber_Better(int n,int m)
{
	if(n < 1 || m < 1)
		return -1;
	int last = 0;
	for(int i = 2;i <= n;++i)
		last = (last+m)%i;
	return last;
}
void test6()
{
	cout<<LastNumber(6,2)<<endl;
	cout<<LastNumber_Better(6,2)<<endl;
}
//7***************************求1+2+3...+n,不能用乘除和条件判断
//1.利用构造函数，构造一个N个对象数组
class tmp{
public:
	tmp()
	{
		sum += count;
		count++;
	}
	static int GetSum()
	{
		return sum;
	}
	static void Reset()
	{
		sum = 0;
		count = 1;
	}
private:
	static int sum;
	static int count;
};
int tmp::sum = 0;
int tmp::count = 1;

void GetRet(int n)
{
	tmp::Reset();
	tmp *a = new tmp[n];
	delete []a;
	a = NULL;
	cout<<tmp::GetSum()<<endl;
}
//2.利用虚函数求解
class A;
A *array[2];
class A
{
public:
	virtual int sum(int n)
	{
		return 0;
	}
};
class B:public A
{
public:
	virtual int sum(int n)
	{
		return array[!!n]->sum(n-1)+n;
	}
};
int Getsum(int n)
{
	A a;
	B b;
	array[0] = &a;
	array[1] = &b;

	int sum = array[1]->sum(n);
	return sum;
}
//3.利用函数指针求解
typedef int (* fun)(int n);
int fun1(int n)
{
	return 0;
}
int fun2(int n)
{
	static fun f[2] = {fun1,fun2};
	return n + f[!!n](n-1);
}
//4.利用模板类型求解  
template<int n> 
struct fun4
{
	enum Value
	{
		N = fun4<n - 1>::N + n,
	};

};
template<>
struct fun4<1>
{
	enum Value{
		N = 1,
	};
};
void test7()
{
	GetRet(5);
	cout<<Getsum(5)<<endl;
	cout<<fun2(5)<<endl;
	struct fun4<5> f;
	cout<<f.N<<endl;
}
//8***************************不用加减乘除做加法
//用位运算
int add(int num1,int num2)
{
	int sum,carry;
	do
	{
		sum = num1 ^ num2;
		carry = (num1 & num2)<<1;

		num1 = sum;
		num2 = carry;
	}
	while(num2 != 0);
	return sum;
}
void test8()
{
	cout<<add(5,7)<<endl;
}
int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	//test5();
	//test6();
	//test7();
	//test8();
	system("pause");
	return 0;
}