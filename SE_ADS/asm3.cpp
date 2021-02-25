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
    void bst();
    int BST();
    void Delete_start();
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

node * tbt :: caseA(node *root,node *par, node *ptr)
{
    if (par == head)         //root
        root = NULL;
    else if (ptr == par->left)     //left of parent
    {
        par->l = true;
        par->left = ptr->left;
    }
    else
    {
        par->r = true;
        par->right = ptr->right;
    }
    free(ptr);
    return root;
}

node * tbt :: caseB(node *root,node *par,node *ptr)
{
    node *child;

    if (ptr->l == false)   //left child exist
        child = ptr->left;

    else
        child = ptr->right;     //right child exist

    if (par == head)
        {
            root = child;
        }
    else if (ptr == par->left)
        par->left = child;
    else
        par->right = child;

    node *s = inSucc(ptr);
    node *p = inPred(ptr);

    // If ptr has left subtree.
    if (ptr->l == false)
        p->right = s;

    // If ptr has right subtree.
    else
    {
        if (ptr->r == false)
            s->left = p;
    }

    free(ptr);
    return root;
}

node *tbt :: caseC(node *root,node *par,node *ptr)
{
  
    node *parsucc = ptr;
    node *succ = ptr -> right;

    // Find leftmost child of successor
    while (succ->left != head && succ->l!=true)
    {
        parsucc = succ;
        succ = succ -> left;
    }

    ptr->data = succ->data;

    if (succ->l == true && succ->r == true)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);

    return root;
}

void tbt :: Delete_start()
{
    int key;
    cout<<" Enter the value to be Delete : ";
    cin>>key;
    root = Delete(root,key);
}

node *tbt :: Delete(node* root, int key)
{
    node *par = head, *ptr = root;
    int found = 0;

    while (ptr != head)
    {
        if (key == ptr->data)
        {
            found = 1;
            break;
        }
        par = ptr;
        if (key < ptr->data)
        {
            if (ptr->l == false)
                ptr = ptr -> left;
            else
                break;
        }
        else
        {
            if (ptr->r == false)
                ptr = ptr->right;
            else
                break;
        }
    }
    if (found == 0)
        cout<<"Key Not Present"<<endl;

    // Two Children
    else if (ptr->l == false && ptr->r == false)
        root = caseC(root, par, ptr);

    // Only Left Child
    else if (ptr->l == false)
        root = caseB(root, par, ptr);

    // Only Right Child
    else if (ptr->r == false)
        root = caseB(root, par, ptr);

    // No child
    else
        root = caseA(root, par, ptr);

    return root;
}

int tbt :: BST()
{
    cout<<endl<<"Binary Tree"<<endl;
    int num;
    cout<<endl<<"Enter no. of nodes: ";
    cin>>num;
    root=new node;
    cout<<"Enter the root : ";
    cin>>root->data;
    root->left=NULL;
    root->right=NULL;

    for(int i=0;i<num-1;++i)
    {
        node *temp=root;
        node *p=new node;
        cout<<"Enter the data : ";
        cin>>p->data;
        p->left=NULL;
        p->right=NULL;
        while(1)
        {
            if(temp->left==NULL && temp->data>p->data)
            {
                p->flag=0;
                temp->left=p;
                break;
            }
            else if(temp->right==NULL && temp->data<p->data)
            {
                p->flag=1;
                temp->right=p;
                break;
            }
            else if(temp->data==p->data)
            {
                cout<<"Number Already Exist"<<endl;
                break;
            }
            else if(temp->data>p->data)
                temp=temp->left;
            else
                temp=temp->right;
        }
    }
    return num;
}

void tbt :: bst()
{
    tbt tb;
    int num=tb.BST();
    stack <node *>s;
    node *tem=tb.root;
    node *arr[30];
    int n=0;
    while(!s.empty() || tem!=NULL)
    {
        if(tem!=NULL)
        {
            if(tem->left!=NULL)
                tem->l=false;
            else
                tem->l=true;
            if(tem->right!=NULL)
                tem->r=false;
            else
                tem->r=true;
            s.push(tem);
            tem=tem->left;
            continue;
        }
        else if(tem==NULL)
        {
            tem=s.top();
            s.pop();
            arr[n++]=tem;
            tem=tem->right;
        }
    }
    tb.head->left=tb.root;
    tb.head->l=false;
    node *p1=arr[0];
    p1->left=tb.head;
    if(p1->r==true)
        p1->right=arr[1];
    p1=arr[num-1];
    p1->right=tb.head;
    if(p1->l==true)
        p1->left=arr[num-2];

    //For Rmaining Nodes

    for(int i=1;i<num-1;++i)
    {
        p1=arr[i];
        if(p1->l==true)
            p1->left=arr[i-1];
        if(p1->r==true)
            p1->right=arr[i+1];
    }

    for(int i=0;i<num;++i)
    {
        p1=arr[i];
        cout<<"Data="<<p1->data<<" L="<<p1->l<<"  R="<<p1->r<<endl;
    }

    cout<<endl<<"Inoder traversal : ";
    tb.inorder();
    cout<<endl<<"Preorder traversal : ";
    tb.preorder();
    cout<<endl<<" Postorder traversal : ";
    tb.postorder();
    cout<<endl;
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
        cout<<" 6. Deletion "<<endl;
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
            case 5 : t.bst();
                     break;
            case 6 : t.Delete_start();
                     break;           
	    case 7 : exit (0);
                     break;
        }
    }
    return 0;
}









