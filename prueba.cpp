#include <iostream>
#include <sdsl/int_vector.hpp>

using namespace std;
using namespace sdsl;



int main(int argc, char * argv[]){
    
    int n = atoi(argv[1]);

    int_vector<8> iv(n);
    int c;
    int i =0;
    while(cin>>c){
        iv[i] = c;
        i++;
    }


    bit_vector b_p(n);  
    vector<int> v_p;
      

    i=0;
    int j=0;
    int k =0;

    // Pato's Version
    
    bool first = true;
    while(j<n){

        if(iv[j]!= iv[i]){ // Son distintos

            for ( k = i; k < j; k++){
                if(first){
                    b_p[k] = 1;
                    first = false;
                    v_p.push_back(iv[k]);
                } 
                else b_p[k] = 0;
            }

            i = j;
            first = true;
        }
        
        if(iv[j] == iv[i]) j++;  // Son iguales
        
    }
    for ( k = i; k < j; k++){
        if(first){
            b_p[k] = 1;
            first = false;
            v_p.push_back(iv[k]);
        }else b_p[k] = 0;
    }

    int_vector <8> v_pp(v_p.size());

    

    bit_vector::iterator it;
    vector<int>::iterator itv;

    for (it = b_p.begin(); it != b_p.end(); it++)
    {
        cout << (int)*it << " ";
    }
    cout << endl;
    int x  =0;
    for(itv = v_p.begin(); itv != v_p.end() ; itv++){
        v_pp[x] =*itv;
        x++;
        cout <<  *itv << " " ;
    }
    cout << endl;

    int_vector<8>::iterator ivi ;

    for (ivi = v_pp.begin(); ivi != v_pp.end(); ivi++)
    {
        cout << (int)*ivi << " ";
    }
    cout <<endl;
    
    return 0;
}
