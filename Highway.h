#ifndef HIGHWAY_H
#define HIGHWAY_H

#include "Segment.h"
#include <vector>


class highway
{
    int vehicles;
    std::vector<segment*> segments;    
 
public:
    highway(int NSegs, int capacity, int K);
    ~highway();
    void operate(int percent);
};

#endif
