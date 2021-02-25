#include<bits/stdc++.h>
using namespace std ; 
typedef pair<int,int> pii;

class topological{
    int n,m;
    vector <int> a[10000];
    bool visited[10000];
    int in[10000];
public:
	topological(){
		memset(visited,false,sizeof(visited));
		memset(in,0,sizeof(in));
	}
    void input();
    void topologicalSort();
};

void topological :: input(){
	cout << "ENTER NUMBER OF NODES AND EDGES " << endl;
	cin >> n >> m;
	cout<<"  enter pair wise : \n";
	for(int i=0 ; i<m ; i++){
		int x,y; cin >> x >> y;
		in[y]++;
		a[x].push_back(y);
	}
} 

void topological :: topologicalSort(){
	queue <int >q;
	int start;
	cout << "TOPOLOGICAL ORDER " << endl;
	int i;
	
	for(int i=0 ; i<n ; i++)
		if(!in[i])
			q.push(i);
			
	if(q.empty()){
		cout << "CYCLIC GRAPH " << endl;
		return ;
	}
		
	while(!q.empty()){
		start = q.front();
		q.pop();
		
		cout << start << " ";
		
		for(int i=0 ; i<a[start].size() ; i++){
			
			in[a[start][i]]--;
			
			if(!in[a[start][i]])
				q.push(a[start][i]);
		}	
	}	
	cout << endl;
}

int main(){
	int in; 
    topological t;
    t.input();
    t.topologicalSort();
    
}
