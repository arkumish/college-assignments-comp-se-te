#include<bits/stdc++.h>
using namespace std;

class node{
public:
	string word;
	string mean;
	node *left;
	node *right;
	node(){
		mean = word ="";
		left = right = NULL;
	}
	node(string w, string m){
		word = w;
		mean = m;
		left = right = NULL;
	}
};

int cmp=0;

class dictionary{
	node *root;
	int searching(node *, string);
	int printing(node *);
    
    void mirror(node* ,node* );
public:
	node* deleteNode(node *, string);
	dictionary(){root=NULL;}
	void insert(string ,string );
	void searchword(string );
	void printAscending();
	void printDescending();
    void Delete(string );
};

void dictionary :: insert(string w, string m){
	if(root == NULL){
		node * temp = new node(w,m);
		root = temp;
		return;
	}
	
	node *ptr = root;
	while(1){
		string t = ptr -> word;
		if(w<t){
			if(ptr -> left == NULL){
				node *temp = new node(w,m);
				ptr -> left = temp;
				break;
			}
			else 
				ptr = ptr -> left;
		}
		else{
			if(ptr -> right == NULL){
				node *temp = new node(w,m);
				ptr -> right = temp;
				break;
			}
			else 
				ptr = ptr -> right;
	    }	
    }
} 

void dictionary :: searchword(string s){
    int val = searching(root,s);
	if(val==-1){
		cout << "OH BOY! WORD NOT IN DICTIONARY " << endl;
		return ;
	}
	cout << s << " FOUND " << endl;
	cout << "NO. OF COMPARISION ARE " << cmp << endl;
    cmp=0;
}

int dictionary :: searching(node *ptr, string s){
	if(ptr == NULL)
		return -1;
	string t = ptr -> word;
	if(s==t){
        cout << "WORD " << t << " FOUND WITH MEANING " << ptr -> mean << endl;
		return cmp;
    }
		
	if(s<t)
		searching(ptr -> left,s),cmp++;
	else
		searching(ptr -> right,s),cmp++;
}

void dictionary :: printAscending(){
	printing(root);
}

int dictionary :: printing(node *ptr){
	if(ptr == NULL)
		return 0;
	printing(ptr -> left);
	cout << ptr -> word << " " << ptr -> mean << endl;
	printing(ptr -> right);
}

void dictionary :: printDescending(){
	if (root == NULL)
		return;
	node *ptr2 = new node(root-> word,root->mean);
	node *ptr1 = root;
	mirror(ptr1,ptr2);
	printing(ptr2);
	cout << endl;
}

void dictionary :: mirror(node *ptr1,node *ptr2){
	if(ptr1 -> left!= NULL){
		node *temp = new  node(ptr1-> left-> word , ptr1-> left-> mean);
		ptr2 -> right = temp;
		mirror(ptr1->left, ptr2-> right);
	}
	if(ptr1 -> right!= NULL){
		node *temp = new  node(ptr1-> right-> word , ptr1-> right-> mean);
		ptr2 -> left = temp;
		mirror(ptr1-> right, ptr2-> left);
	}
}

void dictionary :: Delete(string s){
    root  =  deleteNode(root, s);
}

node* dictionary :: deleteNode(node* ptr,string s){
    if(ptr == NULL){
        return NULL;
    }
    if(s < ptr->word)
        ptr -> left  = deleteNode(ptr -> left , s);
    else if(s > ptr->word)
        ptr -> right = deleteNode(ptr -> right, s);
    else{
        if(ptr-> left == NULL){
            node *temp = ptr -> right;
            delete ptr;
            return temp;
        }
        else if(ptr-> right == NULL){
            node *temp = ptr -> left;
            delete ptr;
            return temp;
        }
        else{
            node *temp = ptr -> right;
            
            while(temp -> left != NULL)
                temp = temp -> left;         
            swap(ptr -> word, temp-> word);
            swap(ptr -> mean, temp-> mean);
            ptr -> right = deleteNode(ptr -> right, temp -> word);
        }
    }
    return ptr;
}

int main(){
	dictionary t;
    string a,b,c,d;
	int in; 
	do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. ENTER ENTRY " << endl;
		cout << "2. PRINTING IN ASCENDING ORDER " << endl;
		cout << "3. SEARCHING" << endl;
        cout << "4. DELETION " << endl;
        cout << "5. PRINT IN DESCENDING ORDER " << endl; 
        cout << "6. UPDATE " << endl;
        cout << "0. EXIT" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
				cout << "ENTER WORD AND ITS MEANING " << endl;
				cin >> a;
				cin.ignore();
				getline(cin,b);
				t.insert(a,b);
                break;
			case 2:
                t.printAscending();
                break;
			case 3:
                cout << "ENTER WORD NEED TO BE SEARCHED : "; 
                cin >> a;
                t.searchword(a);
                break;
            case 4:
                cout << "ENTER WORD NEED TO BE DELETED : "; 
                cin >> a;
                t.Delete(a);
                break;
            case 5:
            	t.printDescending();
                break;
            case 6:
                cout << "ENTER WORD NEED TO BE UPDATED : "; 
                cout << "ENTER OLD WORD :";
                cin >> a;
                t.Delete(a);
                cout << "ENTER NEW WORD AND ITS MEANING :" ;
                cin >> a >> b;
                t.insert(a,b);
                break;
            default:
                cout << "INVALID INPUT "<< endl;
        }
	}
    while(in);
    return 0;
}
