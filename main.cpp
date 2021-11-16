#include <iostream>
#include <sdsl/int_vector.hpp>

using namespace std;
using namespace sdsl;

typedef vector<vector<bool>> vvb;

int main(int argc, char * argv[]){
    //ola
    int n = atoi(argv[1]);
    int c;
    int i = 0;
    int size_row = n;
    
    n = n*n*5;


    //Punto 2:

    int_vector<8> iv(n);

    //para el punto 5:
    
    vector<int> input;

    
    
    vector<vvb> BM;
    //
    
    while(cin>>c){
        iv[i] = c;
        i++;

        input.push_back(c);
        //Insertemos los primeros n en el int_vector<> iv//
        //Pasados los primeros n, push_back(iv);
        /*if(i==n){
            i = 0;
            matriz.push_back(iv);
        }
        iv[i] = c;
        i++; */
         

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
                    v_p.push_back(iv[k]); // Almacena los núm.
                } 
                else b_p[k] = 0; // b_p almacena 0
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

    //Punto 3:

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

    //Punto 4:


    i=0;
    j=size_row*size_row;

    vector<bool> temp(size_row);
    x = 0;
    int y = 0;
    vector<vector<bool>> M; // Matriz

    cout<<endl;
    while(j<n){

        if(input.at(i) == input.at(j)){

            temp[x] = 0;
            x++;
        }

        else{

            temp[x] = 1;
            x++;
        }

        i++;
        j++;
        if(x == size_row){ 

            M.push_back(temp); 
            for(int l = 0; l < temp.size(); l++){

                cout<<temp.at(l)<<" ";
            }
            cout <<endl;
            x = 0;
            y++;
            
        }

        if(y == size_row){

            BM.push_back(M);

            
            M.clear();
            
            y = 0;
        }
    }

    return 0;
}