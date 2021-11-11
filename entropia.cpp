#include<bits/stdc++.h>
#include<math.h>

using namespace std;

int main(){

    int c;
    int contador;
    map<int,int> m;
    map<int,int>::iterator it;

    while(cin>>c){

        contador++;
        if(m.count(c)==0){

            m[c]=1;
        }
        else{

            m[c]++;
        }

    }

    //cout<<m[27]<<endl;

    int h = 0;

    for(it = m.begin(); it != m.end(); it++){

        h += (it->second / contador) * log2(contador / it->second);
    }

    cout<<h<<endl;
    return 0;
}
