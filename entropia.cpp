#include<bits/stdc++.h>

using namespace std;

int main(){

    int c;

    map<int,int> m;

    while(cin>>c){


        if(m.count(c)==0){

            m[c]=1;
        }
        else{

            m[c]++;
        }

    }

    cout<<m[27]<<endl;

    return 0;
}
