#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    string text,tmp;
    int min,l,screw;
    min=2;
    cin>>text;
    
    l=text.length();
    
    screw=0;
    for(int i=0;i<l;i++)
    {
        if(text[i]=='G')
            screw++;
        if(text[i]=='C')
            screw--;
        
        //cout<<screw<<" ";
        if(screw<min)
            min=screw;        
        
    }
    screw=0;
    for(int i=0;i<l;i++)
    {
        if(text[i]=='G')
            screw++;
        if(text[i]=='C')
            screw--;
        
        //cout<<screw<<" ";
        if(screw==min)
            cout<<i+1<<" ";       
        
    }
    
    
    
    return 0;
}
