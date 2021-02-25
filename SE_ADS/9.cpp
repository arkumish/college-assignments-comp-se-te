#include <bits/stdc++.h>
using namespace std;

//ASSIGNMENT 10
struct node{
	string val;
	node* left;
	node* right;
	node(){
		val = "";
		left = right = NULL;
	}
	node(string v){
		val = v;
		left = right = NULL;
	}
};
class OBST{
	private :
	int n,*p,*q,**cost,**weight,**parent;
	string *val;
	node *root;
	public :
	OBST(){
		n =0;
		p = q = 0;
		cost = weight = parent = 0;
		root = NULL;
	}
	void input(){
		cout<<"Enter number of nodes : ";
		cin>>n;
		p = new int[n+1];
		q = new int[n+1];
		val = new string[n+1];
		for (int i  = 1; i<=n; i++){
			cout<<"Enter value in node "<<i<<" : ";
			cin>>val[i];
		}
		for (int i = 1; i<=n; i++){
			cout<<"Enter number of searches for \""<<val[i]<<"\" : ";
			cin>>p[i];
		}
		cout<<"Enter number of searches <"<<val[1]<<" : ";
		cin>>q[0];
		for (int i = 1; i<n; i++){
			cout<<"Enter number of searches in range("<<val[i]<<","<<val[i+1]<<") : ";
			cin>>q[i];
		}
		cout<<"Enter number of searches >"<<val[n]<<" ; ";
		cin>>q[n];
	}
	void construct(){
		cost = new int*[n+1];
		for (int i = 0; i<=n; i++){
			cost[i] = new int[n+1];
		}
		weight = new int*[n+1];
		for (int i = 0; i<=n; i++){
			weight[i] = new int[n+1];
		}
		parent = new int*[n+1];
		for (int i = 0; i<=n; i++){
			parent[i] = new int[n+1];
		}
		for (int i = 0; i<=n; i++){
			weight[i][i] = q[i];
			cost[i][i] = q[i];
		}
		for (int i = 1; i<=n; i++){
			for (int j = i; j<=n; j++){
				int x = j-i,y = j;
				weight[x][y] = weight[x][y-1] + weight[x+1][y] - weight[x+1][y-1];
				if (i == 1){
					weight[x][y] += p[y];
					parent[x][y] = j;
				}
			}
		}
		for (int i = 1; i<=n; i++){
			for (int j = i; j<=n; j++){
				int x = j-i,y = j;
				int minc=INT_MAX,minp = -1;
				for (int par = x+1; par<=y; par++){
					int c = cost[x][par-1] + cost[par][y];
					if (c < minc){
						minc = c;
						minp = par;
					}
				}
				cost[x][y] = minc + weight[x][y];
				parent[x][y] = minp;
			}
		}
		//cout<<"Weight tree : "<<endl;
		for (int i =0; i<=n; i++){
			for (int j = 0; j<=n; j++){
				//cout<<weight[i][j]<<" ";
			}
			//cout<<endl;
		}
		//cout<<"Cost tree : "<<endl;
		for (int i =0; i<=n; i++){
			for (int j = 0; j<=n; j++){
			//	cout<<cost[i][j]<<" ";
			}
			//cout<<endl;
		}
	//	cout<<"Parent tree : "<<endl;
		for (int i =0; i<=n; i++){
			for (int j = 0; j<=n; j++){
				//cout<<parent[i][j]<<" ";
			}
		//	cout<<endl;
		}
    cout << "optimal cost for below BST is " << cost[0][n]<<endl;
	}
	void levelDisplay(){
		cout<<"Level order display is : \n\n";
		queue<pair<int,int> > q1,q2;
		q1.push({0,n});
		while(q1.size()){
			auto it = q1.front();
			q1.pop();
			int par = parent[it.first][it.second];
			cout<<val[par]<<" ";
			if(it.first+1 != par){
				q2.push({it.first,par-1});
			}
			if (it.second != par){
				q2.push({par,it.second});
			}
			if (q1.size() == 0){
				cout<<endl;
				swap(q1,q2);
			}
		}
	}
};

int main(){
    OBST tree;
    tree.input();
    tree.construct();
    tree.levelDisplay();
    return 0;
}
