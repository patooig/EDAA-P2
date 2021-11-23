#ifndef _NOMBRECLASE_
#define _NOMBRECLASE_
#include <sdsl/int_vector.hpp>
#include <sdsl/rrr_vector.hpp>
#include <sdsl/sd_vector.hpp>
#include <stdlib.h>
#include <vector>

using namespace sdsl;
using namespace std;

class Compacta{
    private:
    int size_k2=0;  // Tamaño de todos los k2 tree
    int_vector<8> iv; // v
    bit_vector bv;  // bit vector
    vector<int> v_p; // vector temporal, almacena v'
    int_vector<8> v; // v'
    int ivSize; //Cantidad de elementos del int_vector
    int rowSize; //Cantidad de elementos por fila

    //Parte 4
    rrr_vector<> * rv;
    sd_vector<> * sv;
    rrr_vector<>::rank_1_type rank_rrr1;
    sd_vector<>::rank_1_type rank_sd1;
    
    //Parte 6
    int_vector<4> vdif;
    bit_vector signo;

    bool first;

    void vectorToIntVector();
    void deletevK2();

    

    public: 
    Compacta(const int_vector<8> &ivv, int rS);
    ~Compacta();
    void createRRRVector();
    void createBitmap();
    int createK2Tree();
    double calculateEntropy();
    void createSDVector(); 
    int rank_rrr(int i);
    int rank_sd(int i);
    void diferencias();
};

#endif