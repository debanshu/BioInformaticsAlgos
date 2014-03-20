#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void output(vector<string> &b,int t)
{
    for(int i=0;i<t;i++)
	cout<<b[i]<<endl;
	
}
void fillBestRandom(vector<string> &b,vector<string> &dna,int k,int t)
{
    int s;
    srand(time(NULL));
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

void profileGibbs(vector< vector<double> > &p,vector<string> &b,int k,int t,int r)
{
    map<char,double> n;
    string tmp,bases="ATGC";
    
    for(int i=0;i<k;i++)
    {
	tmp="";
	for(int j=0;j<t;j++)
	{
	    if(j!=r) 
	    { tmp = tmp + b[j][i]; }
	}
	  
		
	for(int j=0;j<4;j++)
	{
	    n[bases[j]] = count(tmp.begin(),tmp.end(),bases[j]) + 1;
	    p[i][j] = n[bases[j]]/(2*(t-1));
	}
    }
}

string prgkmer(vector< vector<double> > &p, int k, string text)
{
    
    int l = text.length();
    string val = text.substr(0,k);
    double pval,prev;
    
    string t,bases="ATGC";
    map<char,int> pos;
    
    pos['A'] = 0;
    pos['T'] = 1;
    pos['G'] = 2;
    pos['C'] = 3;
    
    //~ for(int i=0;i<k;i++)
    //~ {
	//~ for(int j=0;j<4;j++)
	    //~ cout<<p[i][j]<<" ";
	//~ cout<<endl;
    //~ }
    //~ cout<<endl<<endl;
    
    vector<double> probs(l-k+1); 
    prev=0;
    
    for(int i=0; i<(l-k+1);i++)
    {
	t = text.substr(i,k);
	pval = 1;
	
	for(int j=0;j<k;j++)
	{
	    pval = pval * p[j][ pos[ t[j] ] ];
	}
	//~ cout<<pval<<" ";
	
	probs[i] = prev + pval;
	prev = probs[i];
	
	
    }
    
    for(int i=0; i<(l-k+1);i++)
    {
	probs[i] = probs[i]/prev;
	
    }
    
    
    double choice = (double)rand()/RAND_MAX;
    
    int kmer;
    for(int i=0; i<(l-k+1);i++)
    {
	if( choice<probs[i])
	{
	    kmer = i;
	    break;
	}
    }
    
    val = text.substr(kmer,k);
    
    
    return val;
    
}


void gS(vector<string> &dna,int k,int t,int N,vector<string> &bestMotifs)
{
    
    fillBestRandom(bestMotifs,dna,k,t);  
   
    int min = score(bestMotifs,k,t);
    int tmp,r;   
    srand(time(NULL)); 
    
    vector<string> motifs(t);    
    motifs = bestMotifs;
    vector< vector<double> > p(k,vector<double>(4));
    
    for(int i=0;i<N;i++)
    {
	r = rand()%t;
	
	profileGibbs(p,motifs,k,t,r);	    
	motifs[r] = prgkmer(p,k,dna[r]);
	
	tmp = score(motifs,k,t);
	if( tmp < min )
	{
	    min = tmp;
	    bestMotifs = motifs;
	}
    }
    
    //~ output(bestMotifs,t);
    
}

void gibbsSampler(vector<string> &dna,int k,int t,int N)
{
    vector<string> bestMotifs(t);
    int tmp;
    gS(dna,k,t,N,bestMotifs);
    int min = score(bestMotifs,k,t);
    
    vector<string> motifs(t);
    
    for(int i=1;i<20;i++)
    {
	gS(dna,k,t,N,motifs);
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
    int t,k,N;
    cin>>k;
    cin>>t;
    cin>>N;
    
    vector<string> dna;
    string tmp;
    while(cin>>tmp)
    {
	dna.push_back(tmp);
    }
    
    gibbsSampler(dna,k,t,N);
    
    return 0;
    
}
    
