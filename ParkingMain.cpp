#include <iostream>
using namespace std;
#include "ParkingSystem.h"

int main(){

    ParkingSystem L;
    L.listLots();
    cout << endl;

    // Testing add parking lot
    cout << endl;
    cout << "Testing add parking lots" << endl;
    cout << endl;
    L.createLot(981, 7, 7);
    L.createLot(666, 6, 11);
    L.createLot(222, 12, 12);
    cout << endl;
    L.createLot(434, 19, 3);
    L.createLot(222, 5, 4);
    L.createLot(301, 9, 9);
    cout << endl;
    L.createLot(301, 19, 3);
    L.createLot(205, 4, 4);
    cout << endl;
    L.listLots();
    cout << endl;

    // Testing remove parking lot
    cout << endl;
    cout << "Testing remove parking lot" << endl;
    cout << endl;
    L.removeLot(666);
    L.removeLot(101);
    L.removeLot(205);
    cout << endl;
    L.createLot(743, 6, 7);
    cout << endl;

    // Testing park car
    cout << endl;
    cout << "Testing park a car" << endl;
    cout << endl;
    L.parkCar( 981, "C3", "b", 211);
    L.parkCar( 981, "E5", "a", 141);
    L.parkCar( 981, "A3", "b", 199);
    cout << endl;
    L.parkCar( 981, "A3", "a", 199);
    L.parkCar( 981, "G1", "b", 888);
    L.parkCar( 222, "G7", "b", 200);
    L.parkCar( 222, "B2", "a", 156);
    cout << endl;
    L.parkCar( 221, "C3", "a", 177);
    L.parkCar( 222, "C3", "a", 177);
    L.parkCar( 223, "C3", "b", 177);
    cout << endl;
    L.parkCar( 743, "A1", "a", 256);
    L.parkCar( 743, "C4", "b", 159);
    L.parkCar( 743, "B4", "a", 120);
    cout << endl;
    L.listLots();
    cout << endl;


    // Testing find car
    cout << endl;
    cout << "Testing find a car" << endl;
    cout << endl;
    L.findCar(199);
    L.findCar(156);
    L.findCar(198);
    cout << endl;
    L.findCar(159);
    L.findCar(100);
    L.findCar(177);
    cout << endl;

    // Testing show lot contents
    cout << endl;
    cout << "Testing show lot contents" << endl;
    cout << endl;
    L.lotContents(981);
    cout << endl;
    L.lotContents(222);
    cout << endl;
    L.lotContents(301);
    cout << endl;
    L.lotContents(743);
    cout << endl;

    // Testing remove car
    cout << endl;
    cout << "Testing remove car" << endl;
    cout << endl;
    L.removeCar(156);
    L.removeCar(177);
    L.removeCar(188);
    cout << endl;
    L.removeCar(159);
    L.removeCar(888);
    L.removeCar(127);
    cout << endl;

    cout << "Testing remove car, again, this time with cars in the lot " << endl;
    cout << "Notice how first cars are deleted " << endl;
    cout << endl;
    L.removeLot(222);
    cout << endl;

    return 0;
}
