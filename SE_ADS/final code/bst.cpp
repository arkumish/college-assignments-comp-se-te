#include<bits/stdc++.h>

using namespace std;

class node{
public:
  string word;
  string mean;
  node *left;
  node *right;

  node(){
  	left=right=NULL;
  }

  node(string s , string d ){
  	left=right=NULL;

  	word=s;
  	mean=d;
  }


};

class bst{

	node *root;
public:
		bst(){
			root=NULL;
		}

public:
       void insert(string , string );
       void display();
       void inorder(node *);	
       void insertbst(int);	
       int search(string s);
       node *del(node*,string);
       void searchword();
       void checkdel();




};

void bst::insertbst(int flag){
    string s,m;int x=1;
	if(flag==1)
	{
		while(x>0){
		cout<<"\nenter word and meaning : \n";
		cin>>s;
		cin>>m;
		insert(s,m);
           cout<<"\n enter more (0/1) ";
           cin>>x;
	  }
	 } 

	if(flag==0){

		//cout<<" i was here ";
		ifstream fin;
		fin.open("d.txt");
		while(fin>>s>>m)
			insert(s,m);

		fin.close();
	}


}

void bst::insert(string s , string d){

 //cout<<" i was here ";
   node *temp=new node(s,d);
 	
 	if(root==NULL)
 	{
 		root=temp;
 		cout<<"------ root added ---";
 		return;

 	}

 	int i;

  node *ptr=root;

 	   if(ptr->word > temp->word)
 	   	i=0;
 	   else
 	   	i=1;

 	   while(1){
            
            if(i==0){
            	if(ptr->left==NULL)
            	{
            		ptr->left=temp;
            		break;
            	}
            	if(ptr->left->word > temp->word)
            		i=0;
            	else 
            		i=1;

            	ptr=ptr->left;
            }

            if(i==1){
            	if(ptr->right==NULL)
            	{
            		ptr->right=temp;
            		break;
            	}
            	if(ptr->right->word < temp->word)
            		i=1;
            	else 
            		i=0;

            	ptr=ptr->right;
            }




 	   }


 	   cout<<"\n  --- node added --- \n ";

}


void bst::display(){
	cout<<" ascending order list : \n";

	inorder(root);

}

void bst::inorder(node *ptr){

       if(ptr==NULL)
       	return;

       inorder(ptr->left);
       cout<<ptr->word<<" => "<<ptr->mean<<"\n";
       inorder(ptr->right);

}

void bst :: searchword(){
	cout<<" enter word to search : ";
	string s;
	cin>>s;

	int k=search(s);
}

int bst::search(string s){

	

	node *ptr=root;
	int cnt=0;

	while(ptr){

      if(ptr->word > s)
      {
      	ptr=ptr->left;
      	cnt++;
      }
      else if(ptr->word < s){
      	ptr=ptr->right;
      	cnt++;
      }
      else{
        cout<<"\n word found \n";
        cout<<"\n meaning of word is : "<<ptr->mean;
        cout<<"\n comparison required : "<<cnt<<endl;
        return 1; 

      }


	}
	cout<<" not found ";
	return 0;


}


void bst::checkdel(){
	cout<<"\n enter word to delete : ";
	string s;
	cin>>s;

	if(search(s)){
 
      root=del(root,s);

      if(root==NULL){
      	cout<<" dictionary khali";

      }
      else{
      	display();
      	cout<<" deleteion ok \n";
        
        cout<<"\n";
      }

	}
	else{
		cout<<" unable to delte ";

	}
}

node * bst :: del(node *ptr,string s){
if(ptr==NULL){
	return NULL;
}

 if(s > ptr->word){
 	ptr->right=del(ptr->right,s);
 }
 else if(s < ptr->word){
 	ptr->left = del(ptr->left,s);
 }

 else{
 cout<<" i am here ";
 if(ptr->left ==NULL && ptr->right ==NULL)
 {
 	delete ptr; 
 	ptr=NULL;            //no child
 	return ptr;

 }

 else if(ptr->left == NULL){
 	node *temp = ptr ->right;
 	delete ptr;
 	return temp;

 }
 
 else if ( ptr->right == NULL){
 	cout<<" i am here ";
 	node *temp = ptr->left;
 	delete ptr;
 	return temp;

 }
  else{

  	node *temp = ptr->right;

  	while(temp->left!=NULL){
  		temp=temp->left;
  	}

  	ptr->word=temp->word;
  	ptr->mean = temp->mean;

  	ptr->right = del(ptr->right , temp->word); 
  }

 }

return ptr;
}




int main(){

bst obj;

obj.insertbst(0);
obj.display();
//obj.searchword();
obj.searchword();
obj.checkdel();
//obj.checkdel();
obj.display();



return 0;


}