#include<bits/stdc++.h>
using namespace std ; 
#define all(a) a.begin(),a.end()
#define f first
#define s second
typedef pair<int, pair <int,int > > pii;

class shortestPath{
    int n,m;
    int src;
    vector <pair <int,int > > a[100000];
    bool visited[100000];
    int dist[100000];
public:
    ShortestPath(){
		for(int i=0 ; i<100000 ; i++){
			visited[i] = false;
			dist[i] = INT_MAX;
		}
    }
    void input();
    void findMin();
    void findAllPath();
    void dijkstra();
};

void shortestPath :: input(){ 
    cout << "ENTER NUMBER OF NODES AND EDGES "<< endl;
    cin >> n >> m;
    cout << "ENTER STARTING NODE " << endl;
    cin >> src;
    dist[src]=0;
    cout  << "ENTER EDGES AND ITS WEIGHT " << endl;
    for(int i=0 ; i<m ; i++){
    	int x,y,weight; 
    	cin >> x >> y >> weight;
    	a[x].push_back(make_pair(y,weight));
    }
}


void shortestPath :: findMin(){
	
}

void shortestPath :: dijkstra(){
	for(int k=0 ; k<n ; k++){
		 int mn = INT_MAX;
		 int ind;
		for(int i=1 ; i<n+1 ; i++){
			if(mn>dist[i] && visited[i]==false){
				mn = dist[i];
				ind = i;
				visited[i]=true;
			}
		}
		for(int i=0 ; i<a[ind].size() ; i++){
			if(dist[ind] + a[ind][i].second < dist[a[ind][i].first]){
				dist[a[ind][i].first] = dist[ind] + a[ind][i].second;
			}	
		}
	}
	
	for(int i=1 ; i<n+1 ; i++){
		cout << dist[i] << " ";
	}
	cout << endl;
}

int main(){
    int in; 
    shortestPath t;
    do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. ENTER INPUT " << endl;
		cout << "2. BASIC DIJKSTRA " << endl;
		cout << "3. FIND MIN" << endl;
        	cout << "0. EXIT" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
                t.input();
                break;
			case 2:
                t.dijkstra();
                break;
            default:
                cout << "END" << endl;
        }
	}
    while(in);
}
/*
6 8
ENTER EDGES AND ITS WEIGHT 
1 3 1
1 2 2
3 2 0
3 5 2
3 4 4
2 5 0
4 6 1
5 6 2
*/

