#include<bits/stdc++.h>
using namespace std;

class node{
public:
	int data;
	node *left;
	node *right;
	bool l;
	bool r;
	node(){
		data=0;
		left = right = NULL;
		l = r = false;
	}
	node(int d){
		data = d;
		left = right = NULL;
		l = r = false;
	}
};

class threadedTree{
	node *root;
	node *dummy;
	int k;
public:
	vector <node*> a;
	threadedTree(){
	    root = NULL;
		dummy = NULL;
	}
	void insert(int );
	void insertasBST(int );
	void Delete(int );
	void preOrder();
	void inOrder();
	void postOrder();
	void inOrderRecur(node*);
	void convertToThreaded();
	node* search(int, node* );
	node* lsubp(node *);
	node* lsubc(node *);
};

void threadedTree :: insertasBST(int w){
	if(root == NULL){
		node *temp = new node(w);
		root = temp;
		node *temp2 = new node(w);
		dummy = temp2;
		dummy -> left = root;
		dummy -> right = dummy;
		dummy -> l = true;
		dummy -> r = true;
		return;
	}
	
	node *ptr = root;
	while(1){
		int t = ptr -> data;
		if(w<t){
			if(ptr -> left == NULL){
				node *temp = new node(w);
				ptr -> left = temp;
				break;
			}
			else 
				ptr = ptr -> left;
		}
		else{
			if(ptr -> right == NULL){
				node *temp = new node(w);
				ptr -> right = temp;
				break;
			}
			else 
				ptr = ptr -> right;
	    }	
    }
} 

void threadedTree :: convertToThreaded(){
	inOrderRecur(root);
	int n = a.size();
	a[0] -> left = dummy;
	a[0] -> l = true;
	a[n-1] -> right = dummy;
	a[n-1] -> r = true;
	for(int i=0 ; i<a.size() ; i++){
		if(a[i]->left == NULL){
			a[i] -> left = a[i-1];
			a[i] -> l =true;
		}
		if(a[i]->right == NULL){
			a[i] -> right = a[i+1];
			a[i] -> r =true;
		}
	}
	inOrder();
	cout << endl;	
} 

void threadedTree :: inOrderRecur(node *ptr){
	if(ptr == NULL)
		return ;
	inOrderRecur(ptr -> left);
	a.push_back(ptr);
	inOrderRecur(ptr -> right);
}

void threadedTree :: insert(int n){
	if(root== NULL){
			node *temp = new node(n);
			root = temp;
			node *temp2 = new node(n);
			dummy = temp2;
			dummy -> left = root;
			dummy -> right = dummy;
			root -> right =	root -> left = dummy;
			root -> l = true;
			root -> r = true;
			dummy -> l = true;
			dummy -> r  = true;
			return ;
	}
	
	node *ptr = root;
	while(1){
		int t = ptr -> data;
		if(n<t){
			if(ptr -> l == true){
				node *temp = new node(n);
				temp -> left = ptr -> left;
				temp -> right = ptr;
				ptr -> left = temp;
				ptr -> l = false;
				temp -> l = true;
				temp -> r = true;
				break;
			}
			else
				ptr = ptr -> left;
		}
		else{
			if(ptr -> r == true){
				node *temp = new node(n);
				temp -> right = ptr -> right;
				temp -> left = ptr;
				ptr -> right = temp;
				ptr -> r = false;
				temp -> l = true;
				temp -> r = true;
				break;
			}
			else
				ptr = ptr -> right;
		}
	}
} 




void threadedTree :: inOrder(){ 
    node *ptr = root;
	if(root==NULL){
		cout << "TREE EMPTY " << endl;
		return;
	}
	
	while(ptr -> l != true)
		ptr = ptr -> left;
    while (ptr!=dummy) { 
		if (ptr -> l != true)
			ptr = ptr -> left;
		cout << ptr -> data << " ";
		if(ptr -> r == true){
			if(ptr -> right == dummy)
				return ;
			while(ptr -> r == true && ptr -> right!=dummy){
				ptr = ptr -> right;
				cout << ptr -> data << " ";
			}
		}
		ptr = ptr -> right;
	} 
    cout << endl;
}

void threadedTree :: preOrder(){ 
    node *ptr = root;
	if(root==NULL){
		cout << "TREE EMPTY " << endl;
		return;
	}
	while(ptr -> l != true){
		cout << ptr -> data << " ";
		ptr = ptr -> left;
	}
    while (ptr!=dummy) { 
		if (ptr -> l != true){
			cout << ptr -> data << " ";
			ptr = ptr -> left;
		}
		cout << ptr -> data << " ";
		if(ptr -> r == true){
			if(ptr -> right == dummy)
				return ;
			while(ptr -> r == true && ptr -> right!=dummy)
				ptr = ptr -> right;
		}
		ptr = ptr -> right;
	} 
    cout << endl;
}

