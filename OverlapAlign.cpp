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

int LCS(string v,string w,int vl,int wl,vector< vector<int> > &b,int &mi,int &mj)
{
	vector< vector<int> > s(vl+1 , vector<int> (wl+1) );
	int sigma = 2;
	
    for(int i=0;i<=vl;i++)
		s[i][0] = 0;

	for(int j=0;j<=wl;j++)
		s[0][j] = -j*sigma;

	v=" "+v;
	w=" "+w;

	int maxVal=0;
	int d;

	for(int i=1;i<=vl;i++)
	{
		for(int j=1;j<=wl;j++)
		{
			if( v[i] == w[j] )
				d=1;
			else
				d=-2;

			
			
				s[i][j] = max( s[i-1][j-1] + d , max(s[i-1][j],s[i][j-1]) - sigma );
			//~ cout<<v[i]<<":"<<w[j]<<" "<<s[i-1][j-1] + sc[v[i]][w[j]]<<"\t"<<s[i-1][j] - sigma<<"\t"<<s[i][j-1] - sigma<<"\t"<<s[i][j]<<endl;
			//~ if(s[i][j]==0 && j==1)
			//~ { b[i-1][j-1] = 4; }
			if( s[i][j] == (s[i-1][j-1] + d))
			{	b[i-1][j-1] = 3; }
			else if( s[i-1][j]>=s[i][j-1] )
			{
				
				b[i-1][j-1] = 1;

			}
			else
			{
				
				b[i-1][j-1] = 2;
			}

			if( i == vl)
			{
				if( s[i][j] > maxVal)
				{ maxVal=s[i][j]; mi = i-1; mj=j-1; }
			}		
			
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
//~ 
	//~ cout<<"mi mj "<<mi<<" "<<mj<<endl;
	
	return maxVal;
}

void OutputLCS(vector< vector<int> > &b,string &v,string &w, int i,int j,string &vans,string &wans)
{
	if(  j<0) 
	{
		return;
	}
	else
	{
		if(b[i][j] == 1)
		{	OutputLCS(b,v,w,i-1,j,vans,wans);
			wans = wans + "-";
			if( i < 0 )
				vans = vans + "-";
			else
				vans = vans + v[i];
		}
		else if(b[i][j] == 2)
		{	OutputLCS(b,v,w,i,j-1,vans,wans);
			if(j<0)
				wans = wans + "-";
			else
				wans = wans + w[j];
			vans = vans + "-";
		}
		else 
		{	OutputLCS(b,v,w,i-1,j-1,vans,wans);
			if(j<0)
				wans = wans + "-";
			else
				wans = wans + w[j];
			if( i < 0 )
				vans = vans + "-";
			else
				vans = vans + v[i];
		}
			
	}
}
void readScore(char *file,map< char, map<char,int> > &s)
{
	ifstream fp (file);
    string indel="-",tmp;
    vector<string> sym;
    vector<string>::iterator it;
    
    if (fp.is_open())
	{
		while ( fp.good() )
		{
			getline(fp,tmp);
			stringstream ss;
			
			ss<<tmp;
			
			while(ss>>tmp)
				sym.push_back(tmp);

			while(fp>>tmp)
			{
				REPC(it,sym)
					fp>>s[tmp[0]][(*it)[0]];
			}			
			
		}
	}
	fp.close();
}
			

int main()
{
	string v,w;
	cin>>v;
	cin>>w;

	int vl = v.length();
	int wl = w.length();

	vector< vector<int> > btrack(vl , vector<int> (wl) );
	
	int mi=0,mj=0;
	cout<<LCS(v,w,vl,wl,btrack,mi,mj)<<endl;	
	
    string vans,wans;
	OutputLCS(btrack,v,w,mi,mj,vans,wans);
	cout<<vans<<endl<<wans<<endl;
	
	return 0;
}

