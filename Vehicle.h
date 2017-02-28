#ifndef VEHICLE_H
#define VEHICLE_H

class vehicle
{
    bool ready;
    int exit_no;
    int is_at;
public:
    vehicle(int exits);
    vehicle(int exits, int where);
    ~vehicle();
    int ready_check();
    bool is_ready();
    void set_ready();
    void now_at(int seg);
};

#endif