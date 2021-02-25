#include<bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    node *right,*left;
    bool lt,rt;
    int flag;   

    node(int e){data = e;}                               
};


class tbt{

  node *root;
  node *dummy;

 public:
 	     tbt(){
            
             root =NULL;

 	     	dummy = new node(0);
 	     	dummy->left = dummy;
 	     	dummy ->right =dummy;
 	     	dummy ->lt = true;
 	     	dummy ->rt = false;
 	     }

 	  void insert(int );  
 	  node *insuccess(node *);
 	  void inorder(); 



};


void tbt :: insert(int ele){

     node *ptr = new node(ele);
     ptr ->lt=true;
     ptr ->rt =true;

     if(root == NULL){

     	root= ptr;
     	dummy->left = root;
     	dummy ->lt =false;
     	root ->left = dummy;
     	root ->right = dummy;

     	return;
     }

   node *temp = root;

     if(ele < temp ->data && temp->lt == true)
     {
     	ptr ->left = temp ->left;
     	ptr ->right = temp;

     	temp ->left =ptr;
     	temp ->lt =false;

     	return;

     }

     else if(ele > temp->data && temp ->rt ==true ){

     	ptr ->right = temp ->right;
     	ptr ->left = temp;

     	temp ->right = ptr;
     	temp ->rt = false;
     }
     else if(ele < temp ->data )
     	temp = temp->left;
     else
     	temp =temp->right;

}

node *tbt :: insuccess(node *temp){

	if(temp->rt==0)
        return temp->right;
    temp=temp->right;
    while(temp->lt==true)
        temp=temp->left;
    return temp;

   }
   
 void tbt::inorder(){

node *temp=root;
    if(root==NULL)
    {
        cout<<" Tree is Empty "<<endl;
        return;
    }

    while(temp->lt==false)
        temp=temp->left;

    while(temp!=dummy)
    {
        cout<<" "<<temp->data<<" lt="<<temp->lt<<" rt="<<temp->rt<<endl;
        if(temp->rt==false)
        {
            temp=temp->right;
            while(temp->lt==false)
                temp=temp->left;
        }
        else
            temp=temp->right;
    }
}   

int main(){


int ch,ele;
	tbt obj;
	do{
     cout<<"\n0.Exit";
     cout<<"\n1.Insert";
     cout<<"\n2.Display";
     cout<<"\n3.Deletion";
     cout<<"\nEnter the choice:";
     cin>>ch;

     switch(ch){

     	case 0:break;

     	case 1:cout<<"\nEnter the element :";
     	       cin>>ele;
     	       obj.insert(ele);
     	       break;

     	case 2:obj.inorder();
     	       break;       

     	case 3:cout<<"\nEnter the element to deleted:";
     	       cin>>ele;
     	       
     	       break;
     }
	}while(ch!=0);




}