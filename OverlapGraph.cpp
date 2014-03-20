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
string suffix(string p)
{
    return p.substr(1,p.length()-1);
}

string prefix(string p)
{
    return p.substr(0,p.length()-1);
}


int main()
{
    vector<string> input;
    string t;
    while(cin>>t)
	input.push_back(t);
	
    int l = input.size();
    for(int i=0;i<l;i++)
    {
	for(int j=0;j<l;j++)
	{
	    if( (i!=j) && ( suffix(input[i]) == prefix(input[j])) )
		cout<<input[i]<<" -> "<<input[j]<<endl;
	}
    }
    return 0;
}

    

