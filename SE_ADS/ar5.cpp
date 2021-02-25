#include<bits/stdc++.h>
using namespace std;

vector<int>indeegre(100,0);
queue<int>q;

class graph{
public:
	int g[100][100];
   int n;
   int e;

   graph(){

   	for(int i=0;i<100;i++)
   		for(int j=0;j<100;j++)
   			g[i][j]=0;
   }

	void input(){

         cout<<" enter no of nodes : ";
         cin>>n;
         cout<<" enter no of edges : ";
         cin>>e;
         cout<<" entr pairs : ";
         int x,y;

         for(int i=0;i<e;i++){
         	cin>>x>>y;

         	g[x][y]=1;
         	indeegre[y]++;


         }

         for(int i=0;i<n;i++){
         	if(indeegre[i]==0)
         		q.push(i);
         }




	}


	void topo(){

	
        if(q.empty()){
		cout << "CYCLIC GRAPH " << endl;
		return ;
	}
	
         vector<int>ans;

         while(q.size()){
         	int x=q.front();
         	q.pop();
          ans.push_back(x);

         	for(int i=0;i<n;i++){

         		if(g[x][i]){

         			indeegre[i]--;
         			if(indeegre[i]==0)
         				q.push(i);
         		}
         	}
         }      

     cout<<" topo logical sort : ";

     for(int i=0;i<ans.size();i++)
     	cout<<ans[i]<<" ";

	}

};

	int main(){

		graph obj;
		obj.input();
		obj.topo();
	}



