#include<bits/stdc++.h>
#define infinity INT_MAX
using namespace std;

typedef pair<int,int> pii;
const int N=1e5+1;
vector<pii>graph[N];
int v;
bool visited[N];
int parent[N];
int d[N];

void path(int end){
  if(parent[end]==-1)
  	{
  		cout<<end<<endl;
  		return;
  	}
  path(parent[end]);
  cout<<end<<endl;
}

void display(){
	for(int i=0;i<v;i++){
		cout<< char(65+i)<< " ->" <<d[i]<<endl;
	}
}

void dj(int start,int end){
  
for(int i=0;i<=v;i++){
	d[i]=infinity;
   parent[i]=-1;
}

d[start]=0;
priority_queue< pii ,vector<pii> ,greater<pii> >pq;
pq.push({d[start],start});

while(!pq.empty()){
	pii p=pq.top();
	pq.pop();
	int u,v,w;
    u=p.second;

	if(visited[u])
		continue;
	visited[u]=true;
   for(int i=0;i<graph[u].size();i++){
   	 v=graph[u][i].first;
     w=graph[u][i].second;

      if(d[v] > d[u] + w ){
      	d[v]=d[u]+w;
      	parent[v]=u;
      	pq.push({d[v],v});
      }

   }
}
display();
}


int main(){
	int e;
	cout<<"\nEnter number of vertices:";
	cin>>v;
    cout<<"\nEnter number of edges: ";
    cin>>e;
    for(int i=0;i<e;i++){
    	int a,b,w;
    	cin>>a>>b>>w;
    	graph[a].push_back( { b , w } );
    	graph[b].push_back( { a , w } );
    }
   int S,E;
   cout<<"\nEnter the starting and ending vertex:";
   cin>>S>>E;
  
   dj(S,E);

   path(E);

	return 0;
}