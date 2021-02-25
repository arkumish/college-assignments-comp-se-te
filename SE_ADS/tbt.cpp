#include<bits/stdc++.h>
using namespace std;

struct node{
	int data;
	node *left;
	node *right;
	bool lt;
	bool rt;
   
};

class tbt{
	node *root;
	node *dummy;
	public:
		tbt(){
			dummy=newNode(INT_MAX);
			dummy->right=dummy;
			root=NULL;
		}

		node *newNode(int ele);
		void  insert(int ele);
		void inorder();
		node *inorder(node *);
		void del(int ele);
};

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

           		node *t=inorder(curr);
                int ans=t->data;
           		del(ans);
           		curr->data=ans;
           	}
           
             return;
           }

       }
    
}

node *tbt::inorder(node *temp){
   if(temp->rt)
        return temp->right;
    temp=temp->right;
    while(temp->lt!=true)
        temp=temp->left;
    return temp;
}

node *tbt::newNode(int ele){
	node *temp=new node;
	temp->data=ele;
	temp->left=NULL;
	temp->right=NULL;
	temp->lt=false;
	temp->rt=false;
	return temp;
} 


void tbt::inorder(){

node *temp=root;


while(temp!=dummy){

cout<<temp->data<<" ";
temp=inorder(temp);

}
}

void tbt::insert(int ele){
	if(root==NULL){
		root=newNode(ele);
		root->lt=true;
		root->rt=true;
		root->left=dummy;
		root->right=dummy;
		dummy->left=root;
		return ;
	}
  
   node *temp=root;
   while(1){
     if(temp->data <ele){
            if(temp->rt){
            	node *ptr=newNode(ele);
            	ptr->rt=true;
            	ptr->right=temp->right;
                temp->rt=false;
                temp->right=ptr;
                ptr->left=temp;
                ptr->lt=true;
               // cout<<" "<<temp->data<<" ";
            	break;
            }else
     	        temp=temp->right;
     }else{

         if(temp->lt){
            node *ptr=newNode(ele);
            ptr->lt=true;
            ptr->left=temp->left;
            temp->lt=false;
            temp->left=ptr;
            ptr->right=temp;
            ptr->rt=true;
            //cout<<" "<<temp->data<<" ";
            break;
         }else{
         	temp=temp->left;
         }

     }
   }
inorder();
cout<<endl<<" --- ";
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
     	       obj.del(ele);
     	       break;
     }
	}while(ch!=0);

}