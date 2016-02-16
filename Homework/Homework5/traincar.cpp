// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

TrainCar* PushBack(TrainCar* & simple, TrainCar* car){
	//test for empty list
	if(simple == NULL){
		car-> prev = NULL;
		car-> next = NULL;
		simple = car;
		//cout << endl;

	}
	else{
		while(simple->next!=NULL)
		{
			simple =simple->next;

		}
		//cout << endl;
		car->prev= simple;
		car->next= NULL;
		simple->next = car;

	}
	//cout << "Here" << endl;
	while(simple->prev!=NULL)
		{
			//cout << "Here1" << endl;
			simple =simple->prev;

		}
	return simple;

}
void DeleteAllCars(TrainCar* simple){
	if(simple == NULL){
		return;
	}

	TrainCar * cur = simple-> next;
	while(simple->next!=NULL)
		{
			delete simple; 
			simple = cur;
			cur=simple->next;
		}
		delete simple;
		delete cur;
		simple -> next = NULL;
		simple-> prev = NULL; 
}

void TotalWeightAndCountCars(TrainCar* &train,int &total_weight,int &num_engines,int &num_freight_cars,	int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars){
	total_weight = 0;
	num_engines = 0;
	num_freight_cars = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0; 
	while(train->next!=NULL){
		total_weight += train-> getWeight();
		if(train->isEngine()){
			num_engines+=1;
		}
		if(train->isFreightCar()){
			num_freight_cars+=1;
		}
		if(train->isPassengerCar()){
			num_passenger_cars+=1;
		}
		if(train->isDiningCar()){
			num_dining_cars+=1;
		}
		if(train->isSleepingCar()){
			num_sleeping_cars+=1;
		}
		train = train->next;
	}
	total_weight+= train->getWeight();
	if(train->isEngine()){
		num_engines+=1;
	}
	if(train->isFreightCar()){
		num_freight_cars+=1;
	}
	if(train->isPassengerCar()){
		num_passenger_cars+=1;
	}
	if(train->isDiningCar()){
		num_dining_cars+=1;
	}
	if(train->isSleepingCar()){
		num_sleeping_cars+=1;
	}

	while(train->prev!=NULL)
		{
			//step back again before next function
			train =train->prev;
		}
}

float CalculateSpeed(TrainCar* & train){
 	float total_weight = 0;
	float num_engines = 0;
	while(train->next!=NULL){
		total_weight += train-> getWeight();
		if(train->isEngine()){
			num_engines+=1;
		}
		train = train-> next;
	}
	total_weight += train-> getWeight();
	if(train->isEngine()){
			num_engines+=1;
	}

	while(train->prev!=NULL)
		{
			//step back again before next function
			train =train->prev;
		}

	float speed = ((2999.47*(num_engines)) * 550.00 * 3600.00)/((20/.01)*.02*5280.00*total_weight);
	return speed;
}

float AverageDistanceToDiningCar(TrainCar* & train){
	float average = 0;
	float distance = 0;
	vector <float> distances;
	TrainCar * dining;
	while(1){ 
		if(train->isDiningCar()){
			dining = train;//find the location of the sleeper car and point to it
			break;			
		}
		if (train->next!=NULL)
		{
			train = train->next;
		}
		else{
			dining = train;
			break;
		}
	}


	train = dining;
	//back from dining and pushback distances when it finds passenger
	while(train->prev!=NULL){
		if(train->isPassengerCar()){
			distances.push_back(distance);
		}
		distance+=1;
		train = train->prev;
	}

	//for back from dining
	distance =0;
	train = dining;

	while(train->next!=NULL){
		if(train->isPassengerCar()){
			distances.push_back(distance);
		}
		distance+=1;
		train = train->next;
	}

	float total;
	//find total
	for (int i = 0; i < distances.size(); ++i){
		//cout << distances[i] << endl; //check vector distances
		total += distances[i];
	}

	average = total/distances.size();

	while(train->prev!=NULL){
			//step back again before next function
			train =train->prev;
	}

	return average;
}

int ClosestEngineToSleeperCar(TrainCar * & train){
	int closest_front = 0;
	int closest_back= 0;
	int closest= 0;
	TrainCar * sleeper;
	while(1){ 
		if(train->isSleepingCar()){
			sleeper = train;//find the location of the sleeper car and point to it
			break;			
		}
		if (train->next!=NULL)
		{
			train = train->next;
		}
		else{
			sleeper = train;
			break;
		}
	}

	train = sleeper;
	//back from sleeper and count till engine
	while(train->prev!=NULL){
		if(train->isEngine()){
			break;
		}
		train = train -> prev;//currently it must not have a train->prev after the first link
		closest_back += 1; //closest back from sleeper added
	}

	//for front from sleeper
	train = sleeper;

	while(train->next!=NULL){
		if(train->isEngine()){
			break;
		}
		closest_front +=1;
		train = train->next;
	}

	//whichever is closer
	if(closest_back > 0){
		closest = closest_back;
	}

	if(closest_front > 0 and closest_front < closest_back){
		closest = closest_front;
	}

	while(train->prev!=NULL)
		{
			//step back again before next function
			train =train->prev;
		}

	return closest;
}

