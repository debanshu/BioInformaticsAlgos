#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <algorithm>    // std::sort
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <sstream>

#define REPC(iterator,container) for( iterator = container.begin(); iterator!= container.end(); iterator++ )

using namespace std;

typedef map<char,int> node;

void getTrie(vector<node> &t,list<string> &pat)
{
	list<string>::iterator it;
	int l,cur=0,tot=1;
	
	node* tmp = new node;
	t.push_back(*tmp);
	


	REPC(it,pat)
	{
		cur=0;
		l= it->length();
		for(int i=0;i<l;i++)
		{
			if(t[cur].count((*it)[i]) == 0)
			{
				//~ cout<<"pushing new "<<((*it)[i])<<endl;				
				t[cur][(*it)[i]] = tot;
				tmp = new node;
				t.push_back(*tmp);
				cur=tot;
				tot++;
				
			}
			else
			{
				cur = t[cur][(*it)[i]];
			}
		}
	}
			
	
}

void printTrie(vector<node> &t)
{
	node::iterator it;

	for(int i=0;i<t.size();i++)
	{
		REPC(it,t[i])
		{
			cout<<(i+1)<<" "<<(it->second)+1<<" "<<it->first<<endl;
		}
	}
}
	
int main()
{
	vector<node> t;
	string tmp;
	list<string> pat;
	while(cin>>tmp)
		pat.push_back(tmp);

	getTrie(t,pat);
	printTrie(t);

	//~ cout<<t[0].size()<<endl;

	return 0;
}
	
	
