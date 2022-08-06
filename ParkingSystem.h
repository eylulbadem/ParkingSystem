#ifndef PARKINGSYSTEM_H_INCLUDED
#define PARKINGSYSTEM_H_INCLUDED
#include "ParkingLot.h"
#include <iostream>
using namespace std;

class ParkingSystem{

public:

    ParkingSystem();
    ParkingSystem( const ParkingSystem& psToCopy );
    ~ParkingSystem();
    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId, string location, string carType, int plateNumber);
    void findCar(int plateNumber);
    void removeCar(int plateNumber);

private:

    ParkingLot** lots;
    // A dynamically created array of ParkingLot objects
    int lotNo;
    // Number of the lots in the parking system
};

#endif // PARKINGSYSTEM_H_INCLUDED
