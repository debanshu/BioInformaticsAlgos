#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;

map<char,int> table;



void readTable()
{
    ifstream fp ("integer_mass_table.txt");
    string P;
    int val;
    
    if (fp.is_open())
  {
    while ( fp.good() )
    {
	fp>>P;
	if(P.length() == 1)
	{
	    fp>>val;
	    table[P[0]] = val;
	}
	
    }
}
    fp.close();
}

int weight(string peptide)
{
    int wt=0,l=peptide.length();
    for(int i=0;i<l;i++)
	wt=wt+table[peptide[i]];
    return wt;
}

void Cyclospectrum(vector<int> &ret,string peptide)
{
    ret.clear();
    ret.push_back(0);
    ret.push_back(weight(peptide));
    int n = peptide.length();
    peptide += peptide.substr(0,n-1);
    for(int i=1;i<=n-1;i++)
    {
	for(int j=0;j<n;j++)
	{
	    ret.push_back(weight(peptide.substr(j,i)));
	}
    }
    sort(ret.begin(),ret.end());
        
}    

int score(vector<int> &v,vector<int> &spectrum)
{
    int sc=0;
    vector<int>::iterator it;
    vector<int>::iterator element;
    element = spectrum.begin();
    for(it = v.begin();it!=v.end();it++)
    {
	while( (*element < *it) && (element!=spectrum.end()))
	    element++;
	if( *element == *it)
	{
	    sc++;
	    element++;
	}
	
    }
    return sc;
}


int main(int argc,char* argv[])
{
    readTable();
    string peptide;

    cin>>peptide;
    
    vector<int> ret,spectrum;
    int num;
    while(cin>>num)
	spectrum.push_back(num);
	
    
    
    Cyclospectrum(ret,peptide);    
    cout<<score(ret,spectrum)<<endl;
    
    //~ for(vector<int>::iterator it=ret.begin();it!=ret.end();it++)
	//~ cout<<*it<<" ";
    //~ cout<<endl;
    //~ 
    
    
    return 0;
}
	
	
