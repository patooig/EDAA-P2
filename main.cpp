#include <iostream>
#include <sdsl/int_vector.hpp>

using namespace std;
using namespace sdsl;



int main(int argc, char * argv[]){

    int n = atoi(argv[1]);
    int c;
    int i = 0;
    
    //n = n*n*120;


    //Punto 2:

    int_vector<8> iv(n);
    
    while(cin>>c){
        iv[i] = c;
        i++;
        //Insertemos los primeros n en el int_vector<> iv//
        //Pasados los primeros n, push_back(iv);
        /*if(i==n){
            i = 0;
            matriz.push_back(iv);
        }
        iv[i] = c;
        i++; */
         

    }

    

    int_vector<8>::iterator it;

   
    for (it = iv.begin() ; it != iv.end(); it++){
        
        cout << (int)*it << " ";
    }
    
    cout << endl;

    //Punto 3:

 /*   
    int_vector<> iv;
    iv[0] = 1;
    iv[2] = 1;
    iv[3] = 2;
    iv[4] = 2;


    bit_vector b_p(n);  
    int_vector <8> v_p;  

    int i=0;
    int j=0;
    int k =0;
    int x = 0;

/*    // Pato's Version
    
    bool first = true;
    while(j<n){

        if(iv[j]!= iv[i]){ // Son distintos

            for ( k = i; k < j; i++){
                if(first){
                    b_p[k] = 1;
                    first = false;
                    v_p[x] = iv[k];
                    x++;
                } 
                b_p[k] = 0;
            }

            i = j;
            first = true;
            
        }
        if(iv[j] == iv[i]) j++;  // Son iguales
        
    }
    for ( k = i; k < j; i++){
        if(first){
            b_p[k] = 1;
            first = false;
            v_p[x] = iv[k];
        } 
        b_p[k] = 0;
    }
    
*/
    //Versión Leonardo Aravena Cuevas

    bit_vector bl(n); //Bit vector

    int_vector<8>::iterator jt;
    
    int_vector<8> vLeo(n); //v'


    
    it = iv.begin();//Primer índice
    jt = it++;      //Segundo índice    


    bl[0] = 1; //Primer elemento del bit_vector es cero
    
    int r = 1; //índice para iterar en el bit_vector
    int l = 1; //índice para iterar en v'

    vLeo[0] = *it; //Primer elemento de v' es el primer elemento del int_vector

    //El segundo índice itera hasta el final del int_vector
    while(jt != iv.end()){

        //Si hay coincidencia en los números
        if(*it == *jt){
             
            bl[r] = 0;  //Se coloca el cero en el bit_vector y
            r++;        //Se incrementa su índice
            jt++;       //Se avanza al siguiente número del iv
        
        }

        //Si hay números distintos
        else{
                    
            bl[r] = 1;  //Se coloca el 1 en el bit vector
            r++;        //Se incrementa su índice    

            vLeo[l] = *jt; //Se guarda el valor del nuevo número en v'
            l++; //Se incrementa su índice

            it = jt;    //El primer índice toma el valor del índice donde 
                        //Ocurre la diferencia de los números
            jt = it++;  //Se incrimenta el segundo índice            
        }
        
    }

    bit_vector::iterator bt;

    for(it = vLeo.begin(); it != vLeo.end(); it++){

        cout<<*it<<" ";
    }

    cout<<endl;

    for(bt = bl.begin(); bt != bl.end(); bt++){

        cout<<*bt<<" ";
    }

    cout<<endl;

    return 0;
}