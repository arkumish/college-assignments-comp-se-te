//binary threaded tree
#include<bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    node *right,*left;
    bool l,r;
    int flag	;                                  
};

class tbt
{
    node *head;
    node *root;
    node *postsuc(node *);
    node *parent(node *);
public:
    tbt()
    {
        head=new node;
        head->left=head;
        head->right=head;
        head->l=true;
        head->r=false;
        root=NULL;
    }
    void insert(int);
    void inorder();
    void preorder();
    void postorder();
    
    node *inSucc(node *);
    node *inPred(node *);
    node *caseA(node *,node *, node *);
    node *caseB(node *,node *, node *);
    node *caseC(node *,node *, node *);
    node *Delete(node *,int);
};

void tbt :: insert(int d)
{
    node *p=new node;
    p->data=d;
    p->r=true;
    p->l=true;
    if(root==NULL)
    {
        root=p;
        head->l=false;
        head->left=root;
        root->left=head;
        head->data=0;
        root->right=head;
        return;
    }

    node *temp=root;
    while(1)
    {
        if(temp->data > p->data && temp->l==true)
        {
            temp->l=false;
            p->left=temp->left;
            temp->left=p;
            p->right=temp;
            p->flag=0;
            return;
        }
        else if(temp->data < p->data && temp->r==true)
        {
            temp->r=false;
            p->right=temp->right;
            temp->right=p;
            p->left=temp;
            p->flag=1;
            return;
        }
        else if(temp->data > p->data)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
    }
}

void tbt :: inorder()
{
    node *temp=root;
    if(root==NULL)
    {
        cout<<" Tree is Empty "<<endl;
        return;
    }

    while(temp->l==false)
        temp=temp->left;

    while(temp!=head)
    {
        cout<<" "<<temp->data<<" lt="<<temp->l<<" rt="<<temp->r<<endl;
        if(temp->r==false)
        {
            temp=temp->right;
            while(temp->l==false)
                temp=temp->left;
        }
        else
            temp=temp->right;
    }
}

void tbt :: preorder()
{
    if(root==NULL)
    {
        cout<<" Tree is Empty"<<endl;
        return;
    }
    node *temp=root;
    while(temp!=head)
    {
        cout<<" "<<temp->data<<" leftt="<<temp->l<<" rightt="<<temp->r<<endl;
        if(temp->l==false)
        {
            temp=temp->left;
            continue;
        }
        else if(temp->r==false)
        {
            temp=temp->right;
            continue;
        }
        else if(temp->r==true)
        {
            while(temp!=head && temp->r==true)
                temp=temp->right;

            temp=temp->right;
        }
    }
}

node *tbt :: postsuc(node *temp)
{
    if(temp->flag==0)
    {
        temp=parent(temp);
        if(temp->r==true)
            return (temp);
        else
        {
            if(temp==temp->right)
                return (temp);
            temp=temp->right;
            while(temp->l==false || temp->r==false)
            {
                if(temp->l==false)
                    temp=temp->left;
                else
                    temp=temp->right;
            }
            return(temp);
        }
    }

    else
        return(parent(temp));
}

node *tbt :: parent(node *temp)
{
    if(temp->flag==0)
    {
        while(temp->r==false)
            temp=temp->right;

        return(temp->right);
    }
    else
    {
        while(temp->l==false)
            temp=temp->left;
        return(temp->left);
    }
}

void tbt :: postorder()
{
    if(root==NULL)
    {
        cout<<" Tree is Empty"<<endl;
        return;
    }
    node *temp=root;
    while(temp->l==false || temp->r==false)
    {
         if(temp->l==false)
            temp=temp->left;
        else
            temp=temp->right;
    }

    while(temp!=head)
    {
        cout<<" "<<temp->data<<" leftt="<<temp->l<<" rightt="<<temp->r<<endl;
        temp=postsuc(temp);
    }
}

node *tbt :: inSucc(node *ptr)
{
    if (ptr->r == true)
        return ptr->right;

    ptr = ptr -> right;
    while (ptr!=head && ptr->right)
        ptr = ptr->left;

    return ptr;
}

node *tbt :: inPred(node *ptr)
{
    if (ptr->l == true)
        return ptr->right;

    ptr = ptr->left;
    while (ptr->r)
        ptr = ptr->right;
    return ptr;
}






int main()
{
    tbt t;
    int choice;
    int d;
    while(1)
      {
        cout<<endl;
        cout<<" 1. Insertion"<<endl;
        cout<<" 2. Inorder Traversal"<<endl;
        cout<<" 3. Preorder Traversal"<<endl;
        cout<<" 4. Postorder Traversal"<<endl;
        cout<<" 5. Convert into Binary Search tree"<<endl;
        
        cout<<" 7.exit"<<endl;
        cout<<"\nEnter your choice:  ";
        cin>>choice;
        switch(choice)
        {
            case 1 : cout<<"Enter the Data : ";
                     cin>>d;
                     t.insert(d);
                     break;
            case 2 : cout<<endl<<"Inorder traversal "<<endl;
                     t.inorder();
                     cout<<endl;
                     break;
            case 3 : cout<<endl<<"Preorder traversal :";
                     t.preorder();
                     cout<<endl;
                     break;
            case 4 : cout<<endl<<"Postorder traversal : ";
                     t.postorder();
                     cout<<endl;
                     break;
            
                      
	    case 7 : exit (0);
                     break;
        }
    }
    return 0;
}









