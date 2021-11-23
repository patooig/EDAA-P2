#include <iostream>
#include <sdsl/int_vector.hpp>
#include "Compacta.h"

using namespace std;
using namespace sdsl;

typedef vector<vector<bool>> vvb;

int main(int argc, char * argv[]){
    
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int c;
    int i = 0;
    int size_row = n;
    
    n = n*n*m;

    int_vector<8> iv(n);
    
    //Almacenamiento en el int_vector
    while(cin>>c){

        iv[i] = c;
        i++;

    }

    Compacta * nC = new Compacta(iv,size_row);

    nC->createBitmap();
    nC->createRRRVector();

    cout << "rank rrr: " << nC->rank_rrr(6)<<endl;

    cout << "rank rrr: " << nC->rank_rrr(7)<<endl;

    nC->createSDVector();

    cout << "rank sd: " << nC->rank_sd(6)<<endl;

    cout << "rank sd: " << nC->rank_sd(7)<<endl;

    cout<<"size k2 tree: "<<nC->createK2Tree()<<endl;

    nC->diferencias();

    
    

 
    delete nC;

    return 0;
}