vector <TrainCar*> ShipFreight(TrainCar* & all_engines, TrainCar* & all_freight, 
	int & min_speed, int & max_cars_per_train){
	vector <TrainCar*> v;
	TrainCar * train = NULL;
	TrainCar * engines = NULL;


	double boundary = min_speed/28120.0313;//did math on paper to get number to divide speed by that engines/weight has to be greater than or equal to
	double single_engine_best = 1/boundary;
	/*cout << setprecision(9) << boundary << endl;
	cout << single_engine_best << endl;*/

	int total_engines = 0;
	float total_weight;
	int total_freights = 0;
	float average_weight;
	float approximate_max_weight;
	int engines_per_train;
	int engines_needed;
	//move through engines
	while(all_engines->next!=NULL){
		total_engines +=1;
		all_engines = all_engines-> next;
	}
	//cout<< total_engines << endl;

	while(all_freight->next!=NULL){
		total_weight += all_freight->getWeight();
		total_freights+=1;
		all_freight = all_freight-> next;
	}

	//average weight of all freights
	average_weight = total_weight/total_freights;
	approximate_max_weight = average_weight *max_cars_per_train;
	engines_per_train = ceil(approximate_max_weight/single_engine_best);
	//round up to the number of engines needed using the best one engine can pull to determine
	engines_needed = ceil(total_weight/single_engine_best);
	cout << engines_needed << endl;

	/*cout << total_weight << endl;
	cout << total_weight/single_engine_best << endl;
	cout << total_freights << endl;
	cout << max_cars_per_train << endl;
	cout << engines_per_train << endl;
	cout << engines_needed << endl;*/

	//reset lists
	while(all_engines->prev!=NULL){
		all_engines = all_engines-> prev;
	}
	//cout<< total_engines << endl;

	while(all_freight->prev!=NULL){
		all_freight = all_freight-> prev;
	}


	//cout << "made it" << endl;
	for (int i = 0; i < engines_needed/engines_per_train; ++i)
	{
		//train -> prev = NULL;
		//train -> next = NULL;
		int next_weight = 0;
		for (int i = 0; i < engines_per_train; ++i)
		{
			if(next_weight >= single_engine_best*engines_per_train){
				break;
			}
			TrainCar * point = all_engines;
			all_engines = all_engines->next;
			all_engines->prev = NULL;
			PushBack(train, point);
			next_weight += all_engines->getWeight();
		}

		next_weight += all_freight->getWeight();
		for (int i = 0; i < max_cars_per_train- engines_per_train; ++i)
		{
			//run check for total weight
			if(next_weight >= single_engine_best*engines_per_train){
				break;
				//cout << "made it" << endl;
			}
			TrainCar * point2 = all_freight;
			all_freight = all_freight->next;
			all_freight->prev = NULL;
			PushBack(train, point2);
			next_weight += all_freight->getWeight();
		}
		v.push_back(train);
		train = NULL;
		//DeleteAllCars(train);
		

	}

	total_weight = 0;
	int next_weight = 150;
	while(all_freight->next!=NULL){
		total_weight += all_freight->getWeight();
		total_freights+=1;
		all_freight = all_freight-> next;
	}

	//step back again
	while(all_freight->prev!=NULL){
		all_freight = all_freight-> prev;
	}

	for (int i = 0; i < 2; ++i)
	{
		if(all_engines->next != NULL){
				TrainCar * point4 = all_engines;
				all_engines = all_engines->next;
				all_engines->prev = NULL;
				PushBack(train, point4);
			}	
		
		
		while(all_freight->next!= NULL && total_weight/2 > next_weight){

			TrainCar * point4 = all_freight;
			all_freight = all_freight->next;
			all_freight->prev = NULL;
			PushBack(train, point4);
			next_weight += all_freight-> getWeight();
			cout << "here" << endl;
		}

		TrainCar *point5 = all_freight;
		PushBack(train, point5);
		//all_freight = NULL;
		v.push_back(train);
		cout << "here3" << endl;
		//cout << "here3" << endl;
		next_weight+= all_freight->getWeight();
		//cout << "here3" << endl;
		next_weight += all_engines ->getWeight();
		//cout << "here3" << endl;
		//DeleteAllCars(train);
	}
		
	return v;
}

void Separate(TrainCar * & train1,TrainCar * & train2,TrainCar * & train3){
	int total_weight = 0;
	int num_engines = 0;
	int num_freight_cars = 0;
	int num_passenger_cars = 0;
	int num_dining_cars = 0;
	int num_sleeping_cars = 0;
	int next_weight = 0;
	TotalWeightAndCountCars(train1,total_weight,num_engines,num_freight_cars,num_passenger_cars,
	 num_dining_cars, num_sleeping_cars);
	int num_of_cars = num_engines + num_freight_cars + num_passenger_cars + num_dining_cars+num_sleeping_cars;
	cout << total_weight << endl;
	cout << num_engines << endl;
	int max_weight = total_weight/2;

	next_weight += train1->getWeight();
	for (int i = 0; i < num_of_cars; ++i)
	{	 
		cout << "Here" << endl;
		//run check for total weight
		if(next_weight >= max_weight){
			cout << "He" << endl;
			break;
		}
		TrainCar * point2 = train1;
		train1 = train1->next;
		train1->prev = NULL;
		PushBack(train2, point2);
		next_weight += train1->getWeight();
	}

	TrainCar * point = train1;
	cout << "Hell" << endl;
	train1 = train1->next;
	cout << "Misery" << endl;
	train1->prev = NULL;
	cout << "Dumb" << endl;
	train3 = NULL;
	PushBack(train3, point);
	train1 = NULL;
	cout << "Dumber" << endl;
}


