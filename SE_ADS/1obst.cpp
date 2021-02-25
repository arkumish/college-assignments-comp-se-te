#include <bits/stdc++.h>
#define nl "\n"
using namespace std ;

class OBST{
	int n , cost ;
	int * suc , * fail ;
	int ** w , ** c , ** r ;
public	:
	OBST(){
		cout << "Enter the no of nodes : " ; cin >> n ;
		this->n = n ;
		suc = new int [n+2] ;
		fail = new int [n+2] ;
		w = new int * [n+2] ;
		c = new int * [n+2] ;
		r = new int * [n+2] ;
		for(int i=0 ;i<n+2 ; i++){
			w[i] = new int [n+2] ;
			c[i] = new int [n+2] ;
			r[i] = new int [n+2] ;
		}
		input() ;
	}
	void input() ;
	int create(int , int) ;
	void preorder(int , int) ;
	void inorder(int , int) ;
};

void OBST :: input(){
	cout << "Enter Success frequencies \n" ;
    for(int i=1 ;i<=n ;i++){
        cin >> suc[i] ;
    }
    cout << "Enter failure frequencies \n" ;
    for(int i=0 ;i<n+1 ;i++){
        cin >> fail[i] ;
    }
    for(int i=1 ; i<n+1 ; i++){
    	for(int j=i ; j<n+1 ; j++){
    		if(i==j){
    			r[i][j] = -1 ;
    			w[i][i] = suc[i] + fail[i-1] + fail[i] ;
    			c[i][i] = w[i][i] ;
    		}
    		else{
    			w[i][j] = w[i][j-1] + fail[j] + suc[j] ;
    			c[i][j]=-1 ;
    		}
    	}
    }
    cost = create(1 , n) ;
    cout << "Minimum Cost of tree : " << cost << "\n" ;
    /*for(int i=1 ; i<n+1 ; i++){
    	for(int j=i ; j<n+1 ; j++){
    		cout << w[i][j] << " " << c[i][j] << " " << r[i][j] << "		" ;
    	}
    	cout << nl ;
    }*/
    preorder(1 , n) ;
    cout << nl ;
    inorder(1 , n) ;
    cout << nl ;
}

int OBST :: create(int s , int e){
	if(s>e){
		return 0 ;
	}
	if(s==e){
		return w[s][e] ;
	}
	if(c[s][e]!=-1){
		return c[s][e] ;
	}
	int min = INT_MAX , temp , k ;
	for(int i = s ; i<=e ; i++){
		temp = create(s , i-1) + create(i+1 , e) + w[s][e] ;
		if(temp<min){
			min = temp ;
			k = i ;
		}
	}
	r[s][e] = k ;
	return (c[s][e] = min) ;
}

void OBST :: preorder(int s , int e){
	if(s>e){
		return ;
	}
	if(r[s][e]==-1){
		cout << s << " " ;
		return ;
	}
	cout << r[s][e] << " " ;
	preorder(s , r[s][e]-1) ;
	preorder(r[s][e]+1 , e) ;
	return ;
}

void OBST :: inorder(int s , int e){
	if(s>e){
		return ;
	}
	if(r[s][e]==-1){
		cout << s << " " ;
		return ;
	}
	inorder(s , r[s][e]-1) ;
	cout << r[s][e] << " " ;
	inorder(r[s][e]+1 , e) ;
	return ;
}

int main(){
	OBST o ;
	return 0 ;		
}

