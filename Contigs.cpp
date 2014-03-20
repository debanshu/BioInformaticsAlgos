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
using namespace std;
int k;
struct degree{
    int in;
    int out;
};
string suffix(string p)
{
    return p.substr(1,p.length()-1);
}

string prefix(string p)
{
    return p.substr(0,p.length()-1);
}
void inputAdjList(map< string, queue<string> > &adjList,map< string, struct degree > &d)
{
	string t,p,s;
	while(cin>>t)
    {
		p = prefix(t);
		s = suffix(t);
		adjList[p].push(s);
		d[s].in++;
		d[p].out++;
	
    }
    
    
}

	    
void DprintList(map< string,queue<string> > &g)
{
    map< string,queue<string> > :: iterator it;
    string i;
    for(it=g.begin(); it!= g.end(); it++)
    {
        i = it->first;
        cout<<i<<" -> "<<g[i].front();
        g[i].pop();
        while(!g[i].empty())
        {
            cout<<","<<g[i].front();
            g[i].pop();
        }
        cout<<endl;
    }
}

void getStarters(map< string, struct degree > &d,list<string> &s)
{
	map< string, struct degree >::iterator it;
	for(it=d.begin(); it!=d.end(); it++)
	{
		if( !((it->second.in==1) && (it->second.out==1) ))
		{
			s.push_back(it->first);
		}
	}
	
}

void outputContigs(map< string, queue<string> > &adjList,map< string, struct degree > &d)
{
	string cntg,cur,next;
	list<string> s;
	getStarters(d,s);
	
	list<string>::iterator it;
	for(it=s.begin();it!=s.end();it++)
	{
		cur = *it;
		cntg = cur;
		while(!adjList[cur].empty())
		{
			next = adjList[cur].front();
			cntg = cntg + next[k-2];
			if( ! ( (d[next].in==1) && (d[next].out==1)) )
			{
				cout<<cntg<<endl;
				cntg = next;
			}
			//~ d[cur].out--;
			//~ d[next].in--;
			adjList[cur].pop();
			cur = next;
		}
	}
}
			
	

    
int main()
{
    map< string, queue<string> > adjList;
    map< string, struct degree > degrees;
    inputAdjList(adjList,degrees);
    k = adjList.begin()->first.length()+1;

    //~ DprintList(adjList);
    

    outputContigs(adjList,degrees);
    
    //~ 
    //~ string initial = adjList.begin()->first;
    //~ 
    //~ 
    //~ string added = convertToCycle(adjList,degrees);
    //~ 
    //~ list<string> cycle;
    //~ 
    //~ eulerCycle(adjList,cycle,initial);
    //~ 
    //~ if(added!="")
	//~ cycleToPath(cycle,added);
    //~ 
    //~ printEdgeList(cycle);
    
    return 0;
    
    
}
    
    


