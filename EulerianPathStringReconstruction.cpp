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

struct degree{
    int in;
    int out;
};

void inputAdjList(map< string, stack<string> > &adjList,map< string, struct degree > &d)
{
    string n,i;  
    
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
	    n = string(tok);
	    //~ cout<<n<<endl;
	    
	    adjList[i].push(n);
	    d[i].out++;
	    d[n].in++;
	    tok = strtok(NULL,delim);
	}
	
    }
    
}


void formCycle(map< string, stack<string> > &g, list<string> &c, string beg)
{
    string tmp = beg,next="";
    c.push_back(tmp);
    while(next!=beg)
    {
	next = g[tmp].top();
	g[tmp].pop();	
	c.push_back(next);
	tmp = next;
    }
}

list<string>::iterator unexplored(map< string, stack<string> > &g, list<string> &c)
{
    list<string>::iterator it;
    for( it = c.begin();it!=c.end();it++)
    {
	if( !g[*it].empty() )
	    return it;
    }
    
    return it;
}
    
void eulerCycle(map< string, stack<string> > &g, list<string> &c,string l)
{
    list<string> tmp;
    formCycle(g,c,l);
    list<string>:: iterator un; 
    
    while( (un=unexplored(g,c)) != c.end() )
    {
	formCycle(g,tmp,*un);
	un = c.erase(un);
	c.splice(un,tmp);
    }
}    

void printEdgeList(list<string> &c)
{
    list<string> ::iterator it;
    it = c.begin();
    int l = it->length();
    l--;
    cout<<*it;
    it++;
    while(it!=c.end())
    {
	cout<<(*it)[l];
	it++;
    }
    cout<<endl;
}

string convertToCycle(map< string, stack<string> > &adjList,map< string, struct degree > &d)
{
    string from="",to="";
    map< string, struct degree > :: iterator it;
    struct degree tmp;
    it = d.begin();
    while( ((from=="") || (to== "")) && (it!=d.end()) )
    {
	tmp = it->second;
	
	if( tmp.in < tmp.out )
	    to = it->first;
	    
	if( tmp.in > tmp.out )
	    from = it->first;
	 
	it++;    
    }
    
    if( from!= "" && to!="")
	adjList[from].push(to);
	
    //~ cout<<"from :"<<from<<endl;
    //~ cout<<"to :"<<to<<endl;
    return from;
    
}

void cycleToPath(list<string> &c,string t)
{
    list<string>::iterator it;
    list<string> ret;
    c.erase(c.begin());
    for( it = c.begin(); it!= c.end(); it++)
    {
	if( *it == t )
	{
	    it++;
	    ret.splice(ret.begin(),c,it,c.end());
	    ret.splice(ret.end(),c);
	    break;
	}
    }
    c = ret;
}
	    
	    
    
int main()
{
    map< string, stack<string> > adjList;
    map< string, struct degree > degrees;
    inputAdjList(adjList,degrees);
    
    //~ cout<<"input done!"<<endl;
    string initial = adjList.begin()->first;
    //~ cout<<"initial: "<<initial<<endl;
    
    //~ cout<<degrees["CCA"].in<<endl;
    //~ cout<<degrees["CCA"].out<<endl;
    
    
    string added = convertToCycle(adjList,degrees);
    //~ cout<<"added: "<<added<<endl;
    //~ DprintList(adjList,s);
    
    list<string> cycle;
    
    eulerCycle(adjList,cycle,initial);
    
    if(added!="")
	cycleToPath(cycle,added);
    //~ 
    printEdgeList(cycle);
    
    return 0;
    
    
}
    
    


