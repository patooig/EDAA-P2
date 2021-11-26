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
    size_k2 = 0;
    
    ofstream out("int_vector.html");
    write_structure<HTML_FORMAT>(iv,out);
}

Compacta::~Compacta(){
    // Destructor
    delete rv;
    delete sv;  
}

// Se crea rrr_vector a partir de bitvector
void Compacta::createRRRVector(){

    rv = new rrr_vector<>(bv);
    cout << "Tamaño rrr_vector: " <<size_in_bytes(*rv) << endl;
    // Tipo rank1 a rv 
    rrr_vector<>::rank_1_type rank_rrr(rv);
    rank_rrr1 = rank_rrr;
    
    ofstream out("rrr.html");
    write_structure<HTML_FORMAT>(*rv,out);

}


// Crear sd_vector a partir de 
void Compacta::createSDVector(){
    
    sv = new sd_vector<>(bv);
    
    cout << "Tamaño sd_vector: " <<size_in_bytes(*sv) << endl;
   
    sd_vector<>::rank_1_type rank_sd(sv);
    rank_sd1 = rank_sd;

    ofstream out("sd_vector.html");
    write_structure<HTML_FORMAT>(*sv,out);
    
}
// Retorna rank1 con posición i, desde la estructura rrr_vector
int Compacta::rank_rrr(int i){
  
    return rank_rrr1(i);
}
// Retorna rank1 con posición i, desde la estructura sd_vector
int Compacta::rank_sd(int i){

    return rank_sd1(i);
}

//Método que crea bitmap y v' a partir del int_vector<8> iv
void Compacta::createBitmap(){

    int i = 0, j = 0, k = 0;
    bool first = true;
    v_p = new vector<int>;
    while(j<ivSize){

        if(iv[j]!= iv[i]){ // Si los valores de i y j son distintos

            for ( k = i; k < j; k++){   // Realiza recorrido interno desde i hasta j-1
                if(first){              // En la primera ocurrencia asigna un 1 en el bitvector
                    bv[k] = 1;         
                    first = false;
                    v_p->push_back(iv[k]); // Almacena los números en v'
                } 
                else bv[k] = 0; // Luego las siguientes ocurrencias deben tener un 0 en el bitvector
            }

            i = j;
            first = true;
        }
        
        if(iv[j] == iv[i]) j++;  // Si son iguales se sigue avanzando
        
    }
    //Si j llega al ultimo elemento, no hay más números que analizar
    //Se deben analizar el último intervalo.
    for ( k = i; k < j; k++){
        if(first){
            bv[k] = 1;
            first = false;
            v_p->push_back(iv[k]);
        }else bv[k] = 0;
    }

    // Traspasa los datos de vector<int> * v_p a int_vector<8> v
    vectorToIntVector();

    cout << "Tamaño bitvector: " << size_in_bytes(bv) << endl;

    cout << "Tamaño int_vector V: " << size_in_bytes(v) << endl;

    ofstream out("bit_vector.html");
    write_structure<HTML_FORMAT>(bv,out);

}

// Método que pasa los datos desde un vector<int>* v_p a
// una estructura int_vector<8> v, luego libera la memoria de v_p.
void Compacta::vectorToIntVector(){
    
    v.resize(v_p->size());
    int s = v_p->size();

    for (int i = 0; i < s; i++){
        v[i] = v_p->at(i);
    } 

    ofstream out("v_prima.html");
    write_structure<HTML_FORMAT>(v,out);
    
    delete v_p; 
}

double Compacta::calculateEntropy(){

    int c;
    double h = 0;
    map<int,int> m;                 
    map<int,int>::iterator it;
    int_vector<8>::iterator ivt = iv.begin();

    //Recorre el int_vector<8> iv y con map almacenamos la frencuencia 
    //de cada valor.
    for(ivt = iv.begin(); ivt != iv.end(); ivt++){
        
        //Se castea a int
        c = int(*ivt);

        //Si no existe se agrega al mapa y se le asigna el valor 1
        if(m.count(c)==0){

            m[c]=1;
        }
        //Si existe se incrementa su valor
        else{

            m[c]++;
        }
    }
   
    //Se recorre todo el mapa para calcular la entropía según la fórmula descrita en el informe
    for(it = m.begin(); it != m.end(); it++){

        h += ((double)it->second / (double)ivSize) * log2((double)ivSize / (double)it->second);
    }

    return h;
}

