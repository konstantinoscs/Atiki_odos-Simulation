#include <iostream>
#include <vector>
#include <cstdlib>
#include "Entrance.h"


//Author: Konstantinos Stefanidis (Support) / Giannis Lamprou (Lead)

using namespace std;

string entrance_names();/* a function that returns up to 21 different names for entrances */

entrance::entrance(int K, int NSegs, int nodenumber)
	: node_name(entrance_names()), node_number(nodenumber), limit(K), number_of_segments(NSegs)	{      
    
	int rand_toll_number = 0, rand_vehicles_toll = 0;
	toll* temp_toll_ptr = NULL;

	rand_toll_number = (rand() % 3) + 2;		/* randomly select a number from 2 to 4 employee tolls that this entrance should have */
	rand_vehicles_toll = (rand() % 5) + 1;		/* randomly select a number from 1 to 5 vehicles that each enmployee toll should have (then, when a toll is created a random number up to 2 is added to this number) */
	for (int i = 0; i < rand_toll_number; i++) {
		temp_toll_ptr = new toll(number_of_segments, rand_vehicles_toll);
		employee_tolls_ptr.push_back(temp_toll_ptr);
	}

	rand_toll_number = (rand() % 2) + 2;		/* randomly select a number from 1 to 3 automated tolls that this entrance should have */
	rand_vehicles_toll = (rand() % 10) + 1;		/* randomly select a number from 1 to 10 vehicles that each automated toll should have (then, when a toll is created a random number up to 2 is added to this number) */
	for (int i = 0; i < rand_toll_number; i++) {
		temp_toll_ptr = new toll(number_of_segments, rand_vehicles_toll);
		automated_tolls_ptr.push_back(temp_toll_ptr);
	}

	cout << "Entrance with name: " << node_name << endl;;
}

entrance::~entrance()	{
	
	for (unsigned int i = 0; i < employee_tolls_ptr.size(); i++)		/* delete all employee tolls */
		delete employee_tolls_ptr[i];
	employee_tolls_ptr.clear();

	for (unsigned int i = 0; i < automated_tolls_ptr.size(); i++)		/* delete all automated tolls */
    	delete automated_tolls_ptr[i];
	automated_tolls_ptr.clear();

	cout << "Entrance with name: " << node_name << " deleted" << endl;;
}

