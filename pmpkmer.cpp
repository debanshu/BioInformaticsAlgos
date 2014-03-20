#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main()
{
    string text;
    int k;
    cin>>text;
    cin>>k;
    vector< vector<double> > p(k,vector<double>(4));
    map<char,int> n;
    string t;
    for(int i=0;i<4;i++)
    {
	cin>>t;
	n[t[0]] = i;
    }
	
    for(int i=0;i<k;i++)
    {
	for(int j=0;j<4;j++)
	{
	    cin>>p[i][j];
	}
    }
    
    int l = text.length();
    double max = 0;
    string val = "dummy";
    double pval;
    
    for(int i=0; i<(l-k+1);i++)
    {
	t = text.substr(i,k);
	pval = 1;
	for(int j=0;j<k;j++)
	{
	    pval = pval * p[j][ n[ t[j] ] ];
	}
	//~ cout<<" p:"<<pval<<"\tkmer: "<<t<<endl;
	if( pval > max)
	{
	    max = pval;
	    val = t;
	}
    }
    
    cout<<val<<endl;
    
    return 0;
    
}
    
