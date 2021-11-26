#include <iostream>
#include <sdsl/int_vector.hpp>
#include "Compacta.h"

using namespace std;
using namespace sdsl;

typedef vector<vector<bool>> vvb;

int main(int argc, char * argv[]){
    
    int n = atoi(argv[1]);   //Número de filas.
    int m = atoi(argv[2]);   //Número de matrices.
    int c;
    int i = 0;
    int size_row = n; //Cantidad de elementos en una fila
    
    n = n*n*m; //Cantidad total de elementos del dataset

    int_vector<8> iv(n);
    
    //Lectura del archivo y almacenamiento en el int_vector
    while(cin>>c){

        iv[i] = c;
        i++;
    }


    //Creación del objeto nC de la clase 'Compacta'
    //En su constructor se entrega el int_vector con los elementos
    //Del dataset y la cantidad de elementos por fila.
    Compacta * nC = new Compacta(iv,size_row);

    //Creamos bitmap
    nC->createBitmap();

    //Creamos rrrvector
    nC->createRRRVector();

    //Creamos sdvector
    nC->createSDVector();

    //Creamos K2-TREE
    nC->createK2Tree();

    //Creamos Matriz con diferencias
    nC->diferencias();

    
    
    //Variables para calcular tiempo
//    double time_rrr = 0;
//    double time_sd  = 0;

//     int num;
//     RANK RRR_VECTOR
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

    

//     cout << "Entropia " <<nC->calculateEntropy()<<endl;

    
    //Liberamos nC
    delete nC;

    return 0;
}
