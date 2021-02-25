//topological 
#include<bits/stdc++.h>
using namespace std;
#define max 100
vector<int> vis(max, 0), indeg(max, 0);

class graph
{
	int g[max][max];
	int n;
public:
	graph()
	{
		n = 0;
		for(int i = 0; i < max; i++)
		{
			for(int j = 0; j < max; j++)
				g[i][j] = 0;
		}
	}
	void input()
	{
		int x, y;
		cout<< "Enter the number of vertices ";
		cin>> n;
		int num;
		cout<< "Enter the number of edges ";
		cin>> num;
		for(int i = 0; i < num; i++)
		{
			cout<< "Enter parent and child ";
			cin>> x>> y;
			indeg[y]++;
			g[x][y] = 1;
		}
	}
	void top()
	{
		queue<int> q;
		cout<< "Topological order is ";
		for(int i = 0; i < n; i++)
			if(indeg[i] == 0)
				q.push(i);
		vector<int> ans;
		while(q.size())
		{
			int x = q.front();
			q.pop();
			ans.push_back(x);
			for(int i = 0; i < n; i++)
			{
				if(g[x][i])
				{
					indeg[i]--;
					if(indeg[i] == 0)
						q.push(i);
				}
			}
		}
		cout<< "Topological order is ";
		for(int i = 0; i < ans.size(); i++)
			cout<< ans[i]<< " ";
	}
};
int main()
{
	graph obj;
	obj.input();
	obj.top();
	return 0;
}


