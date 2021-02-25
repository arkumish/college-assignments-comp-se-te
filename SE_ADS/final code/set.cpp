#include<bits/stdc++.h>
using namespace std;
#define max 1000

class setop{
 public:
   int a[max];
   int aunion[max];
   int ainter[max];
   int n;int count;
 
  setop(){
       for(int i=0;i<max ; i++)
          {a[i]=-1;
          ainter[i]=-1;
          aunion[i]=-1;
          }

       n=0;
   }

  void insertset(int);
  void printset();
  void interset(setop);
  void unionset(setop);
  void subset(setop);
  void removeset(int);
  void diffset(setop);



};

void setop::insertset(int x){

   a[x]=1;
   aunion[x]=1;  
   if(x>n)
      n=x;
   count++;
}

void setop::printset(){

for(int i=0;i<=n;i++)
if(a[i]==1)
cout<<i<<" ";

}

void setop::interset(setop o1)
{  cout<<"\n Interesction of set : ";
      int mn;
      mn=min(n,o1.n);

      for(int i=0;i<=mn;i++)
      if(a[i]==o1.a[i] && a[i]==1 && o1.a[i]==1)
       { ainter[i]=1;
          cout<<i<<" "; }
       
}

void setop::unionset(setop o1)
{
    cout<<"\n union of set : ";
     
     

     for(int i=0;i<max;i++)
     if(a[i]==1 || o1.a[i]==1)
     cout<<i<<" ";
}

void setop::removeset(int y)
{
    a[y]=-1;
    cout<<" \n -- element removed -- ";
    printset();
}

void setop:: diffset(setop o1)
{
    cout<<"\n difference of set : ";
  for(int i=0;i<max;i++)
  if(o1.a[i]==1)
    aunion[i]=-1;

  for(int i=0;i<max;i++)
  if(aunion[i]==1)
  cout<<i<<" ";  


}

void setop::subset(setop o1)
{  int c=0;
     
    for(int i=0;i<max;i++)
    if(ainter[i]==1)
     c++;

     if(c==o1.count)
     cout<<" yes it is  subset ";
     else
     {
         cout<<" no it is not subset " ;
     }
     

}

/*void allPossibleSubset(int arr[],int n)
{
  int  count = pow(2,n);
  
  for (int i = 0; i < count; i++)
  {
   
    for (int j = 0; j < n; j++)
    {
      
      if ((i & (1 << j)) > 0)
        cout << arr[j] << " ";
    }
    cout << "\n";
  }
}*/
int main(){

setop ob1,ob2;

cout<<" \n ----- SET A ----- \n ";
int val,noe;
cout<<" enter no of elements : ";
cin>>noe;
cout<<" \n enter elements : ";

while(noe--)
{    cin>>val;
    ob1.insertset(val);
    
    }
cout<<"\n elements of set are : ";
ob1.printset();

cout<<" \n ----- SET B ----- \n ";

cout<<" enter no of elements : ";
cin>>noe;
cout<<" \n enter elements : ";

while(noe--)
{    cin>>val;
     ob2.insertset(val);
    
    }
int op;
while(op!=-1){
cout<<" \n\n ---- OPERATIONS ---- \n ";
cout<<"1) Display \n 2) interesction \n 3) union \n 4) difference(A-B) \n 5) differenc(B-A) \n 6) subset(A of B ) \n 7) subset(B of A) \n -1) exit \n ";  

cout<<"enter option : " ;cin>>op;

if(op==1){cout<<"\n set A : ";ob1.printset(); cout<<"\n set B : ";ob2.printset(); }
else if(op==2){ ob1.interset(ob2); }
else if(op==3){ ob1.unionset(ob2); }
else if(op==4){  ob1.diffset(ob2); }
else if(op==5){ ob2.diffset(ob1); }
else if(op==6){ ob1.subset(ob2); } 
else if(op==7){ ob2.subset(ob1); }      

}
return 0;
}