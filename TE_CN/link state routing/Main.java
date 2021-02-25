
import java.net.*;
import java.io.*;
import java.util.*;

class Main{
	int in[][]; // adjacency matrix
	int dist[];
	int par[];
	int ppar[];
	boolean visited[];
	int n; // number of nodes
	int st;
	
	Main(){
	
		in  = new int[1000][1000];
		dist = new int[1000];
		visited = new boolean[1000];
		par = new int[1000];
		ppar = new int[1000];
		for(int i=0 ; i<dist.length ; i++)
			dist[i] = 99999;
	}
	
	int minNodeD(){ 
		int min = 999999;
		int minNode = -1; 
		for (int v = 0; v < n; v++) {
		    if (visited[v] == false && dist[v] <= min){ 
		        min = dist[v];
				minNode = v; 
		    }
		}
		return minNode; 
	} 
	
	void dijiktras(){
		dist[st] = 0;
		for(int i=0 ; i<n ; i++){
			int u = minNodeD();
			visited[u] = true;
			for(int v=0 ; v<n ; v++){
				if(visited[v]==false && in[u][v]!=0 && dist[u] + in[u][v] < dist[v]){
					if(par[u] == -2){
						ppar[v] = -2;
					}
					else if(par[u] == -1){
						ppar[v] = -1;
					}
					else{
						if(par[u] == -1)
							ppar[v] = u;
						else
							ppar[v] = par[u];
					}
					dist[v] = dist[u] + in[u][v]; 
				}
			}	
		}
	
	}
	
	void fx(){

                System.out.print("Enter number of nodes :");
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		for(int i=0 ; i<n ; i++){
			for(int j=0 ; j<n ; j++){
				in[i][j] = sc.nextInt();
			}
		}
		
		System.out.println("INPUT THE NODE FOR WHICH ROUTER TABLE NEED TO BE PRINTED : ");
		st = sc.nextInt();
	
		par[st] = -2;
		for(int i=0 ; i<n ; i++){
			if(in[st][i]!=0)
				par[i] = -1;
		}
		dijiktras();
		
		System.out.println("NODE" + " " + "DISTANCE" + " " + "NEIGHBOUR"); 
		for(int i=0 ; i<n ; i++){
			System.out.print(i);
			System.out.print("      ");
			System.out.print(dist[i]);
			System.out.print("      ");
			if(ppar[i] == -1 || ppar[i] == -2)
				System.out.print("-");
			else
				System.out.print(ppar[i]);
			System.out.println();
		}
	}
	
	
	public static void main(String args[]){
		Main obj = new Main();
		obj.fx();
	}
		
	
}
/*
0 4 0 0 1
4 0 2 0 6
2 0 0 3 3
0 0 3 0 1
1 6 3 1 0
*/
