#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <iostream>
using namespace std;

class Car{
public:
    Car( const string type, const int plateNo);
    Car();
    string getType();
    int getPlateNo();
    void setType(string a);
    void setPlateNo(int plate);

private:
    string type;            // type of the car
    int plateNo;            // unique plate number of the car

    friend class ParkingLot;
    friend class ParkingSystem;
};


#endif // CAR_H_INCLUDED
