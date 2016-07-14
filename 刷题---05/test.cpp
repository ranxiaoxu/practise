#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<set>
#include<vector>
using namespace std;
//1*********************************��ֵ�������η�
//1.���ָ��Ϊ������Ҫ��������0����������������Ϊ0��ָ��Ϊ����ʱ������������
//��θ��ߺ��������߳��������ִ������ַ���������ֵ��ȫ�ִ��룬�쳣
//2.0��0�η�û�����壬����0��1������
bool equal(double num1,double num2)
{
	if(abs(num1 - num2) < 0.0000001)
		return true;
	else 
		return false;
}
//double Exponent(double base,int exponent)    //���������Ż�
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
	if(equal(base,0.0) && exponent < 0)    //Ϊʲô����base==0.0,��Ϊ�����
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
//2*********************************��ӡ1������nλ��
//Ҫ���Ǵ�������
bool Increace(char *num,int n)   //�ַ���ģ��ӷ�
{
	for(int i = n-1;i >= 0;--i)
	{
		int carry = 0;
		int sum = num[i] - '0' + 1 + carry;
		
		if(sum == 10)
		{
			if(i == 0)    //���
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
void _Print(char *num)   //��ӡ�ַ�����������'0'�ĲŴ�ӡ
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
//3*********************************�ַ���������
//abc---abc,acd,bac,bca,cba,cab�õݹ飬�����ַ�
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
//4*********************************�ַ����������
void _Combination(char *string ,int number,vector<char> &result);  
void Combination(char *string)  
{  
    assert(string != NULL);  
    vector<char> result;  
    int i , length = strlen(string);  
    for(i = 1 ; i <= length ; ++i)  
        _Combination(string , i ,result);  
}  
void _Combination(char *string,int number,vector<char> &result)  
{  
    assert(string != NULL);  
    if(number == 0)  
    {  
        static int num = 1;  
        cout<<num++<<":";  
  
        vector<char>::iterator iter = result.begin();  
        for( ; iter != result.end() ; ++iter)  
            cout<<*iter; 

        cout<<endl;
        return ;  
    }  
    if(*string == '\0')  
        return ;  
    result.push_back(*string);  
    _Combination(string + 1,number - 1,result);  
    result.pop_back();  
    _Combination(string + 1,number,result);  
}  
void test4()
{
	char str[] = "ABC";  
    Combination(str); 
}
//5*********************************�����г���һ�������
//1.�����ڿ���������㷨���ҵ���λ��  
bool g_ret = false;
bool CheckOverHalf(int *a,int length,int number)
{
	g_ret = false;
	int count = 0;
	for(int i = 0;i < length;++i)
	{
		if(a[i] == number)
			count++;
	}
	if(count >= (length+1)/2)
	{
		g_ret = true;
		return true;	
	}
	else
		return false;
}
int Patition(int *a,int left,int right)
{
	assert(a && left >= 0 && right >= 0 && right >= left);
 
    int begin = left;  
    int end = right - 1;
    int key = a[right]; 

    while(begin < end)  
    {  
  
        while(begin < end && a[begin] <= key)  
            ++begin;  
  
        while(begin < end && a[end] >= key)  
            --end;  
  
        if(begin < end)  
            swap(a[begin],a[end]);  
    }  
    if(a[end] > key)  
    {  
        swap(a[end],a[right]);  
        return end;  
    }  
    else  
    {  
        return right;  
    }  
}  
int MoreThanhalf(int *array,int length)
{
	assert(array);
	assert(length > 0);

	int mid = length/2;
	int start = 0;
	int end = length-1;

	int index = Patition(array,start,end);

	while(index != mid)
	{
		if(index > mid)
		{
			end = index -1;
			index = Patition(array,start,end);
		}
		else if(index < mid)
		{
			start = index + 1;
			index = Patition(array,start,end);
		}
	}
	int ret = array[mid];
	if(CheckOverHalf(array,length,ret))
		return ret;
	else
		return 0;
}
//2.����������ص����

//���count==0,���浱ǰ������count=1
//�����ǰ�������ϴε�����ͬ��count++
//�����ǰ�������ϴβ�ͬ��count--
//���Ľ���������һ�α������
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
	int a1[5] = {2,3,1,2,2};
	cout<< MoreThanhalf(a,5)<<"   g_ret:"<<g_ret<<endl;
	cout<<FindOverHalf(a,5)<<endl;
	cout<< MoreThanhalf(a1,5)<<"   g_ret:"<<g_ret<<endl;
	cout<<FindOverHalf(a1,5)<<endl;
}
//6*********************************��С��K����
//1.�õ�ǰ���Patition����,���Ǹı���ԭ��������
void FinkMinK(int *array,int n,int k)
{
	assert(array && n >=0 && k >= 0);

	int start = 0;
	int end = n-1;
    
	int index = Patition(array,start,end);

	while(index != k-1)
	{
		if(index > k-1)
		{
			end = index -1;
			index = Patition(array,start,end);
		}
		else if(index < k-1)
		{
			start = index + 1;
			index = Patition(array,start,end);
		}
	}
}
//2.��stl�������,�ô�ѵ�˼��
void _FinkMinK(int *array,int length,int k)
{
	assert(array);
	assert(k > 0);

	multiset<int,greater<int>> s;
	multiset<int,greater<int>>::iterator s_iterater;

	int count = 0;

	s.clear();

	while(count < length)
	{
		if(s.size() < k)
			s.insert(array[count]);
		else
		{
			s_iterater = s.begin();
			if(*s_iterater > array[count])
			{
				s.erase(s_iterater);
				s.insert(array[count]);
			}
		}
		count++;
	}
	s_iterater = s.begin();
	while(s_iterater != s.end())
	{
		cout<<*s_iterater<<"  ";
		s_iterater++;
	}
}
void test6()
{
	int a[10] = {3,4,5,6,7,8,9,10,1,2};
	FinkMinK(a,10,4);
	for(int i = 0;i < 4;++i)
		cout<<a[i]<<"  ";
	cout<<endl;
	_FinkMinK(a,10,4);
}
//7*********************************���������������
//�۲����
int FindMaxSubArray(int *a,int n)
{
	assert(a);
	assert(n > 0);

	int sum = 0;
	int maxsum = sum;
	for(int i = 0;i < n;++i)
	{
		if(sum < 0)
			sum = a[i];
		else 
			sum += a[i];
		if(sum > maxsum)
			maxsum = sum;
	}
	return maxsum;
}
void test7()
{
	int a[8] = {1,-2,3,10,-4,7,2,-5};
	cout<<FindMaxSubArray(a,8)<<endl;
}
//8*********************************�������ų���С����
//����3��32��321���ų�����С������321323�����صĴ�������
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

//9*********************************����
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

		if(ret == number2 * 2)     //����
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
//10*********************************�����е������
//���������5��6��3��4����ô������ǣ�5��3����5��4����6��3����6��4��
//����һ��ʱ�临�Ӷ���O(n^2)
int ReversePair(int *array,int length)
{
	assert(array && length > 0);
	int count = 0;
	for(int i = 0;i < length;++i)
	{
		for(int j = i+1;j < length;++j)
		{
			if(array[i] > array[j])
				//cout<<"�����"<<"("<<array[i]<<","<<array[j]<<")"<<endl;
				count++;
		}
	}
	return count;
}
//����2:���ù鲢�����˼��,ʱ�临�Ӷ�O(nlogn)
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
	test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	//test10();
	system("pause");
	return 0;
}