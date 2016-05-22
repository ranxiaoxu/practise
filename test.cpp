#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;

//1**************************面试题3：二维数组中查找
//1.递归实现
bool Search(int a[][4],int row,int rowstart,int colend,int x)   
{
	assert(a);
	if(rowstart > row || colend < 0)
		return false;

	if(x > a[rowstart][colend-1])
		return Search(a,row,rowstart+1,colend,x);
	else if(x < a[rowstart][colend-1])
		return Search(a,row,rowstart,colend-1,x);
	else                  //x == a[rowstart][colend-1]
		return true;
}

//2.非递归实现
bool Search_NonR(int a[][4],int row,int col,int x)    
{
	bool ret = false;
	int rowstart = 0;
	int colend = col-1;
	while(rowstart < row && colend >= 0)
	{
		if(x == a[rowstart][colend])
		{
			ret = true;
			break;
		}
		else if(x > a[rowstart][colend])
			rowstart++;
		else 
			colend--;
	}
	return ret;
}
void testSearch()
{
	int a[4][4] = {1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15};
	bool ret1 = Search(a,4,0,4,7); 
	cout<<ret1<<endl;
	bool ret2 = Search_NonR(a,4,4,7); 
	cout<<ret2<<endl;

	bool ret3 = Search(a,4,0,4,5); 
	cout<<ret3<<endl;
	bool ret4 = Search_NonR(a,4,4,5); 
	cout<<ret4<<endl;
}

//2************************************面试题3：空格替换为%20
char* Replace_blank(char *str)
{
	assert(str);
	char *tmp = str;
	int count = 0;   
	while(*tmp != '\0')   //统计空格的个数
	{
		if(*tmp == ' ')
			count++;
		tmp++;
	}
	if(count == 0)
	{
		return str;
	}

	char *str1 = str + strlen(str) + count*2;
	char *str2 = str + strlen(str);

	while(str1 != str2)
	{
		while(*str2 != ' ')
		{
			*str1-- = *str2--;
		}
		*str1-- = '%';
		*str1-- = '0';
		*str1-- = '2';

		str2--;
	}
	return str;
}
void testReplace_blank()
{
	char a[20] = "we are happy";
	cout<<Replace_blank(a);
}

//3***********************************面试题八：旋转数组中的最小数字
int Min(int *a,int length)
{
	assert(a);

	int left = 0;
	int right = length - 1;
	int mid = (left + right)/2;

	while(right - left > 1)
	{
		if(a[left] > a[right])    //最小值在右边
		{
			left = mid;
			mid = (left + right)/2;
		}
		else if(a[left] > a[right])    //最小值在左边
		{
			right = mid;
			mid = (left + right)/2;
		}
		//没有考虑到极端情况，例如11101，或者是12301，如果left,right的值相同，就只能顺序查找
		else if(a[left] == a[right])
		{
			int min = a[left];
			for(int i = left;i < right;++i)
			{
				if(a[i] < min)
					min = a[i];
			}
			return min;
		}
	}
	return a[left] > a[right] ? a[right]:a[left];
}
void testMin()
{
	int a[5] = {3,4,5,1,2};
	int ret = Min(a,5);
	cout<<ret<<endl;

	int a1[5] = {0,1,0,0,0};
	int ret1 = Min(a1,5);
	cout<<ret1<<endl;
}

//4***********************************面试题九：斐波那契数列
//递归实现,时间复杂度是o(2^n)(想成一个二叉树)
int Fibonacci_R(int n)
{
	if(n == 1 || n == 2)
		return 1;
	return Fibonacci_R(n-1) + Fibonacci_R(n-2);
}
//非递归实现
//时间复杂度是o(n)
int Fibonacci_NonR(int n)
{
	if(n == 1 || n == 2)
		return 1;
	int f1 = 1;
	int f2 = 1;
	int f3;
	while( n-2 > 0)
	{
		f3 = f2 + f1;
		f1 = f2;
		f2 = f3;
		--n;
	}
	return f3;
}
void testFibonacci()
{
	int ret = Fibonacci_R(6);
	cout<<ret<<endl;

	int ret1 = Fibonacci_NonR(6);
	cout<<ret1<<endl;
}

//5***********************************面试题十：二进制中1的个数
//常规解法
int Count(int num)
{
	int tmp = 1;
	int count = 0;
	for(int i = 0;i < 32;i++)
	{
		if((num & tmp) > 0)
			count++;

		tmp = tmp<<1;
	}
	return count;
}
//新奇的解法
//以9为例，第一次num = (9-1)&9 = 8;第二次num = (8-1)&8 = 0
int Count_N(int num)
{
	int count = 0;
	while(num)
	{
		num = (num - 1) & num;
		++count;
	}
	return count;
}
void testCount()
{
	int ret = Count(9);
	cout<<ret<<endl;

	int ret1 = Count_N(9);
	cout<<ret1<<endl;
}

//6***********************************面试题十四：调整数组顺序，使奇数位于偶数前面
void Adjust(int *a,int length)
{
	int start = 0;
	int end = length-1;

	while(start < end)
	{
		while((start < end) && ((a[start] & 1) != 0))   //从左边找偶数
		{
			++start;
		}
		while((start < end) && ((a[end] & 1) == 0))   //从右边找奇数
		{
			--end;
		}

		if(start < end)
		{
			int tmp;
			tmp = a[start];
			a[start] = a[end];
			a[end] = tmp;
			++start;
			--end;
		}
	}
}
//扩展性的解法,如果不是判断不是奇数偶数，而是别的，能否给出一个模式
bool isEven(int n)
{
	return n & 1;
}
void ReOrder(int *a,int length,bool (*func)(int))
{
	int start = 0;
	int end = length-1;

	while(start < end)
	{
		while((start < end) && (func(a[start]) == true)) 
		{
			++start;
		}
		while((start < end) && (func(a[end]) == false))   
		{
			--end;
		}

		if(start < end)
		{
			int tmp;
			tmp = a[start];
			a[start] = a[end];
			a[end] = tmp;
			++start;
			--end;
		}
	}
}
void ReOderOddEven(int *a,int length)
{
	 ReOrder(a,length,isEven);
}
void testAdjust()
{
	int a[5] = {2,5,6,8,4};
	Adjust(a,5);
	for(int i = 0;i < 5;++i)
		cout<<a[i];
	cout<<endl;

	ReOderOddEven(a,5);
	for(int i = 0;i < 5;++i)
		cout<<a[i];
}

//7***********************************面试题40：数组中有两个只出现一次的数字（其他的都是成对出现）
//*******************************************要求时间复杂度o（n）,空间复杂度o(1)
int FindOne(int *num,int length)    
{
	int ret = 0;
	for(int i = 0;i < length;++i)
	{
		ret = ret^num[i];
	}
	return ret;
}
int FindOneBit(int num)    //找到从右边开始第一个为1的位
{
	int tmp = 1;
	for(int i = 0;i < 32;++i)
	{
		if((num & tmp) != 0 )
			return i;
		tmp = tmp<<1;
	}
}
void Find_alone_two(int *a,int length)
{
	assert(a);
	assert(length > 0);
	int ret = FindOne(a,length);
	int pos = FindOneBit(ret);
	int num1 = 0;
	int num2 = 0;
	int tmp = 1;
	for(int i = 0;i < length;++i)
	{
		if((a[i] & (tmp<<pos)) == 0 )
			num1 ^= a[i];
		else
			num2 ^= a[i];
	}
	cout<<"num1:"<<num1<<endl;
	cout<<"num2:"<<num2<<endl;

}
void testFindOne()
{
	int a[6] = {1,1,2,2,3,4};
	Find_alone_two(a,6);
}

