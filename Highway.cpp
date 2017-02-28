#include"Highway.h"
#include <new>
#include <cstdlib>
#include <iostream>

//Author: Konstantinos Stefanidis (Lead) / Giannis Lamprou (Support)

using namespace std;

highway::highway(int NSegs, int capacity, int K)
    :vehicles(0)
{
    segment *temp;
    
    temp = new segment(NSegs, capacity, NULL, 0, K);
    segments.push_back(temp);
    
    for (int i = 1; i < NSegs; i++)
    {
        temp = new segment(NSegs, capacity, segments[i - 1], i, K);
        segments.push_back(temp);
    }
    
    temp = NULL;
    
    cout << "The highway is ready for operation!" << endl;
}

highway::~highway()
{
    for(int i = 0; i < segments.size(); i++)
        delete segments[i];
    
    cout<< "Highway destroyed" << endl;
}

void highway::operate(int percent)
{
        for(int i= segments.size()-1; i > -1; i--)
        {
            segments[i]->operate(percent);
        }
    
    vehicles = 0;
    
    for (int i = 0; i < segments.size(); i++)
    {
        vehicles += segments[i]->get_no_of_vehicles();
    }
}


