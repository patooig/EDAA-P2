#ifndef _NOMBRECLASE_
#define _NOMBRECLASE_
#include <sdsl/int_vector.hpp>
#include <sdsl/k2_tree.hpp>
#include <vector>

using namespace sdsl;
using namespace std;

class nombreClase{
    private:
    int_vector<8> iv; // v
    bit_vector bv;  // bit vector
    vector<int> v_p; // vector temporal, almacena v'
    int_vector<8> v; // v'
    int ivSize; //Cantidad de elementos del int_vector
    int rowSize; //Cantidad de elementos por fila
    void vectorToIntVector();

    

    public: 
    nombreClase(const int_vector<8> &ivv, int rS);
    ~nombreClase();
    void createBitmap(int_vector<8> iv);
    void createK2Tree();
    double calculateEntropy(); 
};

#endif