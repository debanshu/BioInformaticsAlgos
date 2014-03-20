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

void composition(string kmers[],string text,int k,int l)
{
    
    for(int i=0;i<(l-k+1);i++)
	kmers[i] = (text.substr(i,k));
	
    sort(kmers,kmers+(l-k+1));
}

void overlapGraph(string input[],int l,map< string,set<string> > &g)
{
    for(int i=0;i<l;i++)
    {
	for(int j=0;j<l;j++)
	{
	    if( (i!=j) && ( suffix(input[i]) == prefix(input[j])) )
		g[input[i]].insert(input[j]);
	}
    }
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

void dBfromString(map< string,set<string> > &g,string text,int k)
{
    int l =text.length();
    string n,n1,n2;
    for(int i=0;i<(l-k+1);i++)
    {
	n=text.substr(i,k);
	n1= n.substr(0,k-1);
	n2= n.substr(1,k-1);
	g[n1].insert(n2);
    }
}


int main()
{
    int k;
    string text;
    map< string,set<string> > adjList;
    cin>>k;
    cin>>text;
    
    
    int l = text.length();
    k--;
    
    string* kmers=new string[(l-k+1)];
    composition(kmers,text,k,l);   
    //~ 
    overlapGraph(kmers,(l-k+1),adjList);
    //~ dBfromString(adjList,text,k);
    
    printList(adjList);
    
    //~ for(int i=0;i<(l-k+1);i++)
	//~ cout<<kmers[i]<<endl;
	
    return 0;
    
}
    
    


