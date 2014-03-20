#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>

using namespace std;

int occurs(string p1,string p2)
{
    int ret=0;
    int k = p1.length();
    for(int i=0;i<k;i++)
        if(p1[i]!=p2[i])
            ret++;
        
    return ret;
}


int countD(string text,string pat,int d)
{
    int l = text.length();
    int k = pat.length();
    int ret=0;
    
    for(int i=0;i<(l-k+1);i++)
    {
        if(occurs(pat,text.substr(i,k))<=d)
            ret++;
    }
    return ret;
}

void mutate(list<string> &kmers,string pat,int k,int d,int j,int b)
{
    if(j<d)
    {
        string tmp;
        for(int i=b;i<k;i++)
        {
            tmp=pat;
            if(tmp[i]=='A')
            {
                tmp[i]='T';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='T')
            {
                tmp[i]='A';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='G')
            {
                tmp[i]='A';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='T';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='C')
            {
                tmp[i]='A';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='T';
                kmers.push_back(tmp);
                mutate(kmers,tmp,k,d,j+1,i+1);
            }
        }
    }
} 

bool findall(list<string> &dna,string kmer,int d)
{    
    list<string>:: iterator itl;
    int val=0;
    for(itl=dna.begin();itl!=dna.end();itl++)
    {
	if(countD(*itl,kmer,d)>0)
	    val++;
    }
    
    if(val<dna.size())
	return false;
    return true;
    
}

void motifEnumeration(list<string> &dna,set<string> &kmers,int k,int d)
{
    set<string>:: iterator its;
    list<string>:: iterator itl;
    list<string> mutations;
    set<string> ans;
    
    
    for(its = kmers.begin();its!=kmers.end();its++)
    {
	mutations.clear();
	mutate(mutations,*its,k,d,0,0);
	for(itl=mutations.begin();itl!=mutations.end();itl++)
	{
	    if(findall(dna,*itl,d))
		ans.insert(*itl);
	}
    }
    
    for(its = ans.begin();its!=ans.end();its++)
	cout<<*its<<" ";
    cout<<endl;
}
	

int main()
{
    int k,d;
    cin>>k;
    cin>>d;
    list<string> dna;
    set<string> kmers;
    string t;
    while(cin>>t)
    {
	dna.push_back(t);
	for(int i=0;i<=t.length()-k;i++)
	    kmers.insert(t.substr(i,k));
    }
    
    set<string>:: iterator its;
    list<string>:: iterator itl;
    //~ cout<<"all kmers"<<endl;
    //~ for(it=kmers.begin();it!=kmers.end();it++)
	//~ cout<<*it<<" ";
	
    //~ list<string> mutations;
    //~ mutations.clear();
    //~ mutate(mutations,"ATC",k,d,0,0);
    //~ cout<<"Mutations of ATC"<<endl;
    //~ for(itl=mutations.begin();itl!=mutations.end();itl++)
	//~ cout<<*itl<<" ";
    
    motifEnumeration(dna,kmers,k,d);
    return 0;
}
