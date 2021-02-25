//insertion and deletion 

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
 	  void del(int);



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

	if(temp->rt)
        return temp->right;
    temp=temp->right;
    while(temp->lt!=1)
        temp=temp->left;
    return temp;

   }
   
 void tbt::inorder(){

 node *temp=dummy->left;
    //cout<<"Me chala hun 1"<<endl;
    while(temp->lt!=1)
        temp=temp->left;
    //cout<<"Leftmost element "<<temp->data<<endl;
    while(temp != dummy){
        cout<<temp->data<<" ";
	temp=insuccess(temp);
    }
    cout<<endl;
}   

void tbt::del(int ele){
	node *curr=root;
    node *prev=dummy;
    
   
    while(1){
       if(curr->data < ele){
         prev=curr;
       	 curr=curr->right;
       }else if(curr->data >ele){
       	prev=curr;
       	curr=curr->left;
       }else{

           if(curr->lt && curr->rt){
           	if(curr==prev->left){
           		prev->lt=true;
           		prev->left=curr->left;
           	}else {
           		prev->rt=true;
           		prev->right=curr->right;
           	}
           	delete curr;

           }else if(curr ->lt==false && curr->rt==true ){
           	 prev=curr->left;	
           	 delete curr;
           	}else if(curr->rt==false && curr->lt==true){
           		prev=curr->right;
           		delete curr;
           	}else{

           		node *t=insuccess(curr);
                int ans=t->data;
           		del(ans);
           		curr->data=ans;
           	}
           
             return;
           }

       }
    
}

//-------------------------------
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
     	       obj.del(ele);
     	       break;
     }
	}while(ch!=0);




}