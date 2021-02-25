#include<bits/stdc++.h>
using namespace std;

class node{
public:
	int data;
	node *left;
	node *right;
	node(){
		left = right = NULL;
	}
	node(int d){
		left = right = NULL;
		data = d;
	}
};

class binaryTree{
	node *root;
	void preOrder(node *);
	void postOrder(node *);
	void inOrder(node *);
	int calcHeight(node *);
	void mirror(node*,node*);
	void copy(node*,node*);
	
public:
	binaryTree(){
		root = NULL;
	}
	void insert(int );
	int height();
	void inOrderTraversal();
	void inOrderIterative();
	void postOrderTraversal();
	void postOrderIterative();
	void preOrderTraversal();
	void preOrderIterative();
	void mirrorTree();
	void copyTree();
	void copyTreeDelete();
	node* copyanddelete(node*);
};


void binaryTree :: preOrderTraversal(){
	preOrder(root);
	cout << endl;
}

void binaryTree :: inOrderTraversal(){
	inOrder(root);
	cout << endl;
}

void binaryTree :: postOrderTraversal(){
	postOrder(root);
	cout << endl;
}

int binaryTree :: height(){
	return calcHeight(root);	
}

void binaryTree :: copyTree(){
	node *ptr2 = new node(root -> data);
	node *ptr1 = root;
	copy(ptr1,ptr2);
	inOrder(ptr2);
	cout << endl;
}

void binaryTree :: copyTreeDelete(){
	node *ptr = new node;
	node *ro = root;
	ptr = copyanddelete(ro);
	inOrder(ptr);
	cout << endl;
	root = NULL;
	
}

void binaryTree :: mirrorTree(){
	node *ptr2 = new node(root-> data);
	node *ptr1 = root;
	mirror(ptr1,ptr2);
	cout << "INORDER ";
	inOrder(ptr2);
	cout << endl;
	cout << "PREORDER ";
	preOrder(ptr2);
	cout << endl;
}

void binaryTree :: insert(int key){
	node *temp = new node(key);
	if(root == NULL){
		root = temp;	
	}
	else{
		cout << "Enter 0 for insertion in left and 1 for insertion in right of root " << root -> data << " : ";
		node *ptr = root;
		int in;
		cin >> in;
		while(1){
			if(!in){
				if(ptr -> left == NULL){
					ptr -> left = temp;
					break;
				}
				else{
					cout << "Enter 0 for insertion in left and 1 for insertion in right of " << (ptr -> left -> data)  << " : ";
					ptr = ptr -> left;
					cin >> in;
				}
			}
			else if(in){
				if(ptr -> right == NULL){
					ptr -> right = temp;
					 break;
				}
				else{
					cout << "Enter 0 for insertion in left and 1 for insertion in right of " << (ptr -> right -> data)  << " : ";
					ptr = ptr -> right;
					cin >> in;
				}
			}
		}
	}
	cout << "Node addition successful " << endl;			
}


void  binaryTree :: preOrderIterative(){
	stack <node *> s;
	node *ptr = root;
	while(ptr != NULL || !s.empty()){
		while(ptr!=NULL){
			s.push(ptr);
			cout << ptr -> data << " ";
			ptr = ptr -> left;
		}		
		ptr = s.top();
		s.pop();
		ptr = ptr -> right;
	}
	cout << endl;
}

void  binaryTree :: inOrderIterative(){
	stack <node *> s;
	node *ptr = root;
	while(ptr != NULL || !s.empty()){
		while(ptr!=NULL){
			s.push(ptr);
			ptr = ptr -> left;
		}
		ptr = s.top();
		s.pop();
		cout << ptr -> data << " ";
		ptr = ptr -> right;
	}
	cout << endl;
}

