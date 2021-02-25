#include<bits/stdc++.h>
using namespace std;

struct node
{
	string name;
	string num;
	int chain;
	int key;
};

long long hashv(string s, int siz)
{
	long long h = 0, p = 31;
	for(int i = s.size() - 1; i >= 0; --i)
		h = (h * p + (s[i] - 'a' + 1))%siz;
	return h;
}

class tele
{
	node n[11];
public:
	tele()
	{
		for(int i = 0; i < 11; ++i)
		{
			n[i].name = "-1";
			n[i].num = "-1";
			n[i].chain = -1;
			n[i].key = -1;
		}
	}
	void input_1()
	{
		string nam, phone;
		cout<< "Enter name of the person ";
		cin>> nam;
		cout<< "Enter phone number of the person ";
		cin>> phone;
		int val = hashv(nam, sizeof(n)/sizeof(n[0]));
		if(n[val].num == "-1")
		{
			n[val].key = val;
			n[val].name = nam;
			n[val].num = phone;
		}
		else
		{
			int curr = val, tmp = -1;
			while(n[curr].key != -1)
			{
				if(n[curr].key == -2)
					break;
				if(n[curr].key == val)
					tmp = curr;
				curr++;
				curr = curr%(sizeof(n)/sizeof(n[0]));
			}
			if(tmp != -1)
				n[tmp].chain = curr;
			n[curr].key = val;
			n[curr].name = nam;
			n[curr].num = phone;
		}
	}
	void print()
	{
		cout<< endl<< endl<< "S.NO \t"<< "NAME \t"<< "NUMBER \t"<< "CHAIN \t"<< "KEY"<< endl;
		for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
			cout<< i<< "  \t"<< n[i].name<< "\t"<< n[i].num<< "\t"<< n[i].chain<< "\t"<< n[i].key<< endl;
		cout<< endl;
	}
	void search_1()
	{
		string q;
		cout<< "Enter the name of the person ";
		cin>> q;
		int srch = hashv(q, sizeof(n)/sizeof(n[0]));
		if(n[srch].name == q)
		{
			cout<< "Name -> "<< q<< endl;
			cout<< "Number -> "<< n[srch].num<< endl;
		}
		else
		{
			int curr = srch;
			while(n[curr].key != srch)
			{
				curr++;
				curr = curr%(sizeof(n)/sizeof(n[0]));
				if(curr == srch)
				{
					cout<< "Name not found "<< endl;
					return;
				}
			}
			while(n[curr].chain != -1)
			{
				if(n[curr].name == q)
					break;
				curr = n[curr].chain;
			}
			if(n[curr].name == q)
			{
				cout<< "Name -> "<< q<< endl;
				cout<< "Number -> "<< n[curr].num<< endl;
			}
			else
			{
				cout<< "Name not found "<< endl;
					return;
			}
		}
	}
	void input_2()
	{
		string nam, phone;
		cout<< "Enter name of the person ";
		cin>> nam;
		cout<< "Enter phone number of the person ";
		cin>> phone;
		int val = hashv(nam, sizeof(n)/sizeof(n[0]));
		if(n[val].key == -1  or  n[val].name == "DELETED")
		{
			n[val].key = val;
			n[val].name = nam;
			n[val].num = phone;
		}
		else
		{
			if(n[val].key == val)
			{
				int curr = val, tmp = -1;
				while(n[curr].key != -1)
				{
					if(n[curr].key == -2  and  n[curr].chain == -1)
						break;
					if(n[curr].key == val)
						tmp = curr;
					curr++;
					curr = curr%(sizeof(n)/sizeof(n[0]));
				}
				if(tmp != -1)
					n[tmp].chain = curr;
				n[curr].key = val;
				n[curr].name = nam;
				n[curr].num = phone;
			}
			else
			{
				int curr = val, tmp = -1;
				for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
				{
					if(n[i].chain == val)
					{
						if(n[val].chain != -1)
							n[i].chain = n[val].chain;
						else
							tmp = i;
					}
				}
				//cout<< tmp<< " ";
				while(n[curr].key != -1)
				{
					curr++;
					curr = curr%(sizeof(n)/sizeof(n[0]));
					if(n[curr].key == n[val].key)
						tmp = curr;
					if(n[curr].key == -2)
						break;
				}
				cout<< tmp<< " "<< curr<< endl;
				if(tmp != -1)
					n[tmp].chain = curr;
				n[curr].name = n[val].name;
				n[curr].num = n[val].num;
				n[curr].key = n[val].key;
				n[val].key = val;
				n[val].name = nam;
				n[val].num = phone;
				n[val].chain = -1;
			}
		}
	}
	void search_2()
	{
		string q;
		cout<< "Enter the name of the person ";
		cin>> q;
		int srch = hashv(q, sizeof(n)/sizeof(n[0]));
		if(n[srch].key != srch)
		{
			cout<< "Name not found "<< endl;
					return;
		}
		else
		{
			int curr = srch;
			while(n[curr].chain != -1)
			{
				if(n[curr].name == q)
					break;
				curr = n[curr].chain;
			}
			if(n[curr].name == q)
			{
				cout<< "Name -> "<< q<< endl;
				cout<< "Number -> "<< n[curr].num<< endl;
			}
			else
			{
				cout<< "Name not found "<< endl;
					return;
			}
		}
	}
	void del_1()
	{
		string nam;
		cout<< "Enter name whose data you want to delete ";
		cin>> nam;
		int val = hashv(nam, sizeof(n)/sizeof(n[0]));
		if(n[val].name == nam)
		{
			cout<< "DELETED "<< endl;
			n[val].name = "DELETED";
			n[val].num = "-1";
			n[val].key = -2;
			n[val].chain = -1;
		}
		else
		{	
			int curr = val;
			while(n[curr].key != val)
			{
				curr++;
				curr = curr%(sizeof(n)/sizeof(n[0]));
				if(curr == val)
				{
					cout<< "Element not found "<< endl;
					return;
				}
			}
			while(n[curr].chain != -1)
			{
				if(n[curr].name == nam)
					break;
				curr = n[curr].chain;
			}
			if(n[curr].name == nam)
			{
				for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
				{
					if(n[i].chain == curr)
					{
						n[i].chain = n[curr].chain;
						break;
					}
				}
				cout<< "DELETED "<< endl;
				n[curr].name = "DELETED";
				n[curr].num = "-1";
				n[curr].key = -2;
				n[curr].chain = -1;
			}
			else
			{
				cout<< "Element not found "<< endl;
					return;
			}
		}
	}
	void del_2()
	{
		string nam;
		cout<< "Enter name whose data you want to delete ";
		cin>> nam;
		int val = hashv(nam, sizeof(n)/sizeof(n[0]));
		if(n[val].name == nam)
		{
			cout<< "DELETED "<< endl;
			n[val].name = "DELETED";
			n[val].num = "-1";
			n[val].key = -2;
		}
		else
		{
			if(n[val].key == -1)
			{
				cout<< "Element not found ";
				return;
			}
			else
			{
				int curr = val;
				while(n[curr].chain != -1)
				{
					if(n[curr].name == nam)
						break;
					curr = n[curr].chain;
					curr = curr%(nam, sizeof(n)/sizeof(n[0]));
				}
				if(n[curr].name == nam)
				{
					for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
					{
						if(n[i].chain == curr)
						{
							n[i].chain = n[curr].chain;
							break;
						}
					}
					cout<< "DELETED "<< endl;
					n[curr].name = "DELETED";
					n[curr].num = "-1";
					n[curr].key = -2;

				}
				else
				{
					cout<< "Element not found ";
					return;
				}
			}
		}
	}
	void load()
	{
		int count = 0;
		for(int i = 0; i < sizeof(n)/sizeof(n[0]); ++i)
		{
			if(n[i].key != -1)
				count++;
		}
		cout<< ((float)count/(float)(sizeof(n)/sizeof(n[0])));
	}
};
int main()
{
	tele obj1, obj2;
	int dd, cc, d, c;
	do
	{
		cout<< "1. Linear probing without replacement with chaining ";
		cout<< endl<< "2. Linear probing with replacement with chaining "<< endl;
		cin>> cc;
		switch(cc)
		{
			case 1:
				do
				{
					cout<< endl<< "1. Insert"<< endl;
					cout<< "2. Search"<< endl;
					cout<< "3. Delete"<< endl;
					cin>> c;
					if(c == 1)
						obj1.input_1();
					else if(c == 2)
						obj1.search_1();
					else
						obj1.del_1();
					obj1.print();
					cout<< "LOAD FACTOR ->";
					obj1.load();
					cout<< endl;
					cout<< "Do you want to continue 0 or 1 ";
					cin>> d;
				}while(d != 0);
				break;

			case 2:
				do
				{
					cout<< endl<< "1. Insert"<< endl;
					cout<< "2. Search"<< endl;
					cout<< "3. Delete"<< endl;
					cin>> c;
					if(c == 1)
						obj2.input_2();
					else if(c == 2)
						obj2.search_2();
					else
						obj2.del_2();
					obj2.print();
					cout<< "LOAD FACTOR ->";
					obj2.load();
					cout<< endl;
					cout<< "Do you want to continue 0 or 1 ";
					cin>> d;
				}while(d != 0);
				break;

			}
			cout<< "Perform another type of hashing ? 0 or 1 ";
			cin>> dd;
	}while(dd != 0);
	return 0;
}