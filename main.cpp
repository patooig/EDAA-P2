#include <iostream>
#include <sdsl/int_vector.hpp>

using namespace std;
using namespace sdsl;

int main(int argc, char * argv[]){

    vector<int_vector<8>>matriz;
    int n = atoi(argv[1]);
    int c;
    int i = 0;

    int_vector<8> iv(n);
    
    while(cin>>c){

        //Insertemos los primeros n en el int_vector<> iv//
        //Pasados los primeros n, push_back(iv);
        if(i==n){
            i = 0;
            matriz.push_back(iv);
        }
        iv[i] = c;
        i++;  

    }
    matriz.push_back(iv);

    

    int_vector<8>::iterator it;

    for (int i = 0; i < matriz.size(); i++)
    {
        for (it = matriz.at(i).begin() ; it != matriz.at(i).end(); it++)
        {
            cout << (int)*it << " ";
        }
        cout << endl;

    }
    
    


    return 0;
}