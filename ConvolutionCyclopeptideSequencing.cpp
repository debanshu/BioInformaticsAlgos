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
using namespace std;

map<char,int> table;

void buildTable(vector<int>& wts)
{
    char c='A';
    int l = wts.size();
    for(int i=0;i<l;i++)
    {
	table[c] = wts[i];
	c++;
    }    
    
   
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



void expand(list<string> &peps)
{
    list<string>::iterator it;
    map<char,int>:: iterator vals;
    list<string> tmp;
    string t;
    for(it=peps.begin();it!=peps.end();it++)
    {
	t = *it;
	for(vals = table.begin();vals!=table.end();vals++)
	{
	    tmp.push_back(t+ (vals->first));
	}
    }
    peps.clear();
    peps.splice(peps.end(),tmp);
}

void pepPrintWts(string peptide)
{
    int l=peptide.length();
    cout<<table[peptide[0]];
    for(int i=1;i<l;i++)
	cout<<"-"<<table[peptide[i]];
    
    cout<<" ";
}

int score(string p,vector<int> &spectrum)
{
    vector<int> tmp;
    Cyclospectrum(tmp,p); 
    return score(tmp,spectrum);
}

struct pep {
	string p;
	int score;
};
    
bool pepCompare( pep i,pep j) { return (i.score > j.score); }

void cut(list<string> &peps,vector<int> &spectrum,int N)
{    
    list<pep> compList;
    pep val;
    list<string>::iterator peptide;
    for( peptide = peps.begin(); peptide!=peps.end(); peptide++)
    {
	val.p = *peptide;
	val.score = score(val.p,spectrum);
	compList.push_back(val);
    }
    compList.sort (pepCompare);
    
    list<pep>::iterator pepstruct;
    
    peps.clear();
    pepstruct = compList.begin();
    int sc;
    
    while( (N>0 ) && (pepstruct!=compList.end()) )
    {
	peps.push_back(pepstruct->p);
	sc = pepstruct->score;
	N--;
	pepstruct++;	
    }
    
    while( (sc == pepstruct->score) && (pepstruct!=compList.end()) )
    {
	peps.push_back(pepstruct->p);
	pepstruct++;	
    }    
    
}
  

void leaderboardCyclopeptideSequencing(vector<int> &spectrum,int pMass,int N)
{
    list<string> Leaderboard; 
    list<pep> finals;   
    pep v;
    
    list<string>::iterator peptide,curr;
    Leaderboard.push_back("");
    string LeaderPeptide = "";
    int maxSc = score(LeaderPeptide,spectrum);
    int tmp,mass;
    
    while( !Leaderboard.empty())
    {
	expand(Leaderboard);
		
	peptide = Leaderboard.begin();
	while( peptide != Leaderboard.end() )
	{	    
	    curr = peptide;
	    peptide++;
	    
	    mass = weight(*curr);
	    if( mass == pMass)
	    {
		tmp = score(*curr,spectrum);
		v.p = *curr;
		v.score = tmp;
		finals.push_back(v);

		if( tmp> maxSc )
		{
		    maxSc = tmp;
		    LeaderPeptide = *curr;
		}
	    }
	    else if(mass > pMass)
	    {
		Leaderboard.erase(curr);
	    }
	}
	
	cut(Leaderboard, spectrum, N);
    }
    
    finals.sort (pepCompare);
    
    list<pep>::iterator pepstruct;
    int pr =23 ;
    pepstruct = finals.begin();
    while(pr--)
    {
	pepPrintWts(pepstruct->p);
	//~ cout<<" : "<<pepstruct->score<<endl;
	cout<<endl;
	pepstruct++;
    }
    cout<<endl;
    
    //~ cout<<LeaderPeptide<<endl;
    pepPrintWts(LeaderPeptide);
    cout<<endl;
    
}

void computeConvolution(vector<int>& cv,vector<int>& spectrum)
{
    int l = spectrum.size();
    int tmp;
    for(int i=0;i<l;i++)
    {
	for(int j=0;j<i;j++)
	{
	    tmp = spectrum[i] - spectrum[j] ;
	    if( tmp>=57 && tmp<=200 )
		cv.push_back(tmp );
	}
	    
    }
	    
}

struct pepCount {
    int wt;
    int count;
};

bool countCompare( pepCount i,pepCount j) { return (i.count > j.count); }

void getFrequent(vector<int>& top,vector<int>& cv,int M)
{
    sort(cv.begin(),cv.end());
    list<pepCount> peps;
    int l = cv.size();
    
    pepCount val;
    val.wt = cv[0];
    val.count = 1;
    
    int i=1;
    while(i<l)
    {
	if( cv[i] != cv[i-1] )
	{
	    peps.push_back(val);
	    val.wt = cv[i];
	    val.count = 1;
	}
	else
	{
	    val.count++;
	}
	i++;
    }
    
    peps.push_back(val);
    peps.sort(countCompare);
    
    list<pepCount>::iterator pepstruct;
    
    top.clear();
    pepstruct = peps.begin();
    int sc;
    
    while( (M>0 ) && (pepstruct!=peps.end()) )
    {
	top.push_back(pepstruct->wt);
	sc = pepstruct->count;
	M--;
	pepstruct++;	
    }
    
    while( (sc == pepstruct->count) && (pepstruct!=peps.end()) )
    {
	top.push_back(pepstruct->wt);
	pepstruct++;	
    }
}
    

int main(int argc,char* argv[])
{
   
    vector<int> spectrum;
    int num,N,M,pmass= 0 ;
    cin>>M;
    cin>>N;
    
    while(cin>>num)
	spectrum.push_back(num); 
    
    sort(spectrum.begin(),spectrum.end());
    pmass = spectrum[spectrum.size()-1];
    
    vector<int> convolution;
    computeConvolution(convolution,spectrum); 
    
    vector<int> top;
    getFrequent(top,convolution,M);
    buildTable(top);
    
    leaderboardCyclopeptideSequencing(spectrum,pmass,N);
    
    //~ for(vector<int>::iterator it=top.begin();it!=top.end();it++)
	//~ cout<<*it<<" ";
    //~ cout<<endl;
    
    
    
    //~ map<char,int>:: iterator vals;
    //~ for(vals = table.begin();vals!=table.end();vals++)
    //~ {
	//~ cout<<vals->first<<" : "<<vals->second<<endl;
    //~ }
    
    
    cout<<endl; 
      
    return 0;
}
	
	    
