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

//     cout << "tamaño iv: " << size_in_bytes(iv) << endl;

    nC->createBitmap();
    nC->createRRRVector();
    nC->createSDVector();

    double time_rrr = 0;
    double time_sd  = 0;

    int num;
    // RANK RRR_VECTOR
//     clock_t start;
//
//     for (int i = 0; i < 100; i++){
//         num = 1 + rand()%(n-1);
//
//         start = clock();
//
//         nC->rank_rrr(num);
//
//         time_rrr+= (double)(clock()-start)/CLOCKS_PER_SEC;
//     }
//
//     printf("rank por rrr_vector: %.8f\n", (double)time_rrr/100);
//
//     // RANK SD_VECTOR
//     for (int i = 0; i < 100; i++)
//     {
//         num = 1 + rand()%(n-1);
//         start = clock();
//         nC->rank_sd(num);
//         time_sd +=(double)(clock()-start)/CLOCKS_PER_SEC;
//     }
//
//     printf("rank por sd_vector : %.8f\n", (double)time_sd/100);
//
//     cout << "rank rrr: " << nC->rank_rrr(6)<<endl;
//
//     cout << "rank rrr: " << nC->rank_rrr(7)<<endl;
//
//     //nC->createSDVector();
//
//     cout << "rank sd: " << nC->rank_sd(6)<<endl;
//
//     cout << "rank sd: " << nC->rank_sd(7)<<endl;
//
//     cout<<"size k2 tree: \n"<<nC->createK2Tree()<<endl;

        nC->diferencias();

//     cout << "Entropia " <<nC->calculateEntropy()<<endl;

    
    

 
    delete nC;

    return 0;
}
