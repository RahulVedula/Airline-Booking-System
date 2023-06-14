#include <iostream>
#include <string>
#include <sstream>
#include "Flight.h"
#pragma once
using namespace std;

Flight::Flight()
{
  flightID = "0"; currentSeatNum = 0;
}

Flight::Flight(int cap, string des)
{
  capacity = cap; destination = des; currentSeatNum = 0;
  flightSeats = new Seat[capacity];
  flightCustomers = new Customer[capacity];
  
}

Flight::Flight(int cap, string des, string id, int duration, string craft)
{
  capacity = cap; destination = des; flightID = id; flightDuration = duration; aircraftType = craft; currentSeatNum = 0;

  flightSeats = new Seat[capacity];
  flightCustomers = new Customer[capacity];

}

int Flight::getCapacity() {return capacity;}
string Flight::getID() {return flightID;}

void Flight::setDestination(string des)
{
  destination = des;
}

void Flight::setDuration(int duration)
{
  flightDuration = duration;
}

string Flight::getDestination(){
  return destination;
}

string Flight::getCraft(){
    return aircraftType;
}

int Flight::getDuration(){
    return flightDuration;
}



void Flight::reserveSeat(int seatNum, Customer user)
{
  if (flightSeats[seatNum].available){
  flightSeats[seatNum] = Seat(seatNum, user);
  flightCustomers[seatNum] = user;
  spaceOnFlight--;
  }
  else{
    cout<<"Seat is Reserved"<<endl; 
  }
}

bool Flight::checkSeatAvailability(int seatNum)
{
  if(flightSeats[seatNum].available) return true;
  else return false;
}

void Flight::availableSeats(){
  cout<<"\nThere are "<<spaceOnFlight<<" seats available on the flight at this moment"<<endl;
  cout<<"These seats are unreserved at the moment:"<<endl;
  for (int i = 0; i < 10;i++){
    if(flightSeats[i].available){
      cout<<"\tSeat "<<i<<endl;
    }
  }
}

string Flight::getSeatInformation(int seatNum){
  return flightSeats[seatNum].printSeatInformation();
}

void bubbleSort(Customer arr[], int length) {
    bool swapped;

    for (int i = 0; i < length - 1; ++i) {
        swapped = false;
        for (int j = 0; j < length - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no elements were swapped in the inner loop, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}

int Flight::getSpaceOnFlight(){
    return spaceOnFlight;
  }


void Flight::passengerList(){
  Customer * newflightCustomers;
  newflightCustomers = new Customer[10 - spaceOnFlight];
  int currentValue = 0;
  for (int i = 0;i < 10;i++){
    if(!(flightSeats[i].available)){
      newflightCustomers[currentValue] = flightCustomers[i];
      currentValue++;
    } 
  }
    bubbleSort(newflightCustomers,10 - spaceOnFlight);
  cout<<"\n\nThese are the customers currently registered for Flight "<<flightID<<" to "<<destination<<":"<<endl;
  for (int i = 0; i < (10 - spaceOnFlight);i++){
    cout<<newflightCustomers[i].toString()<<endl;
  }
}

string Flight::toString()
{
  ostringstream s1;
		s1 << "Flight Information:\n"<< "\tFlight ID: "<<flightID<<"\n\tCapacity: "<<capacity<<"\n\tDestination: "<<destination<<"\n\tDuration: "<<flightDuration<<"\n\tAircraft: "<<aircraftType;
  	string s2 = s1.str();
		return s2;
}


int binarySearch(Customer arr[], int length, const Customer& target) {
   int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;  
        }

        if (arr[mid] < target) {
            left = mid + 1;  
        } else {
            right = mid - 1;  
        }
    }
    return -1;  // Target Customer not found
}


int linearSearch(Customer arr[], int length, const Customer& target) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Return -1 if the target customer is not found
}



void Flight::deleteSeat(Customer user){
    int seatNum = linearSearch(flightCustomers, 10, user);
    cout<<seatNum<<endl;
    flightSeats[seatNum].available = true;
    flightSeats[seatNum] = Seat();
    spaceOnFlight++;
}

bool Flight::operator<(const Flight& other) const {
        return destination < other.destination;
    }

    // Overload the greater than operator (>)
bool Flight::operator>(const Flight& other) const {
        return destination > other.destination;
    }

    // Overload the equality operator (==)
bool Flight::operator==(const Flight& other) const {
        return destination == other.destination;
    }