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


#define REPC(x,y) for( x = y.begin(); x!= y.end(); x++ )
using namespace std;

struct edge{
	int from,to,wt;
};

struct degree{
	int in,out;
};

stack<int> getZeroInDegrees(map<int, degree> &d)
{
	stack<int> ret;
	map<int, degree>:: iterator it;
	REPC(it,d)
	{
		if( it->second.in == 0)
		{	ret.push(it->first);
			//~ cout<<it->first<<endl;
			 }
	}
	return ret;
}

list<int> topoSort(map<int, list<edge> > &g,map<int, degree> d, int src)
{
	int a,b;
	list<int> sorted;
	list<edge>:: iterator it;
	stack<int> cands = getZeroInDegrees(d);
	//~ stack<int> cands;
	//~ cands.push(src);
	while(!cands.empty())
	{
		b = cands.top();
		
		cands.pop();
		sorted.push_back(b);

		REPC(it,g[b])
		{
			a= it->to;
			d[a].in--;
			if( d[a].in == 0)
				cands.push(a);
		}
	}
	return sorted;
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

void printSet(set<int> &c)
{
    set<int> ::iterator it;
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

int max(list<edge> &e,map<int,int> &s,map<int,int> &b,int src,set<int> &inPath)
{
	int max= 0 ,tmp,best=src;
	list<edge>::iterator it;
	cout<<"->";
	REPC(it,e)
	{
		if( inPath.count(it->from))
		{
			tmp = it->wt + s[it->from];
			cout<<it->from<<",";
			if(tmp>max)
			{
				max= tmp;
				best = it->from;
			}
		}
	}
	b[e.begin()->to] = best;
	return max;
}


int LongestPath(int src,int dest,list<int> &n,map<int, list<edge> > &g,list<int> &path,set<int>& inPath)
{
	list<int>::iterator it;
	map<int,int> s;
	REPC(it,n)
		s[*it] = 0;

	REPC(it,n)
		if(*it == src)
			break;

	//~ cout<<"backtracking"<<endl;
	map<int,int> btrack;
	cout<<*it;
	s[*it] = max(g[*it],s,btrack,src,inPath);
		cout<< endl<<"from "<<*it<<" to "<<btrack[*it]<<endl;
		cout<<endl;
	while(*it!=dest)
	{
		it++;
		cout<<*it;
		s[*it] = max(g[*it],s,btrack,src,inPath);
		cout<< endl<<"from "<<*it<<" to "<<btrack[*it]<<endl<<endl;;
	}

	cout<<"printing"<<endl;
	int cur= dest;
	path.push_front(cur);
	//~ cout<<cur;
	while( cur != src )
	{
		cur = btrack[cur];
		path.push_front(cur);
		//~ cout<<"->"<<cur;
		
	}
	
	return s[dest];
}
		
void dfs(map<int, list<edge> > &g,int src,set<int> &r)
{
	r.insert(src);
	list<edge>::iterator it;
	REPC(it,g[src])
		dfs(g,it->to,r);
}
		
void del(list<int> &s,set<int> &r)
{
	list<int>::iterator it;
	it = s.begin();
	while(it != s.end() )
	{
		if(!r.count(*it))
			it = s.erase(it);
		else
			it++;
	}
}

int main()
{
	int src,dest;
	map<int, list<edge> > adjList;
	map<int, list<edge> > preds;
	map<int, degree> degrees;
	scanf("%d%d",&src,&dest);
	//~ cout<<src<<" "<<dest<<endl;
	
	edge e;
	while(scanf("%d->%d:%d",&e.from,&e.to,&e.wt)==3)
	{
		adjList[e.from].push_back(e);
		preds[e.to].push_back(e);
		degrees[e.from].out++;
		degrees[e.to].in++;
		//~ cout<<e.from<<" "<<e.to<<" "<<e.wt<<endl;
	}

	list<int> sorted = topoSort(adjList,degrees,src);
	set<int> inPath ;
	dfs(adjList,src,inPath);
	printSet(inPath);

	del(sorted,inPath);
	list<int> path;
	printList(sorted);

	
	cout<<LongestPath(src,dest,sorted,preds,path,inPath)<<endl;
//~ 
	printList(path);
		
	//~ cout<<"done"<<endl;
	

	return 0;
}
	
	