void binaryTree :: postOrderIterative(){
	stack <node *> s;
	stack <int > t;
	s.push(root);
	while(!s.empty()){
		node *ptr = s.top();
		s.pop();
		t.push(ptr -> data);
		if(ptr->left!=NULL)
			s.push(ptr -> left);
		if(ptr -> right!= NULL)
			s.push(ptr -> right);
	}
	while(!t.empty()){
		int val = t.top();
		t.pop();
		cout << val << " ";
	}
	cout << endl;
}

void binaryTree :: inOrder(node *ptr){
	if(ptr == NULL)
		return ;
	inOrder(ptr -> left);
	cout << ptr -> data << " ";
	inOrder(ptr -> right);
}

void binaryTree :: preOrder(node *ptr){
	if(ptr == NULL)
		return ;
	cout << ptr -> data << " ";
	preOrder(ptr -> left);
	preOrder(ptr -> right);
}

void binaryTree :: postOrder(node *ptr){
	if(ptr == NULL)
		return ;	
	postOrder(ptr -> left);
	postOrder(ptr -> right);
	cout << ptr -> data << " ";
}

int binaryTree :: calcHeight(node *ptr){
	if(ptr == NULL)
		return 0;
	return max(calcHeight(ptr->left),calcHeight(ptr->right))+1;	
}

void binaryTree :: mirror(node *ptr1,node *ptr2){
	if(ptr1 -> left!=NULL){
		node *temp = new  node(ptr1-> left-> data);
		ptr2 -> right = temp;
		mirror(ptr1->left, ptr2-> right);
	}
	if(ptr1 -> right!=NULL){
		node *temp = new  node(ptr1-> right -> data);
		ptr2 -> left = temp;
		mirror(ptr1-> right, ptr2-> left);
	}
}


void binaryTree :: copy(node* ptr1,node *ptr2){
	if(ptr1 -> left!=NULL){
		node *temp = new  node(ptr1-> left -> data);
		ptr2 -> left = temp;
		copy(ptr1->left, ptr2-> left);
	}
	if(ptr1 -> right!=NULL){
		node *temp = new  node(ptr1-> right -> data);
		ptr2 -> right = temp;
		copy(ptr1-> right, ptr2-> right);
	}
}

node* binaryTree :: copyanddelete(node *ptr){
	if(ptr == NULL) 
		return NULL;
	node *temp = new node;
	temp -> data = ptr -> data;
	temp -> left = copyanddelete(ptr -> left);
	temp -> right = copyanddelete(ptr -> right);
	delete ptr;
	return temp;
} 

int main(){
	binaryTree t;
	int in; 
	do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. Enter Node " << endl;
		cout << "2. Display inOrderTraversal" << endl;
		cout << "3. Display preOrderTraversal" << endl;
		cout << "4. Display postOrderTraversal" << endl;
		cout << "5. Height of Tree " << endl;
		cout << "6. Iterative Display inOrderTraversal" << endl;
		cout << "7. Iterative Display preOrderTraversal" << endl;
		cout << "8. Iterative Display postOrderTraversal" << endl;
		cout << "9. Copy Tree and display" << endl;
		cout << "10. Mirror Tree and display" << endl;
		cout << "11. Copy and Delete simultaneously " << endl;
		cout << "0. Exit " << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
				cout << "Enter Node's data need to get inserted ";
				int x; cin >> x;
				t.insert(x);
				break;
			case 2:
				t.inOrderTraversal();
				break;
			case 3:
				t.preOrderTraversal();
				break;
			case 4:
				t.postOrderTraversal();
				break;
			case 5:
				cout << "Height of Tree is " << t.height() << endl;
				break;
			case 6:
				t.inOrderIterative();
				break;
			case 7:
				t.preOrderIterative();
				break;
			case 8:
				t.postOrderIterative();
				break;
			case 9:
				t.copyTree();
				break;
			case 10:
				t.mirrorTree();
				break;
			case 11:
				t.copyTreeDelete();
			default:
				cout << "EXIT " << endl;			
		}
	}
	while(in);
}


