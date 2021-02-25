#include<bits/stdc++.h>
using namespace std;

struct node{
string word,meaning;
node *lt;
node *rt;
};


class bst{
node *root;

public:
	bst(){root=NULL;}
	void insert();
	void Display();
	void inorder(node*);
	node* search(string);
	void modify();
	void remove();
	void dispdel();
	node *del(node *,string);
	bool searchdelete(node *, string s);

};

void bst::insert()
{
//cout<<"\nEnter the word and meaning : "<<endl;
	string d,m;
	//cout<<"\nEnter the word : "<<endl;
	
	//cout<<"\nEnter its meaning : "<<endl;
	//cin>>m;

ifstream fin;
	fin.open("d.txt");
	while(fin>>d>>m){
	
node *temp =new node;
temp->word=d;
temp->meaning=m;
temp->lt=NULL;
temp->rt=NULL;

if(root==NULL)
     { root = temp;continue;}

node* p=new node;
p=root;
while(1)
 {
    if(temp->word<=p->word)
    {
    	if(p->lt==NULL)
    		{p->lt=temp;break;}
    	else
    		{p=p->lt;}
    }
    else
    {
        if(p->rt==NULL)
        	{p->rt=temp;break;}
        else
        	{ p=p->rt;}
    }



  }


}
}


void bst :: Display(){

cout<<" The elements are : \n";
inorder(root);

}

void bst::inorder(node *t){
if(t==NULL)
	return;
 inorder(t->lt);
 cout<<t->word<<" : "<<t->meaning<<"\n";
 inorder(t->rt);

}

node* bst::search(string d){

if(root==NULL)
{cout<<" empty tree "; return NULL;}

node *p=new node;
p=root;
int flag=0;
while(p)
  {  cout<<" -- ";
     if(d==p->word)
     	{cout<<"\n\t element exist "; flag=1;break;}
     else if(p->word<d)
        p=p->lt;
      else
      	p=p->rt;

  }

  if(flag==0)
  	{cout<<"\n\t sorry element not found "; return NULL;}
  else
  {
      return p;
  }



}

void bst:: modify()
{ 
	string d,t;
    cout<<" enter element to modify : ";
    cin>>d;

    node* check=search(d);
    if(check==NULL)
    {
    	cout<<" unable to perform modify operation "; return;
    }
    cout<<"\n\t enter new data : ";
    cin>>t;
    
    check->word=t;
    cout<<"\n Element modified ";
}


bool bst::searchdelete(node *root, string s){
while(root!=NULL)
{
if(s<root->word){
root=root->lt;
}
else if(s>root->word){
root=root->rt;
}
else{
return true;
}
}
return false;
}

void bst::dispdel(){
if(root==NULL)
cout<<"\n bst is EMPTY"<<endl;
else{
cout<<"\nEnter the word to delete"<<endl;
string s;
cin>>s;
if(searchdelete(root,s)){
root=del(root,s);
if(root==NULL){
cout<<"\nDeletion successful"<<endl;
cout<<"\nbst is now empty"<<endl;
}
else{
cout<<"\nDeletion successful"<<endl;
cout<<"\nbst after deletion "<<endl;
inorder(root);
}}
else
cout<<"\nNo word found"<<endl;
}
}

node *bst::del(node *n,string s){
if(n==NULL)
	return n;
else if(s<n->word){
	n->lt=del(n->lt,s);
	}
      else if(s>n->word){
	n->rt=del(n->rt,s);
	}
	   else{
		if(n->lt==NULL && n->rt==NULL){
		delete n;
		n=NULL;
		return n;
		}
		else if(n->lt==NULL){
		node *t=n;
		n=n->rt;
		delete t;
		return n;
		}
		        else if(n->rt==NULL){
			node *t=n;
			n=n->lt;
			delete t;
			return n;
		}
		
else{
	node *t=n->rt;
	while(t->lt!=NULL)
		t=t->lt;
		n->word=t->word;
		n->meaning=t->meaning;
		n->rt=del(n->rt,t->word);
		}}
	return n;
}


int main()
{
     bst bt;string s;
     char ans='y';
        while(ans=='y' || ans == 'Y')
        {
        cout<<"\nChoose one of the following.....\n1. Insert\n2. Display \n3. delete \n4. search\n5. Modify \n";
        int c;
        cin>>c;
        char ck='y';
        switch(c)
        {
                case 1:bt.insert();
                       break;
                case 2:bt.Display();
                       break;
                case 3: bt.dispdel();
                        break; 
                case 4:
						cout<<" enter element to search : ";
						cin>>s;
                       bt.search(s);  
                        break;    
                case 5:bt.modify(); 
                        break;
                //default : return;        
        }
        
        cout<<"\nWant to continue....(y/n)?";
        cin>>ans;
        }

	return 0;
}