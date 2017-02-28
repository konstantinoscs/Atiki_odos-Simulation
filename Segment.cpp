#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Segment.h"

using namespace std;

//Author: Konstantinos Stefanidis (Lead) / Giannis Lamprou (Support)

segment::segment( int NSegs, int cap, segment * pre, int id, int K)
    :capacity(cap), vehicles(0), prev(pre), next(NULL), seg_id(id), entr(NULL)  
{
    int max_cars = capacity/2;
    
    entr = new entrance(K, NSegs+1, id);
    
    if(prev!=NULL)
    {
        prev->next=this;
    }
    
    rand_fill(NSegs, max_cars);
    cout<< "segment created with "<< cars.size()<< " cars"<<endl;
}

segment::~segment()
{
    delete entr;
    for(int i = 0; i<cars.size(); i++)
    {
        delete cars[i];
    }
    cout<< "segment destroyed" <<endl;
}

int segment::operate(int percent)
{
    //cout<<"OPERATE FOR SEGMENT NO "<<seg_id<<endl;
    vector<vehicle*> incoming;
    int message=1;
    int limit = 0, target = 0;
    
    for(int i = 0; i < cars.size(); i++)              //cars exit the highway
    {
        if(cars[i]->ready_check() == 1)
        {
            exit(i);
        }        
    }
    
    limit = capacity - get_no_of_vehicles();
    
    if(prev!=NULL && !prev->pass_vehicles(limit))
    {
        cout << "Delay after seg No "<< entr->get_node_number() << endl << endl;
        message = 0;
    }
            
    limit = capacity - get_no_of_vehicles();    //how many from entrance
    //cout << "limit is "<< limit <<endl;
    
    if(entr->operate(limit, incoming))          //get from entrance
    {
        cout << "Delay at "<< seg_id <<" seg's entrance" << endl << endl;
        message = 0;
    }
    
    
    for (int i = 0; i< incoming.size(); i++)
    {
        if(!enter(incoming[i]))
        {
            cout<<"Did not enter"<< endl;
            return -2;
        }
            
    }

    if(message)
    {
        cout << "Keep safety distances in the segment after entrance No "<< entr->get_node_number()<< endl<<endl;
    }
    
    incoming.clear();
    make_ready(percent);
    
}

int segment::enter(vehicle* entry)
{
    if(vehicles < capacity)
    {
        cars.push_back(entry);
        vehicles ++;
        entry->now_at(seg_id);
        return 1;
    }
    else
    {
        return 0;
    }

}

void segment::exit(int position)
{
    delete cars[position];
    cars.erase(cars.begin() + position);
    vehicles --;
    //cout << "Vehicle was at seg "<< seg_id<< " and exited"<<endl;
}

int segment::pass(int position)
{
    if(position > cars.size()-1)
    {
        cout<<"error"<<endl;
        return 0;
    }
    
    if(!next->enter(cars[position]))
        return 0;
    
    cars.erase(cars.begin() + position);
    vehicles --;
    return 1;
}

int segment::get_no_of_vehicles()
{
    return vehicles;
}

int segment::pass_vehicles(int limit)
{
    vector<int> move_on;
    int target=0;   
    
    if (limit == 0)
            return 0;
    
    find_ready(move_on);
    
    while (limit!=0 && move_on.size()!=0)
    {
        target = rand() % move_on.size();       //choosing the vehicle that will pass
        
        if(!pass(move_on[target]))      //should always be able to pass (limit)
        {
            cout<<"Error at segment::pass"<<endl;
            return 0;
        }
        
        move_on.clear();
        
            limit --;               //next can now take one less vehicle
            
        find_ready(move_on);
            
    }
            
    
    
    if (move_on.size()!=0)
    {
        move_on.clear();
        return 0;           //not all vehicles passes
    }
    else
        return 1;           //all passed
} 

void segment::rand_fill(int NSegs, int max_cars)
{
    vehicle * temp = NULL;
    for (int i = 0; i< max_cars; i++)
    {
        temp = new vehicle (NSegs, seg_id);
        cars.push_back(temp);
        vehicles++;
    }
}

void segment::make_ready(int percent)
{
    int ready = 0, target = 0;
    vector<int> possible;
    
    for(int i = 0; i < cars.size(); i++)
    {
        if(!cars[i]->is_ready()) 
        {
            possible.push_back(i);
        }
            
    }
    
    ready = ceil(possible.size()*(float)percent/100);
    
    while(ready && possible.size())
    {
        target = rand()% possible.size();
        cars[possible[target]]->set_ready();
        possible.erase(possible.begin() + target);
        ready --;
    }
    
    possible.clear();
}

void segment::find_ready(std::vector<int>& move_on)
{
     for(int i = 0; i < cars.size(); i++)              
        {
            if(cars[i]->ready_check() == 2)         //car wants to move
            {
                move_on.push_back(i);
            }    
         }
}