//////////////////////////////////////////
//关于链表的题目
//////////////////////////////////////////

#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<stack>
using namespace std;

struct ListNode
{
	int _data;
	ListNode *_next;

	ListNode(const int &x)
		:_data(x) 
		,_next(NULL)
	{}
};

class List
{
private:
	ListNode *_head;
	ListNode *_tail;
public:
	List()
		:_head(NULL)
		,_tail(NULL)
	{}

	~List()
	{
		Clear();
	}

	void Clear()
	{
		ListNode *begin = _head;
		while(begin)
		{
			ListNode *del = begin;
			begin = begin->_next;
			delete del;
		}
		_head = _tail = NULL;
	}
	void Print()
	{
		ListNode *tmp = _head;
		while(tmp != NULL)
		{
			cout<<tmp->_data<<"->";
			tmp = tmp->_next;
		}
		cout<<"NULL"<<endl;
	}
	void Push_Back(int x)
	{
		//1.没有结点 2.有结点
		ListNode *tmp = new ListNode(x);
		if(_head == NULL){
			_head = tmp;
			_tail = tmp;
		}else{
			_tail->_next = tmp;
			_tail = tmp;
		}
	}
	ListNode *Find(const int& x)
	{
		ListNode *cur = _head;
		while(cur != NULL)
		{
			if(cur->_data == x)
				return cur;

			cur = cur->_next;
		}
		return NULL;
	}

//1**********************从尾到头打印链表
	void PrintListReverse()   
	{
		//利用栈实现
		stack<int> st;
		ListNode *cur = _head;
		while(cur != NULL)
		{
			st.push(cur->_data);
			cur = cur->_next;
		}
		while(!st.empty())
		{
			cout<<st.top()<<"->";
			st.pop();
		}
		cout<<"NULL"<<endl;
	}
	void PrintListReverse_R()
	{
		//递归实现
		_PrintListReverse(_head);   
	}
	void _PrintListReverse(ListNode *cur)
	{
		if(cur == NULL)
			return;

		_PrintListReverse(cur->_next);

		cout<<cur->_data<<" ";
	}
	ListNode *GetHead()
	{
		return _head;
	}
//2**********************在O(1)时间删除链表结点
	void DeleteNode(ListNode *Nodedel)
	{
		//1.要删除的链表不是尾结点,用下一个结点的值覆盖当前结点，删除下一个结点
		if(Nodedel->_next != NULL)
		{
			ListNode *Nextnode = Nodedel->_next;
			Nodedel->_data = Nextnode->_data;
			Nodedel->_next = Nextnode->_next;
			delete Nextnode;
			return;
		}

		//2.链表只有这一个结点
		if(Nodedel == _head && Nodedel->_next == NULL)
		{
			delete Nodedel;
			_head = NULL;
			return;
		}

		//3.Nodedel是尾结点,先要找到前一个结点
		if(Nodedel->_next == NULL)
		{
			ListNode *prev = _head;
			while(prev->_next != Nodedel)
				prev = prev->_next;

			prev->_next = NULL;
			delete Nodedel;
			return;
		}
	}
//3**********************链表中倒数第K个结点
	//注意非法输入
	ListNode *FindKNode(int k)
	{
		//利用快慢指针的思路
		//1.如果链表为空
		if(_head == NULL)
			return NULL;

		//2.如果k为0
		if(k == 0)
			return NULL;

		ListNode *first = _head;
		ListNode *second = _head;
		while(k-1 > 0)
		{
			first = first->_next;
			
			if(first == NULL)
				return NULL;

			k--;
		}

		while(first->_next != NULL)
		{

			first = first->_next;
			second = second->_next;
		}

		return second;
	}
//4**********************反转链表
	//要改变指针的指向
	void ReverseList()
	{
		if(_head == NULL || _head->_next == NULL)
			return;

		ListNode *pre = _head;
		ListNode *cur = pre->_next;
		pre->_next = NULL;

		while(cur != NULL)
		{
			ListNode *next = cur->_next;

			cur->_next = pre;

			pre = cur;
			cur = next;
		}

		_head = pre;
	}
//5**********************合并两个排序链表
	ListNode *Merge(ListNode *head2)
	{
		ListNode *cur1 = _head;
		ListNode *cur2 = head2;

		if(cur1 == NULL)
			return cur2;
		
		if(cur2 == NULL)
			return cur1;

		ListNode *newhead = NULL;
		ListNode *newtail = NULL;

		while(cur1 != NULL && cur2 != NULL)
		{
			if(cur1->_data < cur2->_data)
			{
				if(newhead == NULL)
				{
					newhead = cur1;
					newtail = newhead;
				}
				else
				{
					newtail->_next = cur1;
					newtail = newtail->_next;
				}

				cur1 = cur1->_next;
			}
			else
			{
				if(newhead == NULL)
				{
					newhead = cur2;
					newtail = newhead;
				}
				else
				{
					newtail->_next = cur2;
					newtail = newtail->_next;
				}

				cur2 = cur2->_next;
			}
		}
		if(cur1 == NULL && cur2 != NULL)
			newtail->_next = cur2;
		else if(cur2 == NULL && cur1 != NULL)
			newtail->_next = cur1;

		return newhead;
	}
//6**********************在O(1)时间删除链表结点
//7**********************复杂链表的复制
//8**********************两个链表的第一个公共结点
//9**********************用循环链表模拟圆圈
};
void testPrintListReverse()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);

	s1.PrintListReverse();
	s1.PrintListReverse_R();

}
void testDeleteNode()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);

	s1.Print();

	ListNode *del = s1.Find(5);
	s1.DeleteNode(del);
	s1.Print();

	ListNode *del1 = s1.Find(1);
	s1.DeleteNode(del1);
	s1.Print();

	
	
	ListNode *del2 = s1.Find(2);
	s1.DeleteNode(del2);
	s1.Print();

	ListNode *del3 = s1.Find(3);
	s1.DeleteNode(del3);
	s1.Print();

	ListNode *del4 = s1.Find(4);
	s1.DeleteNode(del4);
	s1.Print();


}
void testFindKNode()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);

	cout<<s1.FindKNode(2)->_data<<endl;
	cout<<s1.FindKNode(6)<<endl;
}
void testReverseList()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);

	s1.ReverseList();

	s1.Print();
}
void testMerge()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);

	List s2;
	s2.Push_Back(6);
	s2.Push_Back(7);
	s2.Push_Back(8);
	s2.Push_Back(9);

	ListNode *head = s1.Merge(s2.GetHead());
	while(head != NULL)
	{
		cout<<head->_data<<" ";
		head = head->_next;
	}
}
int main()
{
	//testPrintListReverse();
	//testDeleteNode();
	//testFindKNode();
	//testReverseList();
	testMerge();
	system("pause");
	return 0;
}

