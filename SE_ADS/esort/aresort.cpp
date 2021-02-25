#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi; 

void array2file (vector<int> ar , string s){

	if(ar.size()==0)
		{ cout<<" empty files ";
              exit(0);  }

    ofstream fout(s.c_str(),ios::trunc);
    if(!fout){
    	cout<<" unble to open fies ";
    	exit(0);
    } 

    fout<<ar[0];

    for(int i=1;i<ar.size();i++)
    {
    	fout<<"\n";
    	fout<<ar[i];
    }         

    fout.close();
}



vector<string> splitfile(string src , int chunks){

std::vector<int > arr;
std::vector<string> tempfilesname;

 ifstream fin(src.c_str());
 if(!fin){
 	cout<<" unable to open file ";
 	exit(0);
 }

 int filecount=0;

 while(!fin.eof()){

  for(int i=0;i<chunks && !fin.eof();i++)
  {
       int n;
       fin>>n;
       arr.push_back(n);

  }

  sort(arr.begin(),arr.end());
  string tempname = to_string(filecount++);

  array2file(arr,tempname);
  tempfilesname.push_back(tempname);

  arr.clear();
 }
fin.close();
return tempfilesname;

}

void mergefiles(vector<string> filename , string dst ){

vector<ifstream> files(filename.size());

for(int i=0;i<filename.size();++i){

  files[i].open(filename[i].c_str());
  if(!files[i].is_open())
  { cout<<" unable to open this file "; exit(0);}

}

    //priority_queue<pair<int,int>> q;    //(ele,fileInd)
  priority_queue<pi, vector<pi>, greater<pi> > q; 

  for(int i=0;i<files.size();i++){

    if(!files[i].eof()){
      int ele;
      files[i]>>ele;
      q.push({ele,i});
    }
  }

ofstream fdst(dst.c_str());
if(!fdst){ cout<<" unable to open this file "; exit(0);}

  bool istrue = false;

  while(!q.empty()){

    if(istrue)
      fdst<<"\n";
    else 
      istrue=true;

    int ele = q.top().first;
    int ind = q.top().second;

    fdst<<ele;
    q.pop();

    if(!files[ind].eof()){
      int num;
      files[ind]>>num;
      q.push({num,ind});

    }
    else{
      cout<<" files "<< ind <<" exhausted "<<endl;
    }


  }

  for(int i=0;i<files.size();i++)
    files[i].close();

  for (int i = 0; i < tFname.size(); ++i)
    if (remove(tFname[i].c_str()) != 0)
      cerr << "Error in deleting file" << endl;


}


//-------------------------------
int main(){

vector<string> tempfiles = splitfile("data.txt",100);

mergefiles(tempfiles , "sort2.txt");

cout<<"\n ------ sorting complete  ----------------- ";
	return 0;
}