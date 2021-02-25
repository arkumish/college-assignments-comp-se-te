#include<bits/stdc++.h>
using namespace std ; 	
#define f first
#define s second
typedef pair<int, pair <int,int > > pii;

class MST{
    int n,m;
    int a[100][100];
    int id[100];
    bool visited[100];
    vector< pair<int,pair<int,int> > > p;
    //priority_queue<pair<int,int> , greater <pair<int,int > >  > pq;
public:
    MST(){
        for(int i=0 ; i<100 ; i++)
            id[i] = i;
        n=m=0;
        for(int i=0 ; i<100 ; i++)
            for(int j=0 ; j<100 ; j++)
                a[i][j]=0;
    }
    void input();
    void Prims();
    int root(int );
    void Union(int, int);
    void Krushkals();
};

void MST :: Union(int x,int y){
    id[root(x)] = id[root(y)];
}

int MST :: root(int x){
    if(id[x]==x)
        return x;
   else 
        return root(id[x]);
}

void MST :: input(){ 
    cout << "ENTER NUMBER OF NODES AND EDGES "<< endl;
    cin >> n >> m;
    cout << "ENTER EDGES CONNECTING NODES AND EDGE's WEIGHT" << endl;
    for(int i=0 ; i<m ; i++){
        int x,y,weight; 
        cin >> x >> y >> weight;
       // pq.push(make_pair(weight,make_pair(x,y)));
        p.push_back(make_pair(weight,make_pair(x,y)));
        a[x][y] = weight;
        a[y][x] = weight;
    }
}

void MST :: Krushkals(){
    long long mncost=0;
    sort(p.begin(),p.end());
    cout << "WEIGHT AND EDGES SELECTED :" << endl; 
    for(int i=0 ; i<n-1 ; i++){
    	//pii p = pq.top()
    	//pq.pop(); 
        if(root(p[i].s.f)!=root(p[i].s.s)){
        	cout << "WEIGHT :  " << p[i].f << " NODES : " << p[i].s.f << " " << p[i].s.s << endl;
            mncost += p[i].f;
            Union(p[i].s.f,p[i].s.s);
        }
    }
    cout << "COST BY KRUSHKALS IS :" << mncost << endl;
}

void MST :: Prims(){
	memset(visited,false,sizeof(visited));
	visited[0] = true;
	int mncost = 0;
	int i,j;
	for(int k=0 ; k<n-1 ; k++){
	  	int min = INT_MAX;
	  	int start,end;
	  	for(i=0 ; i<n ; i++){
	  		if(visited[i] == false)
	  			continue;
	  		for(j=0 ; j<n ; j++){
	  			if(a[i][j]==0 || visited[j]==true)
	  				continue;
	  			if(a[i][j] < min){
	  				start = i;
	  				end = j;
	  				min = a[i][j];
	  			}
	  		}	
	  	}
	  		cout << "WEIGHT :  " << a[start][end] << " NODES : " << start << " " << end << endl;
	  		mncost += a[start][end];
	  		visited[start] = true;
			visited[end] = true; 	
	}
  	cout << "COST BY PRIMS : " << mncost << endl;
}

int main(){
    int in; 
    MST t;
    do{
		cout << "----------------------------------------------------" << endl;
		cout << "1. ENTER INPUT " << endl;
		cout << "2. KRUSHKALS " << endl;
		cout << "3. PRIMS" << endl;
        cout << "0. EXIT" << endl;
		cout << "----------------------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
                t.input();
                break;
			case 2:
                t.Krushkals();
                break;
            case 3:
                t.Prims();
                break;
            default:
                cout << "END" << endl;
        }
	}
    while(in);
}

