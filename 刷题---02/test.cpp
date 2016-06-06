#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<queue>
#include<stack>
using namespace std;

/******************二叉树的题目*********************/

struct BinaryTreeNode{
	char _data;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;

	BinaryTreeNode(int data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

class BinaryTree{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const char *a,size_t size)  //用先根遍历的方法创建数组
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a,size,index);
	}
	
	~BinaryTree()
	{
		_Destroy(_root);
	}
//1********************根据前序和中序遍历的结果重建二叉树
	void ReBuildTree(char* preorder,char* inorder)
	{
		assert(preorder);
		assert(inorder);
		assert(strlen(preorder) == strlen(inorder));
		int length = strlen(preorder);

		_root = _ReBuildTree(preorder,preorder+length-1,inorder,inorder+length-1);
	}

	BinaryTreeNode * _ReBuildTree(char* &prestart,char *preend,char *instart,char *inend)
	{

		BinaryTreeNode *root = new BinaryTreeNode(*prestart);
		if(inend == instart)
		{
			return root;
		}

		char *_instart = instart;
		char *tmproot = NULL;
		while(_instart <= inend)   //寻找根节点
		{
			if(*_instart == *prestart)
			{
				tmproot = _instart;
				break;
			}
			_instart++;
		}

		if(tmproot != NULL && preend - prestart >= 0)
			root->_left = _ReBuildTree(++prestart,preend,instart,tmproot-1);

		if(tmproot != NULL && preend - prestart >= 0)
 			root->_right = _ReBuildTree(++prestart,preend,tmproot+1,inend);

		return root;
	}
	
//2********************从上往下打印二叉树（层序遍历）
	void LevelOrder()
	{
		_LevelOrder(_root);
		cout<<endl;
	}
	void _LevelOrder(BinaryTreeNode *root)
	{
		if(root == NULL){
			cout<<"NULL";
			return;
		}
		queue<BinaryTreeNode *> s;
		s.push(root);
		while(!s.empty()){
			BinaryTreeNode *tmp = s.front();
			cout<<tmp->_data<<" ";
			s.pop();
			if(tmp->_left != NULL){
				s.push(tmp->_left);
			}
			if(tmp->_right != NULL){
				s.push(tmp->_right);
			}
		}
	}

