//////////////////////////////////////////
//�����������Ŀ
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
		//1.û�н�� 2.�н��
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

//1**********************��β��ͷ��ӡ����
	void PrintListReverse()   
	{
		//����ջʵ��
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
		//�ݹ�ʵ��
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
//2**********************��O(1)ʱ��ɾ��������
	void DeleteNode(ListNode *Nodedel)
	{
		//1.Ҫɾ����������β���,����һ������ֵ���ǵ�ǰ��㣬ɾ����һ�����
		if(Nodedel->_next != NULL)
		{
			ListNode *Nextnode = Nodedel->_next;
			Nodedel->_data = Nextnode->_data;
			Nodedel->_next = Nextnode->_next;
			delete Nextnode;
			return;
		}

		//2.����ֻ����һ�����
		if(Nodedel == _head && Nodedel->_next == NULL)
		{
			delete Nodedel;
			_head = NULL;
			return;
		}

		//3.Nodedel��β���,��Ҫ�ҵ�ǰһ�����
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
//3**********************�����е�����K�����
	//ע��Ƿ�����
	ListNode *FindKNode(int k)
	{
		//���ÿ���ָ���˼·
		//1.�������Ϊ��
		if(_head == NULL)
			return NULL;

		//2.���kΪ0
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
//4**********************��ת����
	//Ҫ�ı�ָ���ָ��
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
//5**********************�ϲ�������������
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
//6**********************��������ĵ�һ���������
	void Cross(ListNode *head2)
	{
		//������,O(m*n)
		ListNode *cur1 = _head;
		ListNode *cur2 = head2;
		if(cur1 == NULL || cur2 == NULL){
			return;
		}
		while(NULL != cur1)
		{
			while(NULL != cur2)
			{
				if(cur1->_data == cur2->_data)
				{
					cout<<"������ǣ�"<<cur1->_data<<endl;
					return;
				}
				cur2 = cur2->_next;
			}
			cur2 = head2;
			cur1 = cur1->_next;
		}
		cout<<"û�н���"<<endl;
	}
	void Cross_Better(ListNode *head2)
	{
		if(_head == NULL || head2 == NULL){
			return;
		}

		int length1 = GetLength(_head);
		int length2 = GetLength(head2);

		int sub = abs(length1 - length2);
		 
		ListNode *LongList = _head;
		ListNode *ShortList = head2;

		if(length1 < length2)
			swap(LongList,ShortList);

		//����������sub��
		while(sub > 0)
		{
			LongList = LongList->_next;
			sub--;
		}

		while(LongList != NULL)
		{
			if(LongList->_data == ShortList->_data)
			{
				cout<<"������ǣ�"<<LongList->_data<<endl;
				return;
			}
			LongList = LongList->_next;
			ShortList = ShortList->_next;
		}

		cout<<"û�н���"<<endl;
	}
	int GetLength(ListNode *head)
	{
		int count = 0;
		while(head != NULL)
		{
			count++;
			head =head->_next;
		}
		return count;
	}
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
void testCross()
{
	List s1;
	s1.Push_Back(1);
	s1.Push_Back(2);
	s1.Push_Back(3);
	s1.Push_Back(4);
	s1.Push_Back(5);
	
	List s2;
	s2.Push_Back(2);
	s2.Push_Back(3);
	s2.Push_Back(4);
	s2.Push_Back(5);

	s1.Cross(s2.GetHead());
	s1.Cross_Better(s2.GetHead());

}
//7**********************��������ĸ���
struct _ListNode{            //����һ�����
	char data;
	struct _ListNode *next;
	struct _ListNode *rand;

	_ListNode(const char _data)
		:data(_data)
		,next(NULL)
		,rand(NULL)
	{}

};
void print_list(_ListNode *head)    //��ӡ���������Ԫ��
{
	_ListNode* cur = head;
	_ListNode* ran = head;
	while(cur != NULL){
		printf("%d->",cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
	while(ran != NULL){
		printf("rand :%d piont to %d\n",ran->data,ran->rand->data);
		ran = ran->next;
	}
}
_ListNode *Create_complex(char a,char b,char c)
{
	_ListNode *head = NULL;
	_ListNode *node1 = new _ListNode(a);
	_ListNode *node2 = new _ListNode(b);
	_ListNode *node3 = new _ListNode(c);
	head = node1;
	node1->next = node2;
	node2->next = node3;
	node1->rand = node3;
	node2->rand = node1;
	node3->rand = node2;
	return head;
}
_ListNode *Copy_List(_ListNode *head)
{
	_ListNode *newhead = NULL;
	_ListNode *newnode = NULL;
	_ListNode *cur = head;
	_ListNode *newhead_tail = NULL;
	while(cur != NULL){    //1->2->3====>1->1'->2->2'->3->3'
		newnode = new _ListNode(cur->data);
		newnode->next = cur->next;
		cur->next = newnode;
		cur = cur->next->next;
	}
	cur = head;
	while(cur != NULL){     //ָ����ȷ��rand��
		cur->next->rand = cur->rand->next;
		cur = cur->next->next;
	}
	//print_list(head);
	cur = head;         //�������
	newhead = cur->next;
	cur->next = cur->next->next;
	newhead_tail = head;
	cur = cur->next;
	while(cur != NULL){     //���������β�壬������ı�ָ��
		newhead_tail->next = cur->next;
		cur->next = cur->next->next;
		cur = cur->next;
	}
	return newhead;
}
void testComplexList()
{
	char a = 1;
	char b = 2;
	char c = 3;
	_ListNode *head = Create_complex(a,b,c);
    _ListNode *newhead = NULL;
	print_list(head);
	newhead = Copy_List(head);
	printf("the new list :\n");
	print_list(newhead); 
}
int main()
{
	//testPrintListReverse();
	//testDeleteNode();
	//testFindKNode();
	//testReverseList();
	//testMerge();
	//testCross();
	testComplexList();
	system("pause");
	return 0;
}

