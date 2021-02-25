#include<bits/stdc++.h>
using namespace std;


class node{
public:	
	int data;
	node *left;
	node *right;

	node(){
	left=right=NULL;
	}

	node (int d ){
	left=right=NULL;
	data=d;
	}


};


class binarytree{

   node *root;

public:
	    binarytree(){
	    	root=NULL;
	    }

 void insert(int);
 void preOrder();
 void preorder(node *);
 void preiterative();
 void initerative();

 void postiterative();

 

};

void binarytree::insert(int v){

	node *temp=new node(v);

	if(root==NULL)
		{root=temp;return;}
int i;
	
		node *ptr=root;
		
		cout<<" enter 0 for left and 1 for right of ( "<<ptr->data<<" ) : ";
		cin>>i;

		while(1)
	{ 

		if(i==0){

			if(ptr->left==NULL)
			{
 				ptr->left=temp;
 				break;	
			}
			else{
				cout<<" enter 0 for left and 1 for right of ( "<<ptr->left->data<<" ) : ";
				cin>>i;
				ptr=ptr->left;
			}



		}

		else if(i==1){

			if(ptr->right==NULL)
			{
 				ptr->right=temp;
 				break;	
			}
			else{
				cout<<" enter 0 for left and 1 for right of ( "<<ptr->right->data<<" ) : ";
				cin>>i;
				ptr=ptr->right;
			}


		}






	}




cout<<" \n ---- node inserted --- \n ";


}

void binarytree::preOrder(){
	 cout<<"\n preorder traversal : ";
        preorder(root);
        cout<<endl<<" i m here ";
}

void binarytree::preorder(node *ptr)
{
	if(ptr==NULL)
		return;
	cout<<ptr->data<<" ";
	preorder(ptr->left);
	preorder(ptr->right);
}

void binarytree::preiterative(){

	node *ptr=root;
    stack<node *>s;

	while(1){

       while(ptr)
       {
       	  cout<<ptr->data<<" ";
          s.push(ptr);
          
          ptr=ptr->left;

       }

       if(s.empty())
       	break;

       ptr=s.top();
       s.pop();
       ptr=ptr->right;


	}
}

void binarytree::initerative(){

	node *ptr=root;
    stack<node *>s;

	while(1){

       while(ptr)
       {
       	  
          s.push(ptr);
          
          ptr=ptr->left;

       }

       if(s.empty())
       	break;

       ptr=s.top();
       s.pop();
       cout<<ptr->data<<" ";
       ptr=ptr->right;


	}
}

void binarytree::postiterative(){

	node *ptr=root;

    stack<node *>s;
    stack<int>t;

   s.push(ptr);
	while(!s.empty()){
      
      ptr=s.top();
      s.pop();
      t.push(ptr->data);

      if(ptr->left!=NULL){s.push(ptr->left);}

      if(ptr->right!=NULL){s.push(ptr->right);}

	}

	while(!t.empty()){

		int k=t.top();
		cout<<k<<" ";
		t.pop();
	}
}



int main(){

 binarytree obj;
 int op;

 while(1){
    cout<<"\n ********************************* \n";
    cout<<" 1: insert \n ";
    cout<<" 2: display \n";

    cout<<" enter option : ";
    cin>>op;

    if(op==1)
    {
    	cout<<" enter value to insert : ";
    	int key;
    	cin>>key;

    	obj.insert(key);
    }
    else if(op==2)
    {
    	
    	obj.preiterative();
    	cout<<"\n ";
    	obj.preOrder();
    	cout<<"\n ";
    	obj.initerative();
    	cout<<"\n ";
    	obj.postiterative();
    	
    	
    }

    else{
    	break;
    }



 }




	return 0;
}