//3********************二叉树的后序遍历
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}

	void _PostOrder(BinaryTreeNode *root)
	{
		if(root == NULL){
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	//非递归实现
	void PostOrder_NonR()
	{
		stack<BinaryTreeNode *> s;
		BinaryTreeNode *cur = _root;
		BinaryTreeNode *PreVisited = NULL;
		if(_root == NULL){
			return;
		}
		while(cur || !s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode *top = s.top();
			if(top->_right == NULL || top->_right == PreVisited){
				cout<<top->_data<<" ";
				s.pop();
				PreVisited = top;
			}else{
		        cur = top->_right;
			}
		}
		cout<<endl;
	}

//4********************二叉树的深度
	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t _Depth(BinaryTreeNode *root)
	{
		if(root == NULL)
			return 0;
		size_t depth_l = _Depth(root->_left);
		size_t depth_r = _Depth(root->_right);

		return depth_l > depth_r ? depth_l+1 : depth_r+1;	

	}

//5********************判断二叉树是否为平衡二叉树
//低效的解法
	bool Banlance()
	{
		return _Banlance(_root);
	}
	bool _Banlance(BinaryTreeNode *root)
	{
		if(root == NULL)
			return true;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);
		int bf = abs(left - right);
		if(bf > 1)
			return false;
	
		return _Banlance(root->_left) && _Banlance(root->_right);
	}


//更高效的解法
	bool IsBanlance()
	{
		int depth = 0;
		return _IsBanlance(_root,&depth);
	}
	bool _IsBanlance(BinaryTreeNode *root,int *depth)
	{
		if(root == NULL)
		{
			depth = 0;
			return true;
		}
		int left;
		int right;
		if(_IsBanlance(root->_left,&left) && _IsBanlance(root->_right,&right))
		{
			if(abs(left - right) <= 1)
			{
				*depth = left > right ? left+1 : right+1;
				return true;
			}
		}
		return false;
	}

//6********************二叉树的镜像
	void Mirror(BinaryTreeNode * root)
	{
		if(NULL == root || (root->_left == NULL && root->_right == NULL))
			return;

		BinaryTreeNode *tmp = root->_left;
		root->_left = root->_right;
		root->_right = tmp;

		Mirror(root->_left);
		Mirror(root->_right);

	}

	BinaryTreeNode *GetRoot()
	{
		return _root;
	}

//7********************二叉中和位某一值的路径
	//路径是指从根节点到叶节点经过的结点

	void FindPath(int value)
	{
		vector<BinaryTreeNode *> path;
		int curvalue = 0;
		_FindPath(_root,value,path,curvalue);
	}
	void _FindPath(BinaryTreeNode *root,int value,vector<BinaryTreeNode *> &path,int curvalue)
	{
		if(root != NULL)
		{
			path.push_back(root);
			curvalue += root->_data;
		}

		if(curvalue == value && (root->_left == NULL && root->_right == NULL))  //如果top是叶节点
		{
			cout<<"the path:  ";
			vector<BinaryTreeNode *>::iterator it = path.begin();
			while(it != path.end())
			{
				cout<<(*it)->_data<<" ";
				it++;
			}
			path.pop_back();
			return;
			
		}
			
		else if(root->_left == NULL && root->_right == NULL)  //top是叶节点，但value值不相同
		{	
			path.pop_back();
			curvalue -= root->_data;
			return;
		}
			
		else      //top不是叶节点
		{
			if(root->_left != NULL)
			{
				_FindPath(root->_left,value,path,curvalue);
			}
			if(root->_right != NULL)
			{
				_FindPath(root->_right,value,path,curvalue);
			}
		}
		
	}

//8********************树的子结构
	bool HassubTree(BinaryTreeNode *root2)
	{
		return _HassubTree(_root,root2);
	}
	bool _HassubTree(BinaryTreeNode *root1,BinaryTreeNode *root2)   
	{
		//寻找root1中值==root2根节点的值
		bool result = false;
		if(root1 != NULL && root2 != NULL)
		{
			if(root1->_data == root2->_data)
				result = HasSameTree(root1,root2);
			if(result == false)
				result = _HassubTree(root1->_left,root2);
			if(result == false)
				result = _HassubTree(root1->_left,root2);
		}
		return result;
	}

	bool HasSameTree(BinaryTreeNode *root1,BinaryTreeNode *root2)
	{
		//判断结构是否相同
		if(root2 == NULL)
			return true;

		if(root1->_data == root2->_data)
			return HasSameTree(root1->_left,root2->_left) && HasSameTree(root1->_right,root2->_right);

		else
			return false;
	}

//9********************二叉搜索树与双向链表
	
	BinaryTreeNode* Convert()
	{
		BinaryTreeNode *LastNode = NULL;

		_Convert(_root,LastNode);

		//返回链表的头结点
		BinaryTreeNode *pHead = LastNode;
		while(LastNode != NULL && pHead->_left != NULL)
			pHead = pHead->_left;

		return pHead;
	}

	void _Convert(BinaryTreeNode *root,BinaryTreeNode *&LastNode)
	{
		if(root == NULL)
			return;

		BinaryTreeNode *curnode = root;

		if(curnode->_left != NULL)
			_Convert(root->_left,LastNode);

		curnode->_left = LastNode;
		if(LastNode != NULL)
			LastNode->_right = curnode;

		LastNode = curnode;
		
		if(curnode->_right != NULL)
			_Convert(root->_right,LastNode);
	}

//10********************树中两个结点的最低公共祖先
	bool IsInTree(BinaryTreeNode *root,BinaryTreeNode *x)
	{
		if(root == NULL)
			return false;
		if(root == x)
			return true;

		return IsInTree(root->_left,x) || IsInTree(root->_right,x);
	}

	BinaryTreeNode* GetAncestor(BinaryTreeNode *root,BinaryTreeNode *x1,BinaryTreeNode *x2)
	{
		if(root == NULL)
			return NULL;
    
		if(( root == x1 && IsInTree(root,x2))  ||  (root == x2 && IsInTree(root,x1)) )  
			return root;

	
		bool x1InLeft = IsInTree(root->_left,x1);    
		bool x1InRight = IsInTree(root->_right,x1);
		bool x2InLeft = IsInTree(root->_left,x2);
		bool x2InRight = IsInTree(root->_right,x2);

		if((x1InLeft && x2InRight) || (x1InRight && x2InLeft))
			return root;
		if(x1InLeft && x2InLeft)
			return GetAncestor(root->_left,x1,x2);
		if(x1InRight && x2InRight)
			return GetAncestor(root->_right,x1,x2);
		else
			return NULL;
	}

	BinaryTreeNode *Find(const char ch)
	{
		return _Find(_root,ch);
	}
	BinaryTreeNode *_Find(BinaryTreeNode *root,const char ch)
	{
		if(root->_data == ch)
			return root;
		
		if(root == NULL)
			return NULL;

		BinaryTreeNode *left = _Find(root->_left,ch);

		if(NULL != left) 
			return left;
		else                      //如果左树为空，就去右树找
			return _Find(root->_right,ch);
	}

protected:
	BinaryTreeNode *_CreateBinaryTree(const char *a,size_t size,size_t & index)
	{
		BinaryTreeNode *root = NULL;
		if(index < size && a[index] != '#'){
			root = new BinaryTreeNode(a[index]);
			root->_left = _CreateBinaryTree(a,size,++index);
			root->_right = _CreateBinaryTree(a,size,++index);
		}
		return root;
	}
	
	void _Destroy(BinaryTreeNode * &root)
	{
		if(root == NULL){
			return;
		}                               
		if(root->_left == NULL && root->_right == NULL){    //!!!
			delete root;
			root = NULL;
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}                   

private:
	BinaryTreeNode *_root;
};


	
void testReBuildTree()
{
	BinaryTree bt;
	char preorder[] = "123456";
	char inorder[] = "324165";
	bt.ReBuildTree(preorder,inorder);
	bt.LevelOrder();
}

void testLevelOrder()
{
	//char *a = "123##4##56";
	char *a = "12#3##45#6#7##8";

	//BinaryTree bt(a,10);
	BinaryTree bt(a,15);

	bt.LevelOrder();
}

void testPostOrder()
{
	char *a = "123##4##56";

	BinaryTree bt(a,10);
	
	bt.PostOrder();
	bt.PostOrder_NonR();
}

void testDepth()
{
	char *a = "123##4##56";

	BinaryTree bt(a,10);
	
	cout<<bt.Depth();
}
void testBalance()
{
	char *a = "123##4##56";

	BinaryTree bt(a,10);
	
	cout<<bt.Banlance();
	cout<<bt.IsBanlance();
}

void testMirror()
{
	char *a = "123##4##56";

	BinaryTree bt(a,10);
	
	bt.Mirror(bt.GetRoot());

	bt.LevelOrder();
}

void testAncestor()
{
	char *a = "123##4##56";

	BinaryTree bt(a,10);

	BinaryTreeNode *x1 = bt.Find('4');
	BinaryTreeNode *x2 = bt.Find('3');

	BinaryTreeNode *ret = bt.GetAncestor(bt.GetRoot(),x1,x2);
	cout<<ret->_data<<endl;
}
void testFindPath()
{
	char *a = "123##3##56";

	BinaryTree bt(a,10);

	bt.FindPath(150);
}
void testConvert()
{
	char *a = "976##8";

	BinaryTree bt(a,6);

	BinaryTreeNode *head = bt.Convert();

	while(head != NULL)
	{
		cout<<head->_data;
		head = head->_right;
	}
}
void testHassubTree()
{
	char *a = "123##4##56";
	BinaryTree bt(a,10);

	/*char *a1 = "123";
	BinaryTree b(a1,3);*/
	/*char *a1 = "124";
	BinaryTree b(a1,3);*/
	char *a1 = "123##4";
	BinaryTree b(a1,6);

	cout<<bt.HassubTree(b.GetRoot());
}
int main()
{
	testReBuildTree();
	//testLevelOrder();
	//testPostOrder();
	//testDepth();
	//testBalance();
	//testMirror();
	//testAncestor();
	//testFindPath();
	//testHassubTree();
	//testConvert();
	system("pause");
	return 0;
}