void threadedTree :: postOrder()
{

}

void threadedTree :: Delete(int s){
   if(root==NULL)
   	return;
	int temp;
	node *p=root;
	node *c=root;
	cout<<c->data;
	node *t,*tc,*tp;
	while(1)
	{
		if(c->data==s)
		{
			if(p==c)
			{
				if(c->r==true&&c->l!=true)
				{
					root=c->left;
					dummy->left=root;
					root->right=dummy;
					delete p;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->r!=true&&c->l==true)
				{
					root=c->right;
					dummy->left=root;
					root->left=dummy;
					delete p;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->r==true&&c->l==true)
				{
					root=NULL;
					dummy->left=dummy;
					dummy->l=true;
					delete p;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->right->l==true)
				{
					swap(c->data,c->right->data);
					p=c;
					c=c->right;
				}
				else
				{
					tc=lsubc(c->right);
					tp=lsubp(c->right);
					swap(c->data,tc->data);
					p=tp;
					c=tc;
				}
			}
	else if(p->right==c)
			{	if(c->r==true&&c->l!=true)
				{
					p->right=c->left;
					p=p->right;
					while(p->r!=true)
				      p=p->right;
					p->right=c->right;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->r!=true&&c->l==true)
				{
					p->right=c->right;
					p=p->right;
					while(p->l!=true)
				      p=p->left;
					p->left=c->left;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}	
				else if(c->r==true&&c->l==true)
				{
					p->right=c->right;
					p->r=true;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->right->left==NULL)
				{
					swap(c->data,c->right->data);
					p=c;
					c=c->right;
				}
				else
				{
					tc=lsubc(c->right);
					tp=lsubp(c->right);
					swap(c->data,tc->data);
					p=tp;
					c=tc;
				}
			}
	else if(p->left==c)
			{	if(c->r==true&&c->l!=true)
				{
					p->left=c->left;
					p=p->left;
				   while(p->r!=true)
				      p=p->right;
				   p->right=c->right;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->r!=true&&c->l==true)
				{
					p->left=c->right;
					p=p->left;
					while(p->l!=true)
					   p=p->left;
					p->left=c->left;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}	
				else if(c->r==true&&c->l==true)
				{
					p->left=c->left;
					p->l=true;
					delete c;
					cout<<"Delete Complete"<<endl;
					return;
				}
				else if(c->right->l==true)
				{
					swap(c->data,c->right->data);
					p=c;
					c=c->right;
				}
				else
				{
					tc=lsubc(c->right);
					tp=lsubp(c->right);
					swap(c->data,tc->data);
 
					p=tp;
					c=tc;
				}
			}		
 
	}
	else if(s<c->data &&c->l!=true)
	{
		if(p==c)
		{
			c=c->left;
		}
		else
		{
			p=c;
			c=c->left;
		}
	}
	else if(s>c->data &&c->r!=true)
	{
		if(p==c)
		{
			c=c->right;
		}
		else
		{
			p=c;
			c=c->right;
		}
	}
	else
	{
		cout<<"Number not found!!"<<endl;
		return;
	}
	}
}

node * threadedTree :: lsubc(node *temp)
{
	while(1)
	{
	if(temp->l==true)
	return temp;
	temp=temp->left;
	}
}
node * threadedTree :: lsubp(node *temp)
{
	while(1)
	{
	if(temp->left->l==true)
	return temp;
	temp=temp->left;
	}
}
int main(){
	threadedTree t;
	int a;
	int in; 
	do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. INSERT" << endl;
		cout << "2. DELETE " << endl;
		cout << "3. PREORDER" << endl;
        cout << "4. POSTORDER " << endl;
        cout << "5. INORDER " << endl;
        cout << "6. ENTER AS BST AND MAKE THREADED " << endl;
        cout << "0. EXIT" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
				cout << " Enter Value of Node to be inserted : ";
				cin >> a;
				t.insert(a);
                break;
            case 2:
				cout << "Enter Value of Node to be deleted ";
				int k; cin >> k;
                 t.Delete(k);
                 cout << endl;
                break;
            case 3:
                t.preOrder();
                break;
            case 4:
               t.postOrder();
                break;
            case 5:
                t.inOrder();
                break;   
            case 6:
            	cout << " Enter Value of Node to be inserted : ";
				cin >> a;
                t.insertasBST(a);
                t.convertToThreaded();
                break; 
            default:
                cout << "INVALID INPUT "<< endl;
        }
	}
    while(in);
    return 0;
}
