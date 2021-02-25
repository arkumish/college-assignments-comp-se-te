#include<bits/stdc++.h>

using namespace std;

class graph{

protected: 	
 int am[100][100];
 int n,e;
 vector<pair < int , pair < int , int > > >g;
 
public:
	graph(){
		for(int i=0;i<100;i++)
			for(int j=0;j<100;j++)
				am[i][j]=0;

	   		
	}

	void input(){

		cout<<" enter nodes : ";
		cin>>n;
		cout<<" enter edgs :";
		cin>>e;
		cout<<" enter < parent  , child  , weight > : \n";
		int x,y,z;
		for(int i=0;i<e;i++)
		{
            cin>>x>>y>>z;

            am[x][y]=z;
            am[y][x]=z;

            g.push_back(make_pair(z,make_pair(x,y)));
		}
	}


};

class prims:public graph{

  bool visited[100];

public:

	prims(){
		for(int i=0;i<100;i++)
			{ visited[i]=0;}
	}


	void prims_mst()
	{
        int cst=0;
	    int sv=0,ev=0,loop=0;
		visited[0]=1;

		   	while(loop!=n)
		   {
		       	int min=10000;
		        sv=0;ev=0;

		        for(int i=0;i<n;i++)
		        {
		        	if(visited[i])
		        	{
		        		for(int j=0;j<n;j++)
		        		{
		        			if(am[i][j] && visited[j]==0)
		        			{
		        				if(am[i][j]<min)
		        				{
		        					min=am[i][j];
		        					sv=i;
		        					ev=j;
		        				}
		        			}
		        		}
		        	}
		          

				}

				if(am[sv][ev])
				{
					cout<<" "<<sv<<" < - > "<<ev<<" : "<<am[sv][ev]<<endl;
					cst+=am[sv][ev];
				}
				visited[ev]=1;
				loop++;

		   }

		   cout<<"\n total  cost : "<<cst<<endl;

	}

};

//--------------------------------------------------------------------------

class kruskal : public graph{
 int parent[100];
 int cst;

  public:
  	   kruskal(){
  	   	cst=0;
  	   	for(int i=0;i<100;i++)
	   {
	   	parent[i]=i;
	   }
  	   }

  	   int find(int x){
  	   	if(x==parent[x])
  	   		return x;
  	   	else
  	   		return find (parent[x]);
  	   }

  	   void unions(int x,int y){
  	   	parent[x]=parent[y];
  	   }

  	   void kruskal_mst(){

  	   	sort(g.begin(),g.end());
  	   	for(int i=0;i<g.size();i++)
  	   	{
  	   		int x= find(g[i].second.first);
  	   		int y= find(g[i].second.second);

  	   		if(x!=y)
  	   		{
  	   			cout<<" "<<g[i].second.first<<" < - > "<<g[i].second.second<<" : "<<g[i].first<<endl;
					cst+=g[i].first;
					unions(x,y);
  	   		}
  	   	}
            cout<<"\n total  cost : "<<cst<<endl;
     
  	   }




};







//---------------------------------------------------------------
int main(){

	/*prims obj;
	obj.input();
	obj.prims_mst();*/

	kruskal obj;
	obj.input();
	obj.kruskal_mst();


	return 0;
}