#ifndef PARKINGLOT_H_INCLUDED
#define PARKINGLOT_H_INCLUDED

#include <iostream>
using namespace std;
#include "Car.h"


class ParkingLot{
public:

    ParkingLot( int id, int rows, int columns );
    ParkingLot();
    ParkingLot( const ParkingLot& plToCopy );
    ~ParkingLot();

    int getIdPL();
    int getRows();
    int getColumns();
    int getEmptySpc();
    Car** getCars();
    int getCarNo();
    void lotContentsPL();
    void parkCarPL(string location, string carType, int plateNumber);
    bool findCarPL(int plateNumber);
    bool findCarWOT(int plateNumber);
    bool removeCarPL(int plateNumber);
    int carLocation(string a);

private:

    int carNo;
    int id;
    int rows;
    int columns;
    int emptySpc;
    Car** cars;

    friend class ParkingSystem;

    string letters;
};

#endif // PARKINGLOT_H_INCLUDED


