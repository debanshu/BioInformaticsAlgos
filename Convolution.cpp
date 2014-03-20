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

void computeConvolution(vector<int>& cv,vector<int>& spectrum)
{
    int l = spectrum.size();
    for(int i=0;i<l;i++)
    {
	for(int j=0;j<i;j++)
	    cv.push_back( spectrum[i] - spectrum[j] );
	    
    }
	    
}

int main(int argc,char* argv[])
{
    vector<int> spectrum;
    int num;   
    
    while(cin>>num)
	spectrum.push_back(num);
	
    sort(spectrum.begin(),spectrum.end());

    vector<int> convolution;
    computeConvolution(convolution,spectrum);
    
    sort(convolution.begin(),convolution.end());
    
    vector<int>:: iterator it;
    for(it = convolution.begin(); it!=convolution.end(); it++)
    {
	if( *it > 0)
	    cout<<*it<<" ";
    }

    
    cout<<endl; 
      
    return 0;
}
	
	    
