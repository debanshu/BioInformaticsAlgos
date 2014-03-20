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
using namespace std;
string suffix(string p)
{
    return p.substr(1,p.length()-1);
}

string prefix(string p)
{
    return p.substr(0,p.length()-1);
}


void printList(map< string,set<string> > &g)
{
    map< string,set<string> > :: iterator it;
    set<string>::iterator s;
    for(it=g.begin(); it!= g.end(); it++)
    {
	s = (it->second).begin();
	cout<<it->first<<" -> "<<*s;
	s++;
	while(s!= (it->second).end())
	{
	    cout<<","<<*s;
	    s++;
	}
	cout<<endl;
    }
}

int main()
{
    string t;
    
    map< string,set<string> > adjList;
    
    while(cin>>t)
    {
	adjList[prefix(t)].insert(suffix(t));
    }

    printList(adjList);
    
    //~ for(int i=0;i<(l-k+1);i++)
	//~ cout<<kmers[i]<<endl;
	
    return 0;
    
}
    
    


