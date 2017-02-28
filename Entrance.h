#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <string>
#include "Toll.h"
#include "Vehicle.h"


class entrance	
{
private:
    std::string node_name;	/* name of the entrance */
	int node_number;		/* number of the entrance */
	int limit;			/* number K to limit vehicles transfering from tolls */

	const int number_of_segments;	/* the number of overall segments in the highway (used to create vehicles in tolls) */

	std::vector <toll*> employee_tolls_ptr;		/* vector containing a random number of */
        std::vector <toll*> automated_tolls_ptr;
    
public:
    entrance(int K, int NSegs, int nodenumber);
    ~entrance();

    int operate(int max, std::vector<vehicle*>& move);

    int get_node_number();
};

#endif