int entrance::operate(int max, vector<vehicle*>& move)	{
    
	unsigned int employee_transfercounter = 0, automated_transfercounter = 0, next_emp_toll = 0, next_auto_toll = 0, all_empty_emp = 0, all_empty_aut = 0, rand_vehicles_toll = 0, delay = 0;
	unsigned int empty_employee_tolls = 0, empty_automated_tolls = 0;
	vehicle* temp_vehicle = NULL;

	for (int i = 0; i < employee_tolls_ptr.size(); i++) {		/* start moving vehicles from the employee toll that has the most vehicles */
		int max = 0;
		if (employee_tolls_ptr[i]->vehicles_in_toll() > max) {
			max = employee_tolls_ptr[i]->vehicles_in_toll();
			next_emp_toll = i;
		}
	}

	for (int i = 0; i < automated_tolls_ptr.size(); i++) {		/* start moving vehicles from the automated toll that has the most vehicles */
		int max = 0;
		if (automated_tolls_ptr[i]->vehicles_in_toll() > max) {
			max = automated_tolls_ptr[i]->vehicles_in_toll();
			next_auto_toll = i;
		}
	}

	while (employee_transfercounter + automated_transfercounter < max && ((all_empty_emp == 0 && employee_transfercounter < limit) || (all_empty_aut == 0 && automated_transfercounter < (limit * 2)))) {

		if (all_empty_emp == 0 && employee_transfercounter < limit) {		/* if not all employee tolls are empty, proceed to the process of moving a vehicle */

			next_emp_toll = (next_emp_toll + 1) % employee_tolls_ptr.size();		/* next employee toll to move a vehicle from (one vehicle is taken each toll at a time) */
			
			empty_employee_tolls = 0;
			while (employee_tolls_ptr[next_emp_toll]->vehicles_in_toll() == 0 && all_empty_emp == 0) {		/* if the next toll is empty of vehicles, and not all tolls are empty, move to the next not empty toll */
				empty_employee_tolls++;

				if (empty_employee_tolls < employee_tolls_ptr.size())		/* if not all tolls are empty of vehicles */
					next_emp_toll = (next_emp_toll + 1) % employee_tolls_ptr.size();		/* move to the next toll as above */
				else
					all_empty_emp = 1;
			}

			if (all_empty_emp == 0) {		/* if not all employee tolls are empty, take a vehicle from chosen toll */

				temp_vehicle = employee_tolls_ptr[next_emp_toll]->get_vehicle();
				move.push_back(temp_vehicle);
				employee_transfercounter++;		/* the number of vehicles transfered from employee tolls is increased (counter) */
			}

			if (employee_transfercounter + automated_transfercounter == max)		/* if the vehicles transfered are the maximum number that can fit in the segment, stop the whole process */
				break;
		}

		if (all_empty_aut == 0 && automated_transfercounter < (limit * 2)) {		/* if not all automated tolls are empty, proceed to the process of moving a vehicle */

			next_auto_toll = (next_auto_toll + 1) % automated_tolls_ptr.size();		/* next automated toll to move a vehicle from (one vehicle is taken each toll at a time) */
			
			empty_automated_tolls = 0;
			while (automated_tolls_ptr[next_auto_toll]->vehicles_in_toll() == 0 && all_empty_aut == 0) {		/* if the next toll is empty of vehicles, and not all tolls are empty, move to the next not empty toll */
				empty_automated_tolls++;

				if (empty_automated_tolls < automated_tolls_ptr.size())		/* if not all tolls are empty of vehicles */
					next_auto_toll = (next_auto_toll + 1) % automated_tolls_ptr.size();		/* move to the next toll as above */
				else
					all_empty_aut = 1;
			}

			if (all_empty_aut == 0) {		/* if not all automated tolls are empty, take a vehicle from chosen toll */

				temp_vehicle = automated_tolls_ptr[next_auto_toll]->get_vehicle();
				move.push_back(temp_vehicle);
				automated_transfercounter++;		/* the number of vehicles transfered from automated tolls is increased (counter) */
			}
		}

	}

	/* K adjustment as a whole. If the sum of all transfered vehicles (both from employee and automated tolls) is lower than 3 * K, then decrease K by one, else increase it by one */

	if (employee_transfercounter + automated_transfercounter < limit * 3)
		limit--;
	else if (employee_transfercounter + automated_transfercounter == limit * 3)
		limit++;

	/* After the vehicle transfer, if there is even one vehicle left in any toll, then return 1 (for "Kathisteriseis to be printed) */
	   
	for (unsigned int i = 0; i < employee_tolls_ptr.size(); i++)
		if (employee_tolls_ptr[i]->vehicles_in_toll() > 0)
			delay = 1;
	for (unsigned int i = 0; i < automated_tolls_ptr.size(); i++)
		if (automated_tolls_ptr[i]->vehicles_in_toll() > 0)
			delay = 1;
	
	/* Toll refill. Vehicles are added to both employee and automated tolls. About the same amount of vehicles are added to all employee tolls 
	   (random number up to 5 (same for all employee tolls), plus 1 - 2 vehicles (exclusive to each toll))
	   the same amount of vehicles are added to all automated tolls (random number up to 10 (same for all automated tolls), plus 1 - 2 vehicles (exclusive to each toll)) */
		
	rand_vehicles_toll = (rand() % 5) + 1;
	for (unsigned int i = 0; i < employee_tolls_ptr.size(); i++)
		employee_tolls_ptr[i]->rand_fill(number_of_segments, rand_vehicles_toll);
	
	rand_vehicles_toll = (rand() % 10) + 1;
	for (unsigned int i = 0; i < automated_tolls_ptr.size(); i++)
		automated_tolls_ptr[i]->rand_fill(number_of_segments, rand_vehicles_toll);

	return delay;

}

int entrance::get_node_number() {
	return node_number;
}

string entrance_names()		/* a function that returns up to 21 different names for entrances */
{
	static int i = 0;
	static string nodes[21] = {
		"Eleusina",
		"Mandra",
		"Magoula",
		"Aghiou Louka",
		"Aspropurgos",
		"Aigaleo",
		"Ano Liosia",
		"Axarnes",
		"Irakleio",
		"Metamorfosi",
		"Kumi",
		"Kifisias",
		"Pentelis",
		"Douk. Plaketnias",
		"Ntrafi",
		"Pallini",
		"Rafina",
		"Kantza",
		"Paiania",
		"KAD Paianias",
		"Aerolimena"
	};

	if (i <= 20)
		return nodes[i++];
	else {
		std::cout << "There are no other entrances" << std::endl;
		return NULL;
	}
}