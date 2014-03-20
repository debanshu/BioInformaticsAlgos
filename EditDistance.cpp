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

#define REPC(x,y) for( x = y.begin(); x!= y.end(); x++ )

using namespace std;

int editDistance(string v,string w)
{
	
	int vl = v.length();
	int wl = w.length();
	vector< vector<int> > s(vl+1 , vector<int> (wl+1) );
	
	
    for(int i=0;i<=vl;i++)
		s[i][0] = i*1;

	for(int j=0;j<=wl;j++)
		s[0][j] = j*1;

	v=" "+v;
	w=" "+w;

	int d;

	for(int i=1;i<=vl;i++)
	{
		for(int j=1;j<=wl;j++)
		{
			if( v[i] == w[j] )
				d=0;
			else
				d=1;

			s[i][j] = min( s[i-1][j-1] + d, min( s[i-1][j],s[i][j-1]) + 1 );
		}
	}
	
	//~ cout<<endl;
	//~ cout<<"S\t";
	//~ for(int j=0;j<=wl;j++)
		//~ cout<<w[j]<<"\t";
	//~ cout<<endl;
	//~ for(int i =0 ;i<=vl;i++)
	//~ {
		//~ cout<<v[i]<<"\t";
		//~ for(int j=0;j<=wl;j++)
			//~ cout<<s[i][j]<<"\t";
		//~ cout<<endl;
	//~ }
	
	return s[vl][wl];
}

			

int main()
{
	string v,w;
	cin>>v;
	cin>>w;
	
	cout<<editDistance(v,w)<<endl;	
    
	return 0;
}

