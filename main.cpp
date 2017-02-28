/* 
 * File:   main.cpp
 * Author: konstantinos(Lead) / Giannis(Support)
 *
 * Created on January 4, 2016, 2:37 AM
 */
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Highway.h"

using namespace std;

inline int args_to_var(int &N, int &NSegs, int &K, int &Percent, int argc, char **argv);

int main(int argc, char** argv) 
{
    int N = 5, NSegs = 10, K = 30, Percent = 40, capacity = 20;
    highway *attiki_odos = NULL;
    
    srand(time(NULL));
    if(!args_to_var(N, NSegs, K, Percent, argc, argv))
    {
        cerr << "Not the correct number of arguments!"<< endl;
        return -1;
    }
    
    cout << "Give segments capacity: ";
    cin >> capacity;
    
    attiki_odos = new highway(NSegs, capacity, K);
    
    for (int i = 0; i< N; i++)
    {
        attiki_odos->operate(Percent);
    }
    
    delete attiki_odos;
    
    return 0;
}

inline int args_to_var(int &N, int &NSegs, int &K, int &Percent, int argc, char ** argv)
{
    if(argc != 5)
    {
       return 0; 
    }
    else
    {
        N = atoi(argv[1]);
        NSegs = atoi(argv[2]);
        K = atoi(argv[3]);
        Percent = atoi(argv[4]);
        return 1;
    }
}
