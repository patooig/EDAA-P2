#include <iostream>
#include <sdsl/int_vector.hpp>

using namespace std;
using namespace sdsl;



int main(int argc, char * argv[]){
    
    int n = atoi(argv[1]);

    int_vector<8> iv(n);
    iv[0] = 1;
    iv[1] = 1;
    iv[2] = 1;


    bit_vector b_p(n);  
    int_vector <8> v_p(n);  

    int i=0;
    int j=0;
    int k =0;
    int x = 0;

    // Pato's Version
    
    bool first = true;
    while(j<n){

        if(iv[j]!= iv[i]){ // Son distintos

            for ( k = i; k < j; k++){
                if(first){
                    b_p[k] = 1;
                    first = false;
                    v_p[x] = iv[k];
                    x++;
                } 
                else b_p[k] = 0;
            }

            i = j;
            first = true;
        }
        cout << "pegado en " << i << " " << j << endl;
        if(iv[j] == iv[i]) j++;  // Son iguales
        
    }
    for ( k = i; k < j; k++){
        if(first){
            b_p[k] = 1;
            first = false;
            v_p[x] = iv[k];
        }else b_p[k] = 0;
    }

    bit_vector::iterator it;

    for (it = b_p.begin(); it != b_p.end(); it++)
    {
        cout << (int)*it << endl;
    }
    
    return 0;
}
