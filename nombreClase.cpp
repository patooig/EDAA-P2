#include "nombreClase.h"

using namespace std;
using namespace sdsl;

nombreClase::nombreClase(const int_vector<8> &ivv, int rS){
    ivSize = ivv.size();
    iv = ivv;
    bv.resize(ivSize); // Asignar tamaño a bitvector
    rowSize = rS;
    
    
}

nombreClase::~nombreClase(){

}

void nombreClase::createBitmap(int_vector<8> iv){

    int i = 0, j = 0, k = 0;
    bool first = true;
    
    while(j<ivSize){

        if(iv[j]!= iv[i]){ // Son distintos

            for ( k = i; k < j; k++){
                if(first){
                    bv[k] = 1;
                    first = false;
                    v_p.push_back(iv[k]); // Almacena los núm.
                } 
                else bv[k] = 0; // bv almacena 0
            }

            i = j;
            first = true;
        }
        
        if(iv[j] == iv[i]) j++;  // Son iguales
        
    }
    for ( k = i; k < j; k++){
        if(first){
            bv[k] = 1;
            first = false;
            v_p.push_back(iv[k]);
        }else bv[k] = 0;
    }
    vectorToIntVector();

}

void nombreClase::vectorToIntVector(){
    /*vector<int>::iterator itv;
    v.resize(v_p.size());
    int x = 0;
    for(itv = v_p.begin(); itv != v_p.end() ; itv++){
        v[x] =*itv;
        x++;
    }
    */
    v.resize(v_p.size());
    int s = v_p.size();
    for (int i = 0; i < s; i++)
    {
        v[i] = v_p[i];
    }
    
}

double nombreClase::calculateEntropy(){

    int c;
    double h = 0;
    map<int,int> m;
    map<int,int>::iterator it;
    int_vector<8>::iterator ivt = iv.begin();

    for(ivt = iv.begin(); ivt != iv.end(); ivt++){

        c = int(*ivt);
        if(m.count(c)==0){

            m[c]=1;
        }
        else{

            m[c]++;
        }
    }
   
    for(it = m.begin(); it != m.end(); it++){

        h += ((double)it->second / (double)ivSize) * log2((double)ivSize / (double)it->second);
    }

    return h;

}

void nombreClase::createK2Tree(){
    int i=0;
    int j= rowSize * rowSize;

    vector<int> temp(rowSize);
    int x = 0;
    int y = 0;
    vector<vector<int>> M; // Matriz

    while(j<ivSize){

        if(iv[i] == iv[j]){ 

            temp[x] = 0;
            x++;
        }

        else{

            temp[x] = 1;
            x++;
        }

        i++;
        j++;
        if(x == rowSize){ 

            M.push_back(temp); 
            x = 0;
            
        }
    } 
}