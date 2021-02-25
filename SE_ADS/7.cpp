//AVL
#include<bits/stdc++.h>
using namespace std ; 
int cmp;
class node{
public:
	string word;
	string mean;
	node *left;
	node *right;
	node(){
		mean=word="";
		left = right = NULL;
	}
	node(string w,string m){
		word = w;
		mean = m;
		left = right = NULL;
	}
};

class dictionary{
	node* root;
	node* insert(node*, string , string);
	node* leftRotate(node* );
	node* rightRotate(node* );
	node* Delete(node*,string);
	node* inOrderSucc(node*);
	void inOrder(node* );
	void preOrder(node* );
	int height(node *);
	int balanceFactor(node *);
	int searching(node* , string);
public:
	dictionary(){
		root = NULL;
	}
	void input(string, string );
	void DeleteNode(string);
	void ascending();
	void printing();
	void Search(string);
};

void dictionary :: input(string a, string b){
	root = insert(root,a,b);
}

void dictionary :: DeleteNode(string val){
	root = Delete(root,val);
}

int dictionary :: balanceFactor(node *t){
	if(t==NULL)
		return 0;
	return height(t-> left) - height(t->right);
}

int dictionary :: height(node *ptr){
	if(ptr==NULL)
		return 0;
	return max(height(ptr->left) ,height(ptr->right)) + 1;
}

node* dictionary :: rightRotate(node* t){
	node* ptr1 = t -> left;
	node* ptr2 = ptr1 -> right;
	ptr1 -> right = t;
	t -> left = ptr2;
	return ptr1;
}

node* dictionary :: leftRotate(node* t){
	node* ptr1 = t -> right;
	node* ptr2 = ptr1 -> left;
	ptr1 -> left = t;
	t -> right = ptr2;
	return ptr1;
}

node* dictionary :: insert(node *r , string w, string m){
	if(r==NULL){
		node *temp = new node(w,m);
		r = temp;
		return r;
	}
	else if(w > r -> word)
		r -> right = insert(r -> right, w, m);
	else 
		r -> left = insert(r -> left, w, m);

	int bf = balanceFactor(r);

	if((bf==2)){
		if(balanceFactor(r-> left) == 1){
			cout << "RIGHT ROTATION AT " << r  -> word << endl ; 
			return rightRotate(r);
		}
		else{
			cout << "LEFT ROTATION AT " << r -> left -> word << endl ; 
			cout << "RIGHT ROTATION AT " << r -> word << endl ; 
			r -> left = leftRotate(r -> left);
			return rightRotate(r);
		}
	}
	else if((bf==-2)){
		if(balanceFactor(r-> right) == -1){
			cout << "LEFT ROTATION AT " << r  -> word << endl ; 
			return leftRotate(r);
		}
		else{
			cout << "RIGHT ROTATION AT " << r -> right -> word << endl ; 
			cout << "LEFT ROTATION AT " << r -> word << endl ;
			r -> right = rightRotate(r -> right);
			return leftRotate(r);
		}
	}
	return r;
}

node* dictionary :: inOrderSucc(node* ptr) 
{ 
    node* current = ptr; 
    while (current->left != NULL) 
        current = current->left; 
    return current; 
} 

void dictionary :: Search(string w){
	cmp = 1;
        int p = searching(root,w);
	if(p==-1){
		cout << "OH BOY! WORD NOT IN DICTIONARY " << endl;
		return ;
	}
	cout << w << " FOUND " << endl;
	cout << "NO. OF COMPARISION ARE " << cmp << endl;
}

int dictionary :: searching(node* r , string w){
	if(r == NULL)
		return -1;
	string t = r -> word;
	if(w==t){
		return cmp;
    	}
	if(w<t)
		searching(r -> left,w),cmp++;
	else
		searching(r -> right,w),cmp++;
}

node* dictionary :: Delete(node* r, string w){
	if(r==NULL)
		return r;
	
	if(w > r -> word)
		r -> right = Delete(r -> right, w);
	else if(w < r -> word)
		r -> left = Delete(r -> left, w);
	else{
		if(r -> left == NULL || r -> right == NULL){
			node * temp = new node;
			if(r -> left == NULL)
				temp = r -> right;
			else if(r -> right == NULL)
				temp = r ->left;

			if(temp==NULL){
					temp = r;
					r = NULL;
					delete temp;
			}
			else{
				r ->left = temp -> left;
				r ->right = temp -> right;
				r -> word = temp -> word;
				r -> mean = temp -> word;
				delete temp;
			}
		}
		else{
			node *temp = inOrderSucc(r -> right);
			swap(r -> word,temp -> word);
			swap(r -> mean,temp -> mean);
			r -> right = Delete(r -> right, temp -> word);
		}
	}
	if(r == NULL)
		return r;
		
	int bf = balanceFactor(r);

	if((bf==2)){
		if(balanceFactor(r-> left) >=0){
			cout << "RIGHT ROTATION AT " << r -> word << endl ; 
			return rightRotate(r);
		}
		else{
			cout << "LEFT ROTATION AT " << r -> left -> word << endl ; 
			cout << "RIGHT ROTATION AT " << r -> word << endl ; 
			r -> left = leftRotate(r -> left);
			return rightRotate(r);
		}
	}
	else if((bf==-2)){
		if(balanceFactor(r-> right) <=0){
			cout << "LEFT ROTATION AT " << r -> word << endl ;
			return leftRotate(r);
		}
		else{
			cout << "RIGHT ROTATION AT " << r -> right -> word << endl ; 
			cout << "LEFT ROTATION AT " << r -> word << endl ; 
			r -> right = rightRotate(r -> right);
			return leftRotate(r);
		}
	}
	return r;
}
void dictionary :: printing(){
	if(root == NULL){
		cout << "EMPTY TREE " << endl;
		return;
	}
	preOrder(root);
	cout << endl;
}

void dictionary :: ascending(){
	if(root == NULL){
		cout << "EMPTY TREE " << endl;
		return;
	}
	inOrder(root);
	cout << endl;
}

void dictionary :: inOrder(node * ptr){
	if(ptr==NULL)
		return ;
	inOrder(ptr -> left);
	cout << "WORD : " << ptr -> word << " MEAN: " << ptr -> mean << endl;
	inOrder(ptr -> right);
}

void dictionary :: preOrder(node * ptr){
	if(ptr==NULL)
		return ;
	cout << "WORD : " << ptr -> word << " MEAN: " << ptr -> mean << endl; 
	preOrder(ptr -> left);
	preOrder(ptr -> right);
}

int main(){
    int in; 
    dictionary t;
    string a,b; 
    do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. ENTER INPUT " << endl;
		cout << "2. DELETE " << endl;
		cout << "3. SEARCH AND ITS COMPARISIONS" << endl;
		cout << "4. ASCENDING ORDER " << endl;
		cout << "5. PRE ORDER" << endl;
        	cout << "0. EXIT" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
				cout << "ENTER VALUE OF WORD AND MEANING: ";
				 cin >>a >>b;
                		t.input(a,b);
                		break;
			case 2:
				cout << "ENTER WORD TO BE DELETED : ";
				cin >> a;
				t.DeleteNode(a);
                		break;
			case 3:
				cout << "ENTER WORD TO BE SEARCHED : ";
				cin >> a;
				t.Search(a);
				break;
			case 4:
				t.ascending();
				break;
			case 5:
				t.printing();
				break;
            		default:
                		cout << "END" << endl;
        	}
	}
    while(in);
}

