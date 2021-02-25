
#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<random>
#include<ctime>
#include<sstream>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> pi; 

void ArraytoFile(vector<int> arr,string fname)
{
	if (arr.size() == 0) return;

	ofstream fout(fname.c_str(),ios::trunc);
	if (!fout)
	{
		cerr << " Failed to open " + fname << endl;
		exit(0);
	}

	fout << arr[0];
	for (int i = 1; i < arr.size(); ++i)
	{
		fout << "\n";
		fout << arr[i];
	}

	fout.close();
}

vector<string> SplitFile(string src,int CHUNKS)
{
	vector<int> arr;
	vector<string> tempFiles;

	ifstream fin(src.c_str());
	if (!fin)
	{
		cerr <<" Failed to open " + src<<endl;
		exit(0);
	}

	int noOfTempFiles = 0;

	while (!fin.eof())
	{
		for (int i = 0; i < CHUNKS && !fin.eof(); ++i)
		{
			int num;
			fin >> num;
			arr.push_back(num);
		}
		
		sort(arr.begin(),arr.end());

		string tempFname = to_string(noOfTempFiles++);
		
		ArraytoFile(arr,tempFname);

		tempFiles.push_back(tempFname);

		arr.clear();
	}

	cout << "NO. of temp files: " << noOfTempFiles << endl;
	fin.close();
	return tempFiles;
}

void MergeFiles(vector<string> tFname, string dest)
{
	vector<ifstream> files(tFname.size());
	//open all temp files
	for (int i = 0; i < tFname.size(); ++i)
	{
		files[i].open(tFname[i].c_str());

		if (!files[i].is_open())
		{
			cerr << " Failed to open " + tFname[i] << endl;
			exit(0);
		}
	}

	//open destination file
	ofstream DestFile(dest.c_str(),ios::trunc);
	if (!DestFile)
	{
		cerr << " Failed to open " + dest << endl;
		exit(0);
	}

	//priority_queue<pair<int,int>> q;		//(ele,fileInd)
	priority_queue<pi, vector<pi>, greater<pi> > q; 

	//push the first element from all the files in queue
	for (int i = 0; i < files.size(); ++i)
	{
		if (!files[i].eof())
		{
			int ele;
			files[i] >> ele;
			q.push({ele,i});
		}
	}

	bool isFirstEntry = true;
	while (!q.empty())
	{
		if (!isFirstEntry)
			DestFile << "\n";
		else
			isFirstEntry = false;

		int ele = q.top().first;		//get the minimum element
		int ind = q.top().second;		//get the ind of file from which this ele belongs
		
		q.pop();
		DestFile << ele ;
		
		if (!files[ind].eof())			//if file[ind] is not empty then get the next ele from this file
		{
			int num;
			files[ind] >> num;
			q.push({ num,ind });
		}
		else
			cout << "TempFile \""+tFname[ind] + "\" is completely Exhausted\n\n";
	
	}
	
	//close all temp files
	for (int i = 0; i < files.size(); ++i)
		files[i].close();

	//delete all temp files
	for (int i = 0; i < tFname.size(); ++i)
		if (remove(tFname[i].c_str()) != 0)
			cerr << "Error in deleting file" << endl;
}

//---------------//
//		MAIN    //
//-------------//
void RandomFileGenerator(string,int);

//--------------------------------------------------
int main()
{
				
	vector<string> tempFiles = SplitFile("data.txt",100);	//Split the Source File into number of Temp files
	
	MergeFiles(tempFiles,"BETA0.txt");						//Merge the Temp Files into one Dest File
	
	cout << "Files Merged Successfully" << endl;

	return 0;
}



