#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main()
{
    map<string,int> kmers;
    map<string,int>::iterator itd;
    set<string> output;
    string text,tmp;
    int k,L,t,l;
    
    cin>>text;
    cin>>k>>L>>t;
    l=text.length();
    //text = text + text.substr(0,L);
    //cout<<text<<endl;
    //l=text.length();
    //cout<<k<<" "<<L<<" "<<t<<endl<<text;
    
    for(int i=0;i<(l-L+1);i++)
    {
        for(int j=0;j<(L-k+1);j++)
        {
            tmp = text.substr(i+j,k);
            if(kmers.count(tmp))
                kmers[tmp]++;
            else
                kmers[tmp]=1;
            
            if(kmers[tmp]>=t)
                output.insert(tmp);
            
        }
        /*
        cout<<"Values diag"<<endl;
        for(itd=kmers.begin();itd!=kmers.end();itd++)
            cout<<itd->first<<"\t"<<itd->second<<endl;
        
        cout<<endl;
        */
        kmers.clear();
    }
    
    set<string>::iterator it;
    for(it=output.begin();it!=output.end();++it)
        cout<<*it<<" ";
    
    return 0;
}
