#include <iostream>
#include <string>
#include <map>
#include <set>

#define REP(i,a,b) for(int i=a;i<b;i++)

using namespace std;

string revC(string p)
{
    string ret=p;
    int l= p.length();
    for(int i=l-1;i>=0;i--)
    {
        if(p[i]=='A')
            ret[l-i-1]='T';
        if(p[i]=='G')
            ret[l-i-1]='C';
        if(p[i]=='T')
            ret[l-i-1]='A';
        if(p[i]=='C')
            ret[l-i-1]='G';
    }
    return ret;
}

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

void mismatch(map<string,int> &kmers,string pat,int k,int d,int j,int b)
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
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='T')
            {
                tmp[i]='A';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='G')
            {
                tmp[i]='A';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='T';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='C';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
            }
            else if(tmp[i]=='C')
            {
                tmp[i]='A';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='G';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
                tmp[i]='T';
                kmers[tmp]++;
                //kmers[revC(tmp)]++;
                mismatch(kmers,tmp,k,d,j+1,i+1);
            }
        }
    }
}
                
    
    
int main()
{
    map<string,int> kmers;    
    int k,d,max=0;
    string text,pat;
    
    cin>>text;
    cin>>k>>d;
    int l=text.length();
    
    
    for(int i=0;i<(l-k+1);i++)
    {
        pat = text.substr(i,k);
        
        kmers[pat]++;
        kmers[revC(pat)]++;        
        
        mismatch(kmers,pat,k,d,0,0);
        mismatch(kmers,revC(pat),k,d,0,0);
    }
    
    map<string,int>::iterator it;
    
    for(it=kmers.begin();it!=kmers.end();++it)
        if(it->second > max)
            max = it->second;
    
    
        /*
    cout<<"Diag:"<<endl;
    for(it=kmers.begin();it!=kmers.end();++it)
        cout<<it->first<<" "<<it->second<<endl;
    */
    
        
        
    for(it=kmers.begin();it!=kmers.end();++it)
        if(it->second == max)
            cout<<it->first<<" ";
    
    return 0;
}
