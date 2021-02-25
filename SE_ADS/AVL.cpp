
#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;

char src[20] = "avl.txt";

struct node
{
	string data;
	int bf;
	node *left;
	node *right;
	node() { left = right = NULL; bf = 0; }
	node(string dt):node() { data = dt; }

};

class AVL
{
	node *root;

	//methods
	node* _add(node*,string);
	void _inorder(node*);
	void _srch(node* t,string key,int cmp);
	int _ht(node*);
	int BFactor(node*);
	node* _del(node*,string);
	node* rightRotation(node*);
	node* leftRotation(node*);

public:
	AVL() { root = NULL; }
	//methods
	void AddNode(string);
	void Inorder() { _inorder(root); }
	int Height() { return _ht(root); }
	void Search(string key) { _srch(root,key,0); }
	void Delete(string data)
	{
		if (data == "") return;
		root = _del(root,data);
	}

};

//------------------------FILE CREATE---------------------
AVL* FileCreate(string fname)
{
	AVL *temp = NULL;
	ifstream fin(fname.c_str());
	if (!fin)
	{
		cerr << "ERROR IN OPENING FILE!" << endl;
		return temp;
	}

	int i = 0;
	temp = new AVL;
	while (!fin.eof())
	{
		cout << ++i<<endl;
		string data;
		fin >> data;
		temp->AddNode(data);
	}
	return temp;
}


int main()
{
	AVL *t = FileCreate("words.txt");

	char ch = 'y';
	while (ch != 'n')
	{

		//cin >> ch;
		//t->Inorder();
		cout<<"\nHEIGHT: "<<t->Height()<<endl;
		string s;
		cout << "\nEnter Key: "; cin >> s;
		t->Search(s);
		//t->Delete(s);
	}

	return 0;
}

//--------------//
//	  AVL      //
//------------//
void AVL::AddNode(string data)
{
	root=_add(root,data);
}

node* AVL:: _add(node *t,string data)
{
	if (t == NULL)
		return new node(data);

	if (data < t->data)
		t->left = _add(t->left,data);
	else
		t->right = _add(t->right,data);
	
	t->bf=BFactor(t);
	//if unbalanced then balance
	if (t->bf == 2)//node is inserted in left
	{
		if (t->left->bf == -1)//right subtree of left child(RL)
			t->left = leftRotation(t->left);
		t = rightRotation(t);
	}

	else if (t->bf == -2)//node is inserted in right
	{
		if (t->right->bf==1)//left subtree of right child(LR)
			t->right = rightRotation(t->right);
		t = leftRotation(t);
	}
	
	return t;
}

//````````````
//	ROTATIONS
//____________
//right
node* AVL::rightRotation(node* t)
{
	node *temp = t->left;
	t->left = temp->right;
	temp->right = t;
	//update balance factor
	t->bf = BFactor(t);
	temp->bf = BFactor(temp);
	return temp;
}
//left
node* AVL::leftRotation(node *t)
{
	node *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	//update balance factor
	t->bf = BFactor(t);
	temp->bf = BFactor(temp);
	return temp;
}

//Balance Factor
int AVL::BFactor(node *t)
{
	if (t == NULL) return 0;

	return _ht(t->left) - _ht(t->right);
}

//height
int AVL::_ht(node *t)
{
	if (t == NULL) return 0;

	return max(_ht(t->left) , _ht(t->right)) + 1;
}


//delete
node* AVL:: _del(node* t,string key)
{
	if (t == NULL)  return t;

	else if (key < t->data)
	{
		t->left = _del(t->left, key);
		
		t->bf = BFactor(t);
		if (t->bf == -2)//
		{
			if(t->right->bf==1)
			t->right = rightRotation(t->right);

			t = leftRotation(t);
		}
		return t;
	}
	else if (key > t->data)
	{
		t->right = _del(t->right, key);
		
		t->bf = BFactor(t);
		if (t->bf == 2)//
		{
			if(t->left->bf==-1)
			t->left = leftRotation(t->left);

			t = rightRotation(t);
		}
		return t;
	}
	//we reached to the node to be deleted
	//one or no child
	if (!t->left)//t->left==NULL
	{
		node *temp = t;
		t = t->right;
		delete temp;
	}
	else if (!t->right)//t->right==NULL
	{
		node *temp = t;
		t = t->left;
		delete temp;
	}

	//two child
	else
	{
		node *succ = t->right;
		while (succ->left)
		{
			succ = succ->left;
		}
		t->data = succ->data;
		t->right = _del(t->right,succ->data);
	}

	return t;
}

void AVL::_srch(node* t, string key, int cmp)
{
	if (t == NULL)
	{
		cerr << "ENTRYY NOT FOUND" << endl;
		cerr << "No. of Comparisons: " << cmp << endl;
		return;
	}

	if (key < t->data)
		_srch(t->left, key, cmp + 1);
	else if (key > t->data)
		_srch(t->right, key, cmp + 1);
	else
	{
		cout << "ENTRY FOUND" << endl;
		cerr << "No. of Comparisons: " << cmp << endl;
	}
}


//Inorder
void AVL::_inorder(node *t)
{
	if (t == NULL) return;

	//if(t->left)
	_inorder(t->left);

	cout << t->data << " ";

	//if(t->right)
	_inorder(t->right);
}

