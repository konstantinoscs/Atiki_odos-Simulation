//Author: Konstantinos Stefanidis (Support) / Giannis Lamprou (Lead))
#include <iostream>
#include <cstdlib>
#include "Toll.h"

using namespace std;

toll::toll(int NSegs, int fill) {
	
	this->rand_fill(NSegs, fill);
	cout << "Toll created" << endl;
}

toll::~toll() {

	for (unsigned int i = 0; i < waiting_vehicles_ptr.size(); i++)
		delete waiting_vehicles_ptr[i];
	waiting_vehicles_ptr.clear();
}

void toll::rand_fill(int NSegs, int fill) {
	
	int rand_vehicles = 0;
	vehicle* temp_vehicle = NULL;

	rand_vehicles = fill + (rand() % 3);		/* number of vehicles created equals to input plus to a maximum 2 vehicles */

	for (int i = 0; i < rand_vehicles; i++) {
		temp_vehicle = new vehicle(NSegs);   
		waiting_vehicles_ptr.push_back(temp_vehicle);
	}

}

int toll::vehicles_in_toll() {
	
	return waiting_vehicles_ptr.size();
}

vehicle* toll::get_vehicle() {
	
	if (waiting_vehicles_ptr.size() == 0) {
		cout << "No vehicles remain in toll for extraction";
		return NULL;
	}

	vehicle* passing_vehicle = NULL;
	
	passing_vehicle = waiting_vehicles_ptr.front();		/* the vector emulates a queue so the first vehicle leaves the tolls */
	waiting_vehicles_ptr.erase(waiting_vehicles_ptr.begin());		/* and is removed from the "queue" */

	return passing_vehicle;
}