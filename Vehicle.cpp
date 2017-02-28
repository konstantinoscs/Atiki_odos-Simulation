#include "Vehicle.h"
#include <iostream>
#include <cstdlib>
//Author: Konstantinos Stefanidis(Lead) / Giannis Lamprou(Support)

vehicle::vehicle(int exits)
    :ready(false), is_at(-1)
{
    static int i=0;
    i++;
    exit_no = rand() % exits + 1;
    //cout << "Vehicle created, wants to exit at:" << exit_no << endl;
}

vehicle::vehicle(int exits, int where)
    :ready(false), is_at(where)
{
    exit_no = rand() % (exits-where) + where + 1;
    //std::cout << "Vehicle created, wants to exit at:" << exit_no << " is at "<< is_at<< std::endl;
}

vehicle::~vehicle()
{ 
    static int i=0;
    i++;
}

int vehicle::ready_check()
{
    if (ready)
    {
        if(is_at +1 == exit_no)
            return 1;           //exit the highway
        else
            return 2;           //move to next segment
    }
    else
        return 0;               //stay at the segment
}

bool vehicle::is_ready()
{
    return ready;
}

void vehicle::set_ready()
{
    ready = true;
}

void vehicle::now_at(int seg)
{
    is_at=seg;
}
