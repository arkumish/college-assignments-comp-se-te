#include <bits/stdc++.h>
using namespace std;
struct node
{
	string word, meaning;
	node *lt, *rt;
};
class dictionary
{
	node *root;

  public:
	dictionary()
	{
		root = NULL;
	}
	void insert(string, string);
	void display();
	void search();
	void dispdel();
	node *del(node *, string);
	void modify();
	void inorder(node *);
	bool searchdelete(node *, string s);
	void insertdata(int);
};

bool dictionary::searchdelete(node *root, string s)
{
	while (root != NULL)
	{
		if (s < root->word)
		{
			root = root->lt;
		}
		else if (s > root->word)
		{
			root = root->rt;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void dictionary::dispdel()
{
	if (root == NULL)
		cout << "\n Dictionary is EMPTY" << endl;
	else
	{
		cout << "\nEnter the word to delete" << endl;
		string s;
		cin >> s;
		if (searchdelete(root, s))
		{
			root = del(root, s);
			if (root == NULL)
			{
				cout << "\nDeletion successful" << endl;
				cout << "\nDictionary is now empty" << endl;
			}
			else
			{
				cout << "\nDeletion successful" << endl;
				cout << "\nDictionary after deletion " << endl;
				inorder(root);
			}
		}
		else
			cout << "\nNo word found" << endl;
	}
}
node *dictionary::del(node *n, string s)
{
	if (n == NULL)
		return NULL;
	else if (s < n->word)
	{
		n->lt = del(n->lt, s);
	}
	else if (s > n->word)
	{
		n->rt = del(n->rt, s);
	}
	else
	{
		if (n->lt == NULL && n->rt == NULL)        //no child
		{
			delete n;
			n = NULL;
			return n;
		}
		else if (n->lt == NULL)               //single child i.e right
		{
			node *t = n;
			n = n->rt;
			delete t;
			return n;
		}
		else if (n->rt == NULL)              //single child i.e left
		{
			node *t = n;
			n = n->lt;
			delete t;
			return n;
		}

		else
		{                                     //two child
			node *t = n->rt;

			while (t->lt != NULL)
				t = t->lt;

			n->word = t->word;
			n->meaning = t->meaning;
			
			n->rt = del(n->rt, t->word);
		}
	}
	return n;
}

void dictionary::search()
{
	int flag = 0;
	int cnt = 1;
	cout << "\nEnter the word to search : " << endl;
	string s;
	cin >> s;
	node *p = root;
	while (p != NULL)
	{
		if (s < p->word)
		{
			p = p->lt;
			cnt++;
		}
		else if (s > p->word)
		{
			p = p->rt;
			cnt++;
		}
		else
		{
			cout << "\nMeaning of " << s << " is : " << p->meaning << endl;
			cout << "\nNo. of comparison : " << cnt << endl;
			return;
		}
	}
	cout << "\nNo word found" << endl;
}

void dictionary::modify()
{
	cout << "\nEnter the word whose meaning is to be modified : " << endl;
	string s;
	cin >> s;
	node *p = root;
	while (p != NULL)
	{
		if (s < p->word)
			p = p->lt;
		else if (s > p->word)
			p = p->rt;
		else
		{
			cout << "\nEnter the new meaning of " << s << " : ";
			string n;
			cin >> n;
			p->meaning = n;
			return;
		}
	}
	cout << "\nNo word found" << endl;
}

void dictionary::insertdata(int flag)
{
	string s, m;
	if (flag == 0)
	{
		cout << "\nEnter the word and meaning : " << endl;

		cout << "\nEnter the word : ";
		cin >> s;
		cout << "\nEnter its meaning : ";
		cin >> m;
		ofstream f;
		f.open("d.txt", ios::app | ios::out);
		  f << endl<<s<<m;
		  f.close();

		insert(s, m);
	}
	else
	{
		ifstream fin;
		fin.open("d.txt");
		while (fin >> s >> m)
			insert(s, m);
		fin.close();
	}
}

void dictionary::insert(string s, string m)
{

	node *temp = new node;
	temp->word = s;
	temp->meaning = m;
	temp->lt = NULL;
	temp->rt = NULL;

	if (root == NULL)
	{
		root = temp;
	}
	else
	{
		node *p = new node;
		p = root;
		while (1)
		{
			if (temp->word <= p->word)
			{
				if (p->lt == NULL)
				{
					p->lt = temp;
					break;
				}
				else
				{
					p = p->lt;
				}
			}
			else
			{
				if (p->rt == NULL)
				{
					p->rt = temp;
					break;
				}
				else
				{
					p = p->rt;
				}
			}
		}
	}
}

void dictionary::inorder(node *n)
{
	if (n == NULL)
		return;
	inorder(n->lt);
	cout << n->word << "=" << n->meaning << endl;
	inorder(n->rt);
}

void dictionary::display()
{
	cout << "\nDisplay of Dictionary" << endl;

	inorder(root);
}

int main()
{
	string s;
	
	dictionary d1;
/*int n;
	cout<<"Enter total no. of elements to insert";
	cin>>n;
	while(n--){
	d1.insert();
	}*/
label:
	cout << "\nChoose one of following... : " << endl;
	cout << "\n1.Insert  \n2.Display \n3.Delete any word\n4.Search the meaning\n5.Modify the meaning \n6. Insert new word and meanining " << endl;
	int ch;
	cin >> ch;
	char choice;
	switch (ch)
	{
	case 1:
		d1.insertdata(1);
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;

	case 2:
		d1.display();
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;

	case 3:
		d1.dispdel();
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;

	case 4:
		d1.search();
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;

	case 5:
		d1.modify();
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;
	case 6:
		d1.insertdata(0);
		cout << "\nDo you want to continue[Y/N] : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			goto label;
		else
			break;
	}
	return 0;
}