//8***********************************面试题20：顺时针打印矩阵
void PrintCircle(int a[][1],int rowstart,int rowend,int colstart,int colend)
{
	//如果只有一行
	if(rowend == rowstart)
	{
		for(int i = colstart;i <= colend;++i)
		cout<<a[rowstart][i]<<" ";
		return;
	}
	
	//如果只有一列
	if(colend == colstart)
	{
		for(int i = rowstart;i <= rowend;++i)
		cout<<a[i][colstart]<<" ";
		return;
	}
	//从左到右打印一行
	for(int i = colstart;i <= colend;++i)
		cout<<a[rowstart][i]<<" ";

	//从上到下打印一列
	for(int i = rowstart;i <= rowend;++i)
		cout<<a[i][colend]<<" ";

	//从右到左打印一行
	for(int i = colend;i >= colstart;--i)
		cout<<a[rowend][i]<<" ";

	//从下到上打印一列
	for(int i = rowend;i >= rowstart;--i)
		cout<<a[i][colstart]<<" ";
}
void PrintMatrix(int a[][1],int row,int col)
{
	int rowstart = 0;
	int rowend = row - 1;
	int colstart = 0;
	int colend = col - 1;

	while((rowstart * 2) < row && (colstart *2) < col)
	{
		PrintCircle(a,rowstart,rowend,colstart,colend);
		++rowstart;
		--rowend;
		++colstart;
		--colend;
	}
}
void PrintMatrixtest()
{
	int a[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	//PrintMatrix(a,4,4);
	//cout<<endl;

	//int a1[1][4] = {1,2,3,4};
	//PrintMatrix(a1,1,4);

	int a2[4][1] = {1,2,3,4};
	PrintMatrix(a2,4,1);
}

//9***********************************面试题44:扑克牌中的顺子
void BullSort(int *a,int size)     //冒泡排序
{
	for(int i = 0;i < size-1;++i)
	{
		for(int j = 0;j < size-1-i;j++)
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}
bool IsCountinue(int *a,int length)
{
	assert(a);
	assert(length > 0);

	BullSort(a,length); 
	
	int zeroCount = 0;
	int gap = 0;

	for(int i = 0;i < length-1;++i)
	{
		if(a[i] == 0)
			zeroCount++;
		else
		{
			if(a[i] == a[i+1])    //如果有对子
				return false;

			gap += a[i+1] - a[i] - 1;
		}
	}
	if(zeroCount >= gap)
		return true;
	else 
		return false;
}
void testIsCountinue()
{
	int a[5] = {0,1,3,2,3};
	cout<<IsCountinue(a,5)<<endl;

	int a1[5] = {0,1,5,2,3};
	cout<<IsCountinue(a1,5)<<endl;
	int a2[5] = {0,1,3,4,2};
	cout<<IsCountinue(a2,5)<<endl;
	int a3[5] = {0,1,3,2,0};
	cout<<IsCountinue(a3,5)<<endl;
	int a4[5] = {0,1,6,2,0};
	cout<<IsCountinue(a4,5)<<endl;
}

//10***********************************面试题49:把字符串转换成整数
enum Status
{
	Valid = 0,
	InValid = 1,
	Overflow = 2,
};
Status g_status = InValid;   //标志是否是非法输入
bool IsOverflow(string str,char cSymbol)   //判断是否溢出
{
	if(str.size() == 0)    //这里不是真的溢出，而是非法值
		return true;
	if(str.size() > 31)    //因为最高位是符号位，所以是31
	{
		g_status = Overflow;
		return true;
	}

	if('+' == cSymbol && str.size() == 10 && strcmp(str.c_str(),"2147483647") > 0)
	{
		g_status = Overflow;
		return true;
	}
	else if('-' == cSymbol && str.size() == 10 && strcmp(str.c_str(),"2147483647") > 0)
	{
		g_status = Overflow;
		return true;
	}
	return false;
}
int My_atoi(const char *str)
{
	//NULL "+12345" "-12345" "001234" "a12345"  溢出
	int num = 0;
	if(str != NULL )
	{
		char cSymbol = '+';   //符号位
		if('+' == str[0] || '-' == str[0])
		{
			cSymbol = str[0];
			str++;
		}
		char *pstr = (char *)str;

		string tmp(str);
		int iCount = 0;    //有效数据的个数
		while(*str >= '0' && *str <= '9')
		{
			iCount++;
			str++;
		}
		tmp.resize(iCount);

		if(!IsOverflow(tmp,cSymbol))
		{
			while(*pstr >= '0' && *pstr <= '9')
			{
				num = num * 10 + *pstr - '0';
				pstr++;
			}
			if(num != 0)  //如果num == 0,说明是无效值
				g_status = Valid;

			if('-' == cSymbol)
			{
				num = 0 - num;
			}
		}
	}
	return num;
}
void testMy_atoi() 
{
	//cout<<My_atoi("-1234")<<"  "<<"status:"<<g_status<<endl;
	//cout<<My_atoi("+1234")<<"  "<<"status:"<<g_status<<endl;
	//cout<<My_atoi("-ahgd")<<"  "<<"status:"<<g_status<<endl;   //无效
	//cout<<My_atoi("a12344444454893789")<<"  "<<"status:"<<g_status<<endl; //无效
	//cout<<My_atoi("237483")<<"  "<<"status:"<<g_status<<endl;
	cout<<My_atoi("123457837239182192890129839201298930293843902398493")<<"  "<<"status:"<<g_status<<endl;   //溢出

}
int main()
{
	//testSearch();
	//testReplace_blank();
	//testMin();
	//testFibonacci();
	//testCount();
	//testAdjust();
	//testFindOne();
	//PrintMatrixtest();
	//testIsCountinue();
	testMy_atoi();
	system("pause");
	return 0;
}