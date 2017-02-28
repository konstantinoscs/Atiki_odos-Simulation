#ifndef TOLL_H
#define TOLL_H
#include <vector>
#include "Vehicle.h"

class toll	{
private:
    std::vector <vehicle*> waiting_vehicles_ptr;
    
public:
    toll(int NSegs, int max_fill);
    ~toll();

	void rand_fill(int NSegs, int max_fill);
	int vehicles_in_toll();
	vehicle* get_vehicle();
};

#endif