int Compacta::createK2Tree(){

    //Variable para indicar la creacion del primer k2-tree
    bool first_k2 = true;  

    //Variables para iterar por las matrices del dataset
    int i=0;
    int j= rowSize * rowSize;
 
    clock_t start;

    //Vector temporal para guardar las filas de las matrices
    vector<int> temp(rowSize);
    
    //Variable para avanzar por los elementos de 'temp'
    int x = 0;
    //Variable para avanzar por las filas de 'M'
    int y = 0;
    
    //Matriz desde la cual se construye el k2-tree
    vector<vector<int>> M; 
    double time_k2 = 0;

    //K2-tree
    k2_tree<4> *k2;

    //Vector opcional para guardar todos los k2-tree
    //vector< k2_tree<4> *> * vK2;
    //vK2 = new vector<k2_tree<4>*>;
   
    //Se recorre todo el dataset
    while(j<ivSize){
        
        //Si el elemento es igual
        if(iv[i] == iv[j]){ 
            
            //Se guarda en el vector<int> como 0
            temp[x] = 0;  
        }

        //En caso contrario se guarda un 1
        else{

            temp[x] = 1; 
        }

        //Se avanza a la siguiente posición de 'temp'
        x++;
        
        //Se avanza en los elementos de las matrices contiguas
        i++;
        j++;

        //Si se llega al tamaño de la fila
        if(x == rowSize){ 
            
            //Se guarda en la matriz y se reinicia el iterador 'x'
            M.push_back(temp); 
            x = 0;
            y++;
        }
        
        // Si está en la última columna de la matriz
        if(y == rowSize){   
            start = clock();

            //Se crea el k2_tree a partir de 'M'
            k2 = new k2_tree<4>(M);
            time_k2+=(double)(clock()-start)/CLOCKS_PER_SEC;
            
            //Se crea la representación del tamaño del primer k2-tree
            if(first_k2){
                ofstream out("k2.html");
                write_structure<HTML_FORMAT>(*k2,out);
                first_k2 = false;
            }

            //Se suma el tamaño del k2-tree para retornar el tamaño total
            size_k2 += size_in_bytes(*k2);

            //Opcionalmente se puede guardar el k2-tree en un vector:
            //vK2->push_back(k2); 
            delete k2;  // Libera memoria de k2
            M.clear(); //Se limpia la matriz M para la siguiente iteración
            
            y = 0;  //Reinicia valor de y, para nueva iteración.
        }
    }

    printf("Tiempo total k2 : %.8f\n",time_k2);

    return size_k2; 
}

void Compacta::diferencias(){
    
    int i=0; //Itera desde la primera matriz
    int j= rowSize * rowSize; //Itera desde la segunda matriz
    
    //Vector temporal para guardar las diferencias entre los elemento
    vector<int> * diff = new vector<int>;

    int n;
    
    //Se itera por todo el dataset
    while(j<ivSize){

        //Si hay diferencia entre los datos se guarda esa diferencia en 'diff'
        if(iv[i] != iv[j]){  
            
            diff->push_back(int(iv[i]-iv[j]));
            
        }
        i++;
        j++;
    }

    //Se obtiene el tamaño de diff
    n = diff->size();
    
    //Se ajusta el tamaño del int_vector y del bit_vector
    vdif.resize(n);
    signo.resize(n);
    
    //Se recorre diff para copiar los valores al int_vector 'vdif'
    for (int i = 0; i < n; i++){
        
        //Si la diferencia es negativa se guarda el valor absoluto y
        //Se fija en 1 el bit_vector signo
        if(diff->at(i) < 0){
            vdif[i] = abs(diff->at(i));
            signo[i] = 1;
        } 

        //Si la diferencia es positiva se guarda en 'vdif' y
        //al bit_vector signo se le asigna el valor 0
        else{           
            vdif[i] = diff->at(i);
            signo[i] = 0;
        }    
    }
    
    cout<<"vdif: "<<size_in_bytes(vdif)<<endl;
    cout<<"signo: "<<size_in_bytes(signo)<<endl;

    //Se libera la memoria del vector temporal 'diff'
    delete diff;
}
