#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
using namespace std;
//1*********************************数值的整数次方
//1.如果指数为负数，要求倒数，对0不能求倒数，当基数为0，指数为负数时，程序会崩溃，
//如何告诉函数调用者出现了这种错误，三种方法，返回值，全局代码，异常
//2.0的0次方没有意义，返回0或1都可以
bool equal(double num1,double num2)
{
	if(abs(num1 - num2) < 0.0000001)
		return true;
	else 
		return false;
}
//double Exponent(double base,int exponent)    //还可以再优化
//{
//	double result = 1;
//	while(exponent-- > 0)
//	{
//		result *= base;
//	}
//	return result;
//}
double Exponent(double base,int exponent)
{
	if(exponent == 0)
		return 1.0;
	if(exponent == 1)
		return base;

	double result = Exponent(base,exponent>>1);

	result *= result;

	if(exponent & 0x01 == 1)
		result *= base;

	return result;
}

bool g_InvalidInput = false;
double power(double base,int exponent)
{
	g_InvalidInput = false;
	double result = 0.0;
	if(equal(base,0.0) && exponent < 0)    //为什么不用base==0.0,因为有误差
	{
		g_InvalidInput = true;
		return 0.0;
	}
	if(base == 0 && exponent == 0)
	{
		return 0.0;
	}
	if(exponent > 0)
	{
		result = Exponent(base,exponent);
	}
	else
	{
		result = Exponent(base,-exponent);
		result = 1/result;
	}
	return result;
}

void test1()
{
	cout<<power(2,3)<<endl;
	cout<<power(0,0)<<endl;
	cout<<power(2,-3)<<endl;
	cout<<power(0.0003,3)<<endl;
	cout<<power(0.5,3)<<endl;
}
//2*********************************打印1到最大的n位数
//要考虑大数问题
bool Increace(char *num,int n)   //字符串模拟加法
{
	for(int i = n-1;i >= 0;--i)
	{
		int carry = 0;
		int sum = num[i] - '0' + 1 + carry;
		
		if(sum == 10)
		{
			if(i == 0)    //溢出
				return false;
			
			carry = 1;
			num[i] = '0';
		}
		else
		{
			num[i]++;
			return true;
		}
	}
}
void _Print(char *num)   //打印字符串，遇到非'0'的才打印
{
	while(*num == '0')
		num++;
	cout<<num<<" ";
}
void PrintNum(int n)
{
	if(n == 0)
		return;

	 char *num = new char[n+1];
	 memset(num,'0',n);
	 num[n] = '\0';

	 while(Increace(num,n) == true)
	 {
		 _Print(num);
	 }
	 cout<<endl;
}
void test2()
{
	PrintNum(3);
}
//3*********************************字符串的排列
//abc---abc,acd,bac,bca,cba,cab用递归，交换字符
void _StrArrange(char *str,char *start)
{
	if(*start == '\0')
		cout<<str<<" ";

	int length = strlen(start);
    for(int i = 0;i < length;++i)
	{
		swap(start[0],start[i]);
		_StrArrange(str,start+1);
		swap(start[0],start[i]);
	}
}
void StrArrange(char *str)
{
	 if(str == NULL)
		 return;
	 _StrArrange(str,str);
}
void test3()
{
	char str[] = "abc";
	StrArrange(str);
}
//4*********************************字符的所有组合


//5*********************************数组中超过一半的数字
bool CheckOverHalf(int *a,int length,int number)
{
	int count = 0;
	for(int i = 0;i < length;++i)
	{
		if(a[i] == number)
			count++;
	}
	if(count >= (length+1)/2)
		return true;
	else
		return false;
}
int FindOverHalf(int *array,int length)
{
	assert(array);
	assert(length > 0);

	int result = array[0];
	int count = 1;
	for(int i = 1;i < length;++i)
	{
		if(count == 0)
			result = array[i];

		if(result == array[i])
			count++;

		else
			count--;
	}
	if(CheckOverHalf(array,length,result))
		return result;
	else
		return 0;
}
void test5()
{
	int a[5] = {1,3,1,2,2};
	cout<<FindOverHalf(a,5);
}
//6*********************************最小的K个数
/*int FinkMinK(int *array,int k)
{
	set<int> set;
	for(;*array!= NULL;++array)
	{

	}
	return 0;
}*/
//7*********************************连续子数组的最大和

//8*********************************把数组排成最小的数
//例如3，32，321，排出来最小的数是321323，隐藏的大数问题
char *g_StrCombin1 = new char[20];
char *g_StrCombin2 = new char[20];

int comp(const void *number1,const void *number2)
{
	strcpy(g_StrCombin1,*(char **)number1);
	strcat(g_StrCombin1,*(char **)number2);

	strcpy(g_StrCombin2,*(char **)number2);
	strcat(g_StrCombin2,*(char **)number1);

	return strcmp(g_StrCombin1,g_StrCombin2);
}
void MergeMinNumber(int *array,int length)
{
	assert(array && length > 0);

	char ** str = (char **) (new int[length]);
	for(int i = 0;i < length;++i)
	{
		str[i] = new char[length];
		sprintf(str[i],"%d",array[i]);
	}

	qsort(str,length,sizeof(str[0]),comp);

	for(int i = 0;i < length;++i)
	{
		cout<<str[i];
	}
	cout<<endl;
}
void test8()
{
	int a[3] = {3,32,321};
	MergeMinNumber(a,3);
}

//9*********************************丑数
int min(int n1,int n2,int n3)
{
	if(n1 > n2)
	{
		swap(n1,n2);
	}
	if(n1 > n3)
		return n3;
	else return n1;
}
int GulyNumber(int count)
{
	assert(count>0);
	int *gulyarray = new int[count];
	memset(gulyarray,0,4*count);
	gulyarray[0] = 1;
	int number2 = 1;
	int number3 = 1;
	int number5 = 1;
	int index = 1;
	while(index < count)
	{
		int ret = min(number2 * 2,number3 * 3,number5 * 5);
		gulyarray[index] = ret;

		if(ret == number2 * 2)     //更新
			number2 = number2 * 2;
		if(ret == number3 * 3)
			number3 = number3 * 3;
		if(ret == number5 * 5)
			number5 = number5 * 5;

		index++;
	}
	return gulyarray[count-1];
}
void test9()
{
	cout<<GulyNumber(20)<<endl;
	cout<<GulyNumber(50)<<endl;

}
//10*********************************数组中的逆序对
//如果数组是5，6，3，4，那么逆序对是（5，3）（5，4）（6，3）（6，4）
//方法一：时间复杂度是O(n^2)
int ReversePair(int *array,int length)
{
	assert(array && length > 0);
	int count = 0;
	for(int i = 0;i < length;++i)
	{
		for(int j = i+1;j < length;++j)
		{
			if(array[i] > array[j])
				//cout<<"逆序对"<<"("<<array[i]<<","<<array[j]<<")"<<endl;
				count++;
		}
	}
	return count;
}
//方法2:利用归并排序的思想,时间复杂度O(nlogn)
int _ReversePair_2(int *array,int *tmp,int start,int end)
{
	if(start == end)
	{
		tmp[start] = array[start];
		return 0;
	}

	int length = (end - start)/2;

	int left = _ReversePair_2(array,tmp,start,start+length);
	int right = _ReversePair_2(array,tmp,start+length+1,end);

	int index1 = start+length;
	int index2 = end;
	int tmpindex = end;
	int count = 0;
	while(index1 >= start && index2 >= start+length+1)
	{
		if(array[index1] > array[index2])
		{
			tmp[tmpindex--] = array[index1--];
			count += index2-start-length;     //index-(start+length)
		}
		else
		{
			tmp[tmpindex--] = array[index2--];
		}
	}
	for(;index1 >= start;index1--)
		tmp[tmpindex--] = array[index1];
	for(;index2 >= start+length+1;index2--)
		tmp[tmpindex--] = array[index2];

	return left + right + count;
}
int ReversePair_2(int *array,int length)
{
	assert(array && length > 0);

	int *tmp = new int[length];

	int count = _ReversePair_2(array,tmp,0,length-1);
	delete[] tmp;

	return count;
}

void test10()
{
	int a[4] = {5,6,3,4};
	cout<<ReversePair(a,4)<<endl;

	cout<<ReversePair_2(a,4)<<endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test5();
	//test8();
	//test9();
	//test10();
	system("pause");
	return 0;
}