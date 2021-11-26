#include "Compacta.h"
#include <fstream>
#include <sdsl/k2_tree.hpp>

using namespace std;
using namespace sdsl;

Compacta::Compacta(const int_vector<8> &ivv, int rS){
    
    ivSize = ivv.size();
    iv = ivv;
    bv.resize(ivSize); // Asigna tamaño a bitvector
    rowSize = rS;
    
    
    ofstream out("int_vector.html");
    write_structure<HTML_FORMAT>(iv,out);

    first = true;
}

Compacta::~Compacta(){
    // Destructor
    delete rv;
    delete sv;
    
}

// Se crea rrr_vector a partir de bitvector
void Compacta::createRRRVector(){

    rv = new rrr_vector<>(bv);
    cout << "size rv :" <<size_in_bytes(*rv) << endl;
    // Tipo rank1 a rv 
    rrr_vector<>::rank_1_type rank_rrr(rv);
    rank_rrr1 = rank_rrr;
    ofstream out("rrr.html");

    write_structure<HTML_FORMAT>(*rv,out);


}


// Crear SD_VECTOR
void Compacta::createSDVector(){
    
    sv = new sd_vector<>(bv);
    
    cout << "size sd :" <<size_in_bytes(*sv) << endl;
   
    sd_vector<>::rank_1_type rank_sd(sv);
    rank_sd1 = rank_sd;

    ofstream out("sd_vector.html");
    write_structure<HTML_FORMAT>(*sv,out);
    
}

int Compacta::rank_rrr(int i){
  
    return rank_rrr1(i);
}

int Compacta::rank_sd(int i){

    return rank_sd1(i);
}

void Compacta::createBitmap(){

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

    cout << "Tamaño BITVECTOR: " << size_in_bytes(bv) << endl;

    cout << "Tamaño INT_VEC V: " << size_in_bytes(v) << endl;

    ofstream out("bit_vector.html");
    write_structure<HTML_FORMAT>(bv,out);

}


void Compacta::vectorToIntVector(){
    
    v.resize(v_p.size());
    int s = v_p.size();
    for (int i = 0; i < s; i++)
    {
        v[i] = v_p[i];
    } 
    ofstream out("v_prima.html");
    write_structure<HTML_FORMAT>(v,out);
}

double Compacta::calculateEntropy(){

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

int Compacta::createK2Tree(){
    
    int i=0;
    int j= rowSize * rowSize;
    clock_t start;
    vector<int> temp(rowSize);
    int x = 0;
    int y = 0;
    vector<vector<int>> M; // Matriz
    double time_k2;
    k2_tree<4> *k2;
    //k2_tree<4> *k1;

    //vector< k2_tree<4> *> * vK2;
    //vK2 = new vector<k2_tree<4>*>;
   
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
            y++;
            
        }
        
        if(y == rowSize){
            start = clock();
            k2 = new k2_tree<4>(M);
            time_k2+=(double)(clock()-start)/CLOCKS_PER_SEC;
            
            if(first){
                ofstream out("k2.html");
                write_structure<HTML_FORMAT>(*k2,out);
                first = false;
            }

            

            size_k2 += size_in_bytes(*k2);

            //vK2->push_back(k2);
            
            M.clear();
            
            
            y = 0;
        }

        
    }

    printf("Tiempo total k2 : %.8f\n",time_k2);

    

    return size_k2; 
}

void Compacta::diferencias(){
    
    int i=0;
    int j= rowSize * rowSize;
    vector<int> * diff = new vector<int>;
    int n;

    while(j<ivSize){

        if(iv[i] != iv[j]){  
            
            diff->push_back(int(iv[i]-iv[j]));
            
        }
        i++;
        j++;
    }

    n = diff->size();
    
    vdif.resize(n);

    signo.resize(n);
    
    for (int i = 0; i < n; i++){
        
        if(diff->at(i) < 0){// negativo
            vdif[i] = abs(diff->at(i));
            signo[i] = 1;
        } 
        else{           // positivo
            vdif[i] = diff->at(i);
            signo[i] = 0;
        }    
    }
    
    delete diff;

}
