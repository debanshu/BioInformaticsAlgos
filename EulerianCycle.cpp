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
using namespace std;

void inputAdjList(map< int, stack<int> > &adjList)
{
    int n,i;  
    
    string tmp;
    char line[1000],*delim=",";
    char *tok;
    while(cin>>i)
    {
	
	cin>>tmp;
	cin>>line;
	
	tok = strtok(line,delim);
	while(tok!= NULL )
	{
	    n = atoi(tok);
	    
	    adjList[i].push(n);
	    tok = strtok(NULL,delim);
	}
	
    }
    
}

void DprintList(map< int, stack<int> > &g, int l)
{
    for(int i=0;i<l;i++)
    {
	
	cout<<i<<" -> "<<g[i].top();
	g[i].pop();
	while(!g[i].empty())
	{
	    cout<<","<<g[i].top();
	    g[i].pop();
	}
	cout<<endl;
    }
}
void formCycle(map< int, stack<int> > &g, list<int> &c, int beg)
{
    int tmp = beg,next=-1;
    c.push_back(tmp);
    while(next!=beg)
    {
	next = g[tmp].top();
	g[tmp].pop();	
	c.push_back(next);
	tmp = next;
    }
}

list<int>::iterator unexplored(map< int, stack<int> > &g, list<int> &c)
{
    list<int>::iterator it;
    for( it = c.begin();it!=c.end();it++)
    {
	if( !g[*it].empty() )
	    return it;
    }
    
    return it;
}
    
void eulerCycle(map< int, stack<int> > &g, list<int> &c,int l)
{
    list<int> tmp;
    formCycle(g,c,l);
    list<int>:: iterator un; 
    
    while( (un=unexplored(g,c)) != c.end() )
    {
	formCycle(g,tmp,*un);
	un = c.erase(un);
	c.splice(un,tmp);
    }
}    

void printList(list<int> &c)
{
    list<int> ::iterator it;
    it = c.begin();
    cout<<*it;
    it++;
    while(it!=c.end())
    {
	cout<<"->"<<*it;
	it++;
    }
    cout<<endl;
}
    
int main()
{
    map< int, stack<int> > adjList;
    inputAdjList(adjList);
    
    //~ DprintList(adjList,s);
    
    list<int> cycle;
    eulerCycle(adjList,cycle,0);
    printList(cycle);
    
    return 0;
    
    
}
    
    


