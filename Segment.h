#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#include "Entrance.h"
#include "Vehicle.h"



class segment
{
    int vehicles;
    int capacity;
    int seg_id;
    entrance* entr;
    std::vector<vehicle*> cars;
    segment *prev;
    segment *next;
    
    void exit(int position);
    int pass_vehicles(int limit);
    void rand_fill(int NSegs, int max_cars);
    void make_ready(int percent);
    void find_ready(std::vector<int> & move_on);
    
public:
    segment( int NSegs, int cap, segment *pre, int id, int K);
    ~segment();
    int operate(int percent);
    int enter(vehicle *entry);
    int pass(int position);
    int get_no_of_vehicles();
    
};

#endif