#include<bits/stdc++.h>
using namespace std;

	map<int, int> m1, m2;
	vector<int> v1, v2;

class Set{
public:
	void insert();
	void check();
	void Intersection();
	void Union();
	void subString();
	void remove();
	void Print();
	void difference();
	void subSets();
	void computeSize();
};

void Set :: insert(){
	cout << "1. Insert an element in set 1. "<< endl;
	cout << "2. Insert an element in set 2. "<< endl;
	int ch ; cin >> ch;
	cout << "Enter the number "; 
	int x; cin >> x;
	if(ch == 1){
		if(m1[x] == 0){
			m1[x] = 1;
			v1.push_back(x);
		}
		else
			cout<< "Number already exists in this set "<< endl;
	}
	else{
		if(m2[x] == 0){
			m2[x] = 1;
			v2.push_back(x);
		}
		else
			cout<< "Number already exists in this set "<< endl;		
	}
	sort(v1.begin(),v1.end());
	sort(v2.begin(),v2.end());
}

void Set :: check(){
	cout<< "1. Check for set 1."<< endl;
	cout<< "2. Check for set 2. "<< endl;
	int ch ; cin >> ch;
	cout<< "Enter the number you want to check ";
	int x; cin >> x;
	if(ch == 1){
		if(m1[x])
			cout<< "Present "<< endl;
		else
			cout<< "Absent "<< endl;
	}
	else{
		if(m2[x])
			cout<< "Present "<< endl;
		else
			cout<< "Absent "<< endl;	
	}
}

void Set :: Intersection(){
	vector<int> ans;
	int i = 0, j = 0;
	int n1 = v1.size(), n2 = v2.size();
	while(i < n1  &&  j < n2){
		if(v1[i] < v2[j])
			i++;
		else if(v1[i] > v2[j])
			j++;
		else{
			ans.push_back(v1[i]);
			i++,j++;
		}
	}
	cout<< "Intersection of set 1 and set 2 is "<< endl;
	for(unsigned int k = 0; k < ans.size(); ++k)
		cout<< ans[k]<< " ";
	cout<< endl;
}

void Set :: Union(){
	vector<int> ans;
	int i = 0, j = 0, n1 = v1.size(), n2 = v2.size();
	while(i < n1  and  j < n2){
		if(v1[i] < v2[j])
			ans.push_back(v1[i]),i++;
		else if(v1[i] > v2[j])
			ans.push_back(v2[j]),j++;
		else{
			ans.push_back(v1[i]);
			i++,j++;
		}
	}
	while(i < n1)
		ans.push_back(v1[i]),i++;	
	while(j < n2)
		ans.push_back(v2[j]),j++;
	
	cout<< "Union of the two sets is "<< endl;
	for(unsigned int k = 0; k < ans.size(); ++k)
			cout<< ans[k]<< " ";
	cout<< endl;
}

void Set :: difference(){
	vector <int> ans;
	cout<< "1. Set 1 - Set 2"<< endl;
	cout<< "2. Set 2 - Set 1"<< endl;
	int ch; cin >> ch;
	int i=0, j=0;
	int n1 = v1.size(), n2 = v2.size();
	if(ch == 1){
		while(i < n1  &&  j < n2){
			if(v1[i] < v2[j])
				ans.push_back(v1[i]),i++;
			else if(v1[i] > v2[j])
				j++;
			else
				i++,j++;
		}
		while(i < n1)
			ans.push_back(v1[i]),i++;
		cout<< "Set 1 - Set 2 is "<< endl;
	}
	else{
		while(i < n1  &&  j < n2){
			if(v1[i] < v2[j])
				i++;
			else if(v1[i] > v2[j])
				ans.push_back(v2[j]),j++;
			else
				i++,j++;
		}
		while(j < n2)
			ans.push_back(v2[j]),j++;
		cout<< "Set 2 - Set 1 is "<< endl;
	}
	for(unsigned int k = 0; k < ans.size(); ++k)
		cout<< ans[k]<< " ";
	cout<< endl;
}

void Set :: subString(){
	cout<< "1. Check if 1 is subset of 2 or not?"<< endl;
	cout<< "2. Check if 2 is subset of 1 or not?"<< endl;
	int p; cin >> p;
	if(p == 1){
		for(unsigned int i = 0; i < v2.size(); ++i){
			if(m1[v2[i]] == 0){
				cout<< "Not a subset "<< endl;
				return;
			}
		}
	}
	else{
		for(unsigned int i = 0; i < v1.size(); ++i){
			if(m2[v1[i]] == 0){
				cout<< "Not a subset "<< endl;
				return;
			}
		}	
	}
	cout<< "Is a subset "<< endl;
}

void Set :: remove(){
	cout<< "1. Set 1"<< endl;
	cout<< "2. Set 2"<< endl;
	int ch; cin >> ch;
	cout<< "Enter element to be deleted ";
	int x ;cin>> x;
	if(ch == 1){
		if(m1[x] == 0)
			cout<< "Element not found "<< endl;
		else{
			m1[x] = 0;
			int tmp;
			for(unsigned int i = 0; i < v1.size(); ++i){
				if(v1[i] == x){
					tmp = i;
					break;
				}
			}
			v1.erase(v1.begin() + tmp);
			cout<< "DELETED"<< endl;
		}
	}
	else{
		if(m2[x] == 0)
			cout<< "Element not found "<< endl;
		else{
			m2[x] = 0;
			int tmp;
			for(unsigned int i = 0; i < v2.size(); ++i){
				if(v2[i] == x){
						tmp = i;
						break;
				}
			}
			v2.erase(v2.begin() + tmp);
			cout<< "DELETED"<< endl;
		}
	}
}
void Set :: Print(){
	cout<< "SET 1 : ";
	for(unsigned int i = 0; i < v1.size(); ++i)
		cout<< v1[i]<< " ";
	cout<< endl;
	cout<< "SET 2 : ";
	for(unsigned int i = 0; i < v2.size(); ++i)
		cout<< v2[i]<< " ";
	cout<< endl;
}

void Set :: subSets(){
	int n1 = v1.size();
	int n2 = v2.size();
	cout<< "1. Find subsets of 1st Set"<< endl;
	cout<< "2. "<< endl;
	int p; cin >> p;
	if(p==1){
		int c = pow(2,n1);
		cout << "{";
		for(int i=0 ; i<c ; i++){
			cout << "{";
			for(int j=0 ; j<n1 ; j++){
				if(i & (1<<j))
					cout << v1[j] <<" ";
			}
			cout << "}, ";
		}
		cout << "}";
	}
	else{
		int c = pow(2,n2);
		cout << "{";
		for(int i=0 ; i<c ; i++){
			cout << "{";
			for(int j=0 ; j<n2 ; j++){
				if(i & (1<<j))
					cout << v2[j] <<" , ";
			}
			cout << "},";
		}
		cout << "}";
	}
}

void Set :: computeSize(){
	int c;
	cout<< "1. Set 1"<< endl;
	cout<< "2. Set 2"<< endl;
	cin >> c;
	cout << "SIZE -> ";
	if(c == 1)			cout<< v1.size()<< endl;
	else				cout<< v2.size()<< endl;
}
int main(){
	Set t;
	int d;
	do{
		int in;
		cout << "1. Insert " << endl;
		cout << "2. Check if the element is present "<< endl;
		cout << "3. Size of the set "<< endl;
		cout << "4. Intersection "<< endl;
		cout << "5. Union "<< endl;
		cout << "6. Difference "<< endl;
		cout << "7. Check if subset "<< endl;
		cout << "8. Find All Subsets " << endl; 
		cout << "0. Exit " << endl;
		cin>> in;
		switch(in){
			case 1:
				t.insert();
				break;
			case 2:
				t.check();
				break;
			case 3:
				
				break;
			case 4:
				t.Intersection();
				break;
			case 5:
				t.Union();
				break;
			case 6:
				t.difference();
				break;
			case 7:
				t.subString();
				break;
			case 8:
				t.subSets();
				break;
			case 0:
				cout << "EXITING" << endl;
				break;
		}
	}
	while(d);
}