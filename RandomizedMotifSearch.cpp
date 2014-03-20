#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void output(vector<string> &b,int t)
{
    for(int i=0;i<t;i++)
	cout<<b[i]<<endl;
	
}
void fillBestRandom(vector<string> &b,vector<string> &dna,int k,int t)
{
    int s;
    for(int i=0;i<t;i++)
    {
	s = rand()%(dna[i].length()-k+1);
	b[i] = dna[i].substr(s,k);
    }
	
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
    
    for(int i=0;i<k;i++)
    {
	tmp="";
	for(int j=0;j<t;j++)
	    tmp = tmp + b[j][i];
	  
		
	for(int j=0;j<4;j++)
	{
	    n[bases[j]] = count(tmp.begin(),tmp.end(),bases[j]) + 1;
	    p[i][j] = n[bases[j]]/(2*t);
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
	
	for(int j=0;j<k;j++)
	{
	    pval = pval * p[j][ pos[ t[j] ] ];
	}
	
	if( pval > m)
	{
	    m = pval;
	    val = t;
	}
    }
    return val;
    
}

void genMotifs(vector< vector<double> > &p,vector<string> &dna,vector<string> &m,int k,int t)
{
    for(int i=0;i<t;i++)
    {
	m[i] = pmpkmer(p,k,dna[i]);
    }
}


void rMS(vector<string> &dna,int k,int t,vector<string> &bestMotifs)
{
    
    fillBestRandom(bestMotifs,dna,k,t);  
   
    int min = score(bestMotifs,k,t);
    int tmp;    
    
    vector<string> motifs(t);    
    motifs = bestMotifs;
    vector< vector<double> > p(k,vector<double>(4));
    
    while(true)
    {
	profile(p,motifs,k,t);	    
	genMotifs(p,dna,motifs,k,t);
	
	tmp = score(motifs,k,t);
	if( tmp < min )
	{
	    min = tmp;
	    bestMotifs = motifs;
	}
	else
	{
	    break;
	}
    }
    
    //~ output(bestMotifs,t);
    
}

void randomizedMotifSearch(vector<string> &dna,int k,int t)
{
    vector<string> bestMotifs(t);
    int tmp;
    rMS(dna,k,t,bestMotifs);
    int min = score(bestMotifs,k,t);
    
    vector<string> motifs(t);
    
    for(int i=1;i<1000;i++)
    {
	rMS(dna,k,t,motifs);
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
    
    randomizedMotifSearch(dna,k,t);
    
    return 0;
    
}
    
