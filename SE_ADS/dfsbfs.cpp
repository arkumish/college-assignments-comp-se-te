#include<bits/stdc++.h>
using namespace std;
vector<bool> vis1(100, 0), vis2(100, 0);
vector<int> v[100];

void dfs(int x)
{
	if(vis1[x])
		return;
	vis1[x] = true;
	cout<< x<< " ";
	for(int i = 0; i < v[x].size(); i++)
		dfs(v[x][i]);
}

void bfs(int x)
{
	queue<int> temp;
	temp.push(x);
	vis2[x] = true;
	while(temp.size())
	{
		int tmp;
		tmp = temp.front();
		temp.pop();
		cout<< tmp<< " ";
		for(int i = 0; i < v[tmp].size(); i++)
		{
			if(vis2[v[tmp][i]] == 0)
			{
				vis2[v[tmp][i]] = true;
				temp.push(v[tmp][i]);
			}
		}
	}
}

int main()
{
	int n;
	cout<< "Enter number of nodes ";
	cin>> n;
	int e;
	cout<< "Enter number of edges ";
	cin>> e;
	for(int i = 0; i < e; i++)
	{
		int a, b;
		cout<< "Enter edge ";
		cin>> a>> b;
		v[a].push_back(b);
		//v[b].push_back(a);
	}
	cout<< "DFS"<< endl;
	for(int i = 0; i < n; i++)
		if(vis1[i] == 0)
			dfs(i);
	cout<< endl;
	cout<< "BFS"<< endl;
	for(int i = 0; i < n; i++)
		if(vis2[i] == 0)
			bfs(i);
	cout<< endl;
	return 0;
}