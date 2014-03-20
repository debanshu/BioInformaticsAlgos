#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void output(vector<string> &b,int t)
{
    for(int i=0;i<t;i++)
	cout<<b[i]<<endl;
	
}
void fillBest(vector<string> &b,vector<string> &dna,int k,int t)
{
    for(int i=0;i<t;i++)
	b[i] = dna[i].substr(0,k);
	
}

  

int score(vector<string> &b,int k,int t)
{
    int tot,m,sc = 0;
    map<char,int> n;
    string tmp,bases="ACGT";
    
    for(int i=0;i<k;i++)
    {
	tmp="";
	for(int j=0;j<t;j++)
	    tmp = tmp + b[j][i];
	    
	
	m= 0;
	tot = 0;
	for(int j=0;j<4;j++)
	{
	    n[bases[j]] = count(tmp.begin(),tmp.end(),bases[j]);
	    m = max(m,n[bases[j]]);
	    tot += n[bases[j]];
	}
	sc += ( tot - m );
    }
    return sc;
}

void profile(vector< vector<double> > &p,vector<string> &b,int k,int t)
{
    map<char,double> n;
    string tmp,bases="ATGC";
    //~ map<char,int> pos;
    //~ for(int j=0;j<4;j++)
    //~ {
	//~ pos[bases[j]] = j;
    //~ }
    //~ output(b,t);
    //~ cout<<endl;
    for(int i=0;i<k;i++)
    {
	tmp="";
	for(int j=0;j<t;j++)
	    tmp = tmp + b[j][i];
	    
	
	//~ cout<<tmp<<endl;
	for(int j=0;j<4;j++)
	{
	    n[bases[j]] = count(tmp.begin(),tmp.end(),bases[j]);
	    //~ cout<<j<<" : "<<n[bases[j]]<<endl;
	    if( n[bases[j]] == 0)
		p[i][j] = 0;
	    else
		p[i][j] = n[bases[j]]/t;
	}
    }
}

string pmpkmer(vector< vector<double> > &p, int k, string text)
{
    
    int l = text.length();
    double m = 0;
    string val = text.substr(0,k);
    double pval;
    
    string t,bases="ATGC";
    map<char,int> pos;
    
    pos['A'] = 0;
    pos['T'] = 1;
    pos['G'] = 2;
    pos['C'] = 3;
    
    
    
    for(int i=0; i<(l-k+1);i++)
    {
	t = text.substr(i,k);
	pval = 1;
	//~ cout<<"done5"<<endl;
	for(int j=0;j<k;j++)
	{
	    pval = pval * p[j][ pos[ t[j] ] ];
	}
	//~ cout<<" p:"<<pval<<"\tkmer: "<<t<<endl;
	if( pval > m)
	{
	    m = pval;
	    val = t;
	}
    }
    return val;
    
}
    


void greedyMotifSearch(vector<string> &dna,int k,int t)
{
    vector<string> bestMotifs(t);
    fillBest(bestMotifs,dna,k,t);
    
   
    
    int min = score(bestMotifs,k,t);
    int tmp;
    
    
    vector<string> motifs(t);
    string text = dna[0];
    int l = text.length();
    string kmer;
    
    vector< vector<double> > p(k,vector<double>(4));
    
    for(int i=0;i<(l-k+1);i++)
    {
	
	kmer = text.substr(i,k);
	motifs[0] = kmer;
	
	//~ cout<<"done3"<<endl;
	
	for(int j=1;j<t;j++)
	{
	    
	    profile(p,motifs,k,j);
	    //~ cout<<"done4"<<endl;
	    //~ for(int i2=0;i<k;i++)
	    //~ {
		//~ for(int j2=0;j<4;j++)
		    //~ cout<<p[i2][j2]<<" ";
		//~ cout<<endl;
	    //~ }
	    motifs[j] = pmpkmer(p,k,dna[j]);
	    
	}
	
	tmp = score(motifs,k,t);
	if( tmp < min )
	{
	    min = tmp;
	    bestMotifs = motifs;
	}
    }
    
    output(bestMotifs,t);
    
}

int main()
{
    int t,k;
    cin>>k;
    cin>>t;
    
    vector<string> dna;
    string tmp;
    while(cin>>tmp)
    {
	dna.push_back(tmp);
    }
    
    greedyMotifSearch(dna,k,t);
    
    return 0;
    
}
    
