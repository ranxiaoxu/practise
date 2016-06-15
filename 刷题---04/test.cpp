#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<stack>
#include<queue>
using namespace std;

//1**********************两个栈实现队列
//定义了两个栈，s1, s2, s1负责入，s2负责出，pop的时候如果s2为空，就把s1的数据倒入s2中，不为空就pop掉s2栈顶的元素
template <typename T>
class Queue{
private:
    stack<T> _s1;    //进的操作
    stack<T> _s2;   //出的操作
public:
    Queue()
    {}
    bool empty()
    {
        if(_s1.empty() && _s2.empty()){
            return true;
        }else{
            return false;
        }
    }
    void push(T data)
    {
        _s1.push(data);
    }
    void pop()
    {
        if(empty()){
            cout<<"Queue is empty"<<endl;
            return;
        }else{
            if(_s2.empty()){
                while(!_s1.empty()){
                T tmp = _s1.top();
                _s1.pop();
                _s2.push(tmp);
                }
            }
            _s2.pop();
        }
    }
};
void test1()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.pop();
    q.push(3);
}

//2**********************一个数组实现两个栈
#define Max_size 100
class Stack{
private:
	int *_array;
    size_t _size;
    int top[2];
public:
	Stack(int size)
                :_size(size)
        {
                _array = ( new int[_size]);
                top[0] = -1;
                top[1] = _size;
        }
        Stack(Stack & s)
        {
                _size = s._size;
                _array = new int[_size];
                top[0] = s.top[0];
                top[1] = s.top[1];
                 for(int i = 0;i < _size;i++)
                {
                        _array[i] = s._array[i];
                }
        }
        Stack & operator = (Stack &s)
        {
                 if(this != &s){
                         delete[]_array;
                        _size = s._size;
                        _array = new int[_size];
                        top[0] = s.top[0];
                        top[1] = s.top[1];
                         for(int i = 0;i < _size;i++)
                        {
                                _array[i] = s._array[i];
                        }
                }
                 return *this ;
        }

        ~Stack()
        {
                 delete[]_array;
        }
         bool empty(int number)
        {
                assert(number == 0 || number == 1);
                 if(number == 0 && top[0] == -1)
				 {
                         return true ;
                 } 
				 else if (number == 1 && top[1] == _size)
				 {
                         return true ;
				 }
                 return false ;
        }
         void push(int n,int value)
        {
                assert(n == 0 || n == 1);
                 if(top[1] - top[0] == 1)
				 {
                        cout<< "full"<<endl;
                         return;
                }
                 else
				 {
                        n == 0 ? top[0]++ : top[1]--;
                        _array[top[n]] = value;
                }
        }
        int pop( int n)
        {
                assert(n == 0 || n == 1);
                int data;
                 if(empty(n) == true )
				 {
                        cout<< "empty!"<<endl;
                         return -1;
                }
                data = _array[top[n]];
                n == 0 ? top[0]-- : top[1]++;
                 return data;
        }
        int top_data( int n)
        {
                assert(n == 0 || n == 1);
                 if(empty(n) == true )
				 {
                        cout<< "empty"<<endl;
                         return -1;
                }
                 return _array[top[n]];
        }
};

void test2()
{
	Stack s(100);
	s.push(0,1);
	s.push(0,2);
	s.push(0,3);
	s.push(0,4);
	s.push(0,5);
	s.push(1,6);
	s.push(1,7);
	s.push(1,8);
	s.push(1,9);
	s.push(1,10);
	s.pop(0);
	s.pop(1);
}
//3**********************两个队列实现一个栈
//出栈的时候先把一个队列里的前面的数都挪到另一个队列中，剩一个的时候再pop
template<typename T>
class _Stack{
private:
    queue<T> q1;
    queue<T> q2;
public:
    _Stack()
    {}

    bool empty()
    {
        if(q1.empty() && q2.empty()){
            return true;
        }else{
            return false;
        }
    }
    void push(T data)
    {
        if(q1.empty() && q2.empty()){
            q1.push(data);
        }else if(!q1.empty() && q2.empty()){
            q1.push(data);
        }else if(q1.empty() && !q2.empty()){
            q2.push(data);
        }
    }
    void pop()
    {
        T tmp ;
        if(empty()){
            cout<<"stack is empty!!";
            return;
        }else if(!q1.empty()){
            while(q1.size() != 1){
                tmp = q1.front();
                q1.pop();
                q2.push(tmp);
            }
            q1.pop();
            return;
        }else{
            while(q2.size() != 1){
                tmp = q2.front();
                q2.pop();
                q2.push(tmp);
            }
            q2.pop();
            return;
        }
    }
};

void test3()
{
    _Stack<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.pop();
}
//4**********************判断出栈入栈的合法性

void judge(int *_in,int *_out, int n)
{
	stack< int> s;
    bool find = false ;
    int j = 1;
    s.push(_in[0]);
    for(int i = 0;i < n;++i)
    {
        if(s.top()== _out[i] && s.size() != 0)
        {
			s.pop();
        } 
		else
        {
             find = false;
             for(; j < n;++j) 
             {
				 s.push(_in[j]);  
                 if(_in[j] == _out[i])
				 {
					 ++j;
				     find = true; 
                     break;                    
                 }
             } 
             if(find == false )
			 {
				 cout<< "wrong!!!"<<endl;
                 return;
             }
			 else
			 {
				 s.pop();
             }
        }  
    }
    cout<< "right!!!"<<endl;
}
void test4()
{
         int a[5] = {1,2,3,4,5};
         int b[5] = {4,5,3,2,1};
		 int c[5] = {4,5,2,3,1};
        judge(a,b,5);
        judge(a,c,5);
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	system("pause");
	return 0;
}