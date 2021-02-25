#include<bits/stdc++.h>
using namespace std;

struct entry{
public:
    string name,number;
    int chain;
};

class hashing{
    struct entry arr[100];
    int SIZE ;
public:
    hashing(){
        SIZE = 100;
        for(int i=0 ; i<SIZE ; i++){
            arr[i].name = arr[i].number = "";
            arr[i].chain  = -1;
        }
    }
    bool insertWR(string ,string);
    bool insertR(string ,string);
    int hFun(string );
    bool checkFull();
    bool isEmpty(int);
    void Erase(int );
    void Copy(int );
    bool Delete(string );
    void display();
    string search(string);
    int findPar(string);
};

int hashing  :: hFun(string a){
    int n = a.size();
    int val=0;
    for(int i=0 ; i<n ; i++){
        val = val + (int)(a[i]);
    }
    val = val%SIZE;
    return val;
}

bool hashing :: isEmpty(int key){
    if(arr[key].name=="" && arr[key].number=="" && arr[key].chain==-1)
        return true;
    return false;
}

bool hashing :: checkFull(){
    for(int i=0 ; i<SIZE ; i++)
        if(arr[i].name == "" && arr[i].number=="" && arr[i].chain==-1)
            return false;
    return true;
}

bool hashing :: insertWR(string a,string b){
    if(checkFull())
        return false;
    int key = hFun(a);

    if(isEmpty(key)){
        arr[key] = (entry){.name = a, .number = b, .chain = -1 };
        return true;
    }
    else{
        int i = key;
        while(arr[i].chain != -1)
            i = arr[i].chain;

        cout << i << endl;
        for(int j = i+1 ; j<SIZE ; j = (j + 1)%SIZE){
            if(isEmpty(j)){
                arr[j] = (entry){.name = a, .number = b, .chain = -1 };
                arr[i].chain = j;
                return true;
            }
        }
        return true;
    }
    return false;
} 


int hashing :: findPar(string s){
    // we are sure that given node has parent as it sits on other's place 
	int key = hFun(s);
	while(1){
        int nxt = arr[key].chain;
		if(arr[nxt].name == s){
			return key;
        }
		key = nxt;
	}
}

bool hashing :: insertR(string a,string b){
    if(checkFull())
        return false;

    int key = hFun(a);
    //cout << a << " " << key << endl;
    
    if(isEmpty(key)){
        arr[key] = (entry){.name = a, .number = b, .chain = -1 };
        return true;
    }
    else if(hFun(arr[key].name)!= key){
        int pos = findPar(arr[key].name);
        while(arr[pos].chain != key)
            pos = arr[pos].chain;

        arr[pos].chain = arr[key].chain;// copying chain of child to root
        string tname = arr[key].name;
        string tnumber = arr[key].number;
        arr[key] = (entry){.name = a, .number = b, .chain = -1 };
        insertR(tname,tnumber);
        return true;
    }
    else{
        int i = key;
        while(arr[i].chain != -1)
            i = arr[i].chain;

      //  cout << i << endl;
        for(int j = i+1 ; j<SIZE ; j = (j + 1)%SIZE){
            if(isEmpty(j)){
                arr[j] = (entry){.name = a, .number = b, .chain = -1 };
                arr[i].chain = j;
                return true;
            }
        }
    }
    return false;
} 

void hashing :: Erase(int key){
    arr[key].name = arr[key].number = "";
    arr[key].chain  = -1;
}

void hashing :: Copy(int key){
    arr[key] = (entry){.name = arr[arr[key].chain].name, .number = arr[arr[key].chain].number , .chain = arr[arr[key].chain].chain };
}

bool hashing :: Delete(string a){

    int key = hFun(a);
    if(isEmpty(key)){
        return false;
    }

    if(arr[key].name == a){
        if(arr[key].chain==-1)
            Erase(key);
        else{
            int p = arr[key].chain;
            Copy(key);
            Erase(p);
        }
        return true;
    }
    else if(arr[key].name!= a && arr[key].chain == -1)
        return false;
    
    int prev = key;
    int i = arr[key].chain;
    while(1){
        if(arr[i].name == a){
            arr[prev].chain = arr[i].chain;
            Erase(i);
            return true;
        }
        else if(arr[i].name !=a && arr[i].chain == -1){
            return false;
        }
        else{
            prev = i;
            i = arr[i].chain;
        }
    }
    return false;
}

void hashing :: display(){
	for(int i=0 ; i<SIZE ; i++){
		if(!isEmpty(i))
			cout << i << "-> " << arr[i].name << " " << arr[i].number << " " << arr[i].chain << endl;
	}
}

string hashing :: search(string s){
	int key = hFun(s);
	if(arr[key].name !=s && arr[key].chain == -1)
		return "Not Found!";

	while( key!=-1 ){
		if(arr[key].name == s){
            string temp = arr[key].name + " has number "  + arr[key].number + "at position" + to_string(key) + "\n";
			return temp;
        }
		key = arr[key].chain;
	}
	return "Not Found!";
}

int main(){
    hashing d;
	string name,num;
	int in;
	do{
		cout<< " Choose:"  << endl;
        cout << "-------------------------------------" << endl;
		cout <<" 1. Insert With Replacement" << endl;
        cout <<" 2. Insert Without Replacement" << endl;
        cout <<" 3. Display" << endl;
        cout <<" 4. Search" << endl;
        cout <<" 5. Delete" << endl;
        cout <<" 0. Exit" << endl;
        cout << "-------------------------------------" << endl;
		cin >> in;
		switch(in){
			case 1:
					cout << "Enter The Name and Number : ";
					cin >> name >> num;
					if(!d.insertR(name,num))
						cout<<"Not Inserted!";
					break;
            case 2:
					cout << "Enter The Name and Number : ";
					cin >> name >> num;
					if(!d.insertWR(name,num))
						cout<<"Not Inserted!";
					break;
			case 3: 
                    d.display();
					break;
			case 4:	
                    cout << "ENTER NAME TO BE SEARCHED" << endl;
                    cin >> name;
                    cout << d.search(name);
					break;
            case 5:
                    cout << "ENTER NAME TO BE DELETED" << endl;
                    cin >> name;
                    if(!d.Delete(name))
                        cout << "NO ENTRY FOUND " << endl;
                    break;
			case 0: 
				in = 0;
		}
	}
	while(in);
}