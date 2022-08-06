#include <iostream>
using namespace std;
#include "ParkingLot.h"

// Default Constructor
ParkingLot::ParkingLot(int id, int rows, int columns ){
    this->id = id;
    this->rows = rows;
    this->columns = columns;
    this->emptySpc = rows*columns;
    this->carNo = 0;
    this->letters = "ABCDEFGHIJKL";

    if ( rows <= 0 || columns <= 0 ) {
        cars = NULL;
    }
    else {
        cars = new Car* [rows];
        for ( int i = 0; i < rows; i++) {
            this->cars[i] = new Car[columns];
            for ( int j = 0; j < columns; j++) {
                cars[i][j].setType(" +");
                cars[i][j].setPlateNo(0);
            }
        }
    }
}

// Empty Constructor
ParkingLot::ParkingLot(){
    this->id = 0;
    this->rows =0;
    this->columns = 0;
    this->emptySpc = 0;
    this->carNo = 0;
    this->letters = "ABCDEFGHIJKL";
}

// Destructor
ParkingLot::~ParkingLot(){
    if ( this->cars )
    for ( int i = 0; i < rows; i++ ) {
        delete [] this->cars[i];
    }
    delete [] this;
}

/**
 *  @brief Returns lot id
 */
int ParkingLot::getIdPL(){
    return id;
}

/**
 *  @brief Returns lot rows
 */
int ParkingLot::getRows(){
    return this->rows;
}

/**
 *  @brief Returns lot columns
 */
int ParkingLot::getColumns(){
    return this->columns;
}

/**
 *  @brief Returns lot empty space
 */
int ParkingLot::getEmptySpc(){
    return this->emptySpc;
}

/**
 *  @brief Returns lot cars
 */
Car** ParkingLot::getCars(){
    return this->cars;
}

/**
 *  @brief Returns total car number in the lot
 */
int ParkingLot::getCarNo(){
    return this->carNo;
}

void ParkingLot::lotContentsPL(){
    for ( int i = 0; i < columns+1; i++) {
        if ( i == 0) {
            cout << " ";
        }
        else {
            cout << " " << i ;
        }
    }
    cout << endl;

    for ( int i = 0; i < rows; i++) {
        cout << letters[i];
            for ( int j = 0; j < columns; j++) {
                if ( j >= 10 ) {
                    cout << " " << cars[i][j].getType();
                }
                else {
                    cout << cars[i][j].getType();
                }
            }

        cout << endl;
    }
}

void ParkingLot::parkCarPL(string location, string carType, int plateNumber) {
    int tempRowNum = carLocation(location);
    int tempColNum = location[1]- '0';
    tempColNum--;
    // try finding the car with the given id
    bool exist = true;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (cars[i][j].getPlateNo() == plateNumber) {
                exist = false;
            }
        }
    }
    if (exist) {
        if ( carType == "a" ) {
            if ( cars[tempRowNum][tempColNum].getType() == " +") {

                carNo++;
                cars[tempRowNum][tempColNum].setPlateNo(plateNumber);
                cars[tempRowNum][tempColNum].setType(" a");

                emptySpc--;
                cout << "light-Duty car with number plate " << plateNumber << " has been parked at location " << location
                     << " , lot " << this->id << endl;
            }
            else {
                cout << "Cannot park light-duty car with number plate " << plateNumber << " at location " << location << ", already occupied" << endl;
                return;
            }
        }
        else if ( carType == "b" ){
            if ( tempRowNum == 0 ) {
                cout << "Cannot park heavy-duty car with number plate " << plateNumber << " at location " << location << ", not enough space" << endl;
                return;
            }

            if ( cars[tempRowNum][tempColNum].getType() == " +" && cars[tempRowNum-1][tempColNum].getType() == " +" ) {
                // create a new array to add the new lot in collection
                // increment the lot no
                carNo++;
                // add the lot to the collection
                cars[tempRowNum][tempColNum].setPlateNo(plateNumber);
                cars[tempRowNum][tempColNum].setType(" b");
                cars[tempRowNum-1][tempColNum].setType(" b");

                emptySpc--;
                emptySpc--;
                cout << "Heavy-duty car with number plate " << plateNumber << " has been parked at location " << location << " , lot " << this->id  << endl;

            }
            else {
                cout << "Cannot park heavy-duty car with number plate " << plateNumber << " at location " << location << ", already occupied" << endl;
                return;
            }
        }
    } else {
        string tempType;
        if ( carType == "a" ) {
            tempType = "light-duty";
        } else if ( carType == "b" ){
            tempType = "heavy-duty";
        }
        cout << "Cannot park " << tempType << " car with number plate " << plateNumber << ", a car with this plate number already exists in this lot " << endl;
        return;
    }
}

bool ParkingLot::findCarPL(int plateNumber){

    int foundRow = -1;
    int foundCol = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (cars[i][j].plateNo == plateNumber) {
                foundRow = i;
                foundCol = j;
            }
        }
    }
    if (foundRow == -1) {
        return false;
    }
    else {

        string tempType;
        if ( cars[foundRow][foundCol].getType() == "a"){
            tempType = "Light-duty";
        }
        else {
            tempType = "Heavy-duty";
        }

        char tempLetter = letters[foundRow];
        cout << tempType << " car with number plate " << plateNumber << " is at location " << tempLetter << foundCol << ", lot " << id << endl;

        return true;
    }
}

bool ParkingLot::findCarWOT(int plateNumber){

    bool found = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (cars[i][j].getPlateNo() == plateNumber) {
                found = true;
            }
        }
    }
    return found;
}

bool ParkingLot::removeCarPL(int plateNumber) {
    // try finding the car with the given id
    int foundRow = -1;
    int foundCol = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (cars[i][j].getPlateNo() == plateNumber) {
                foundRow = i;
                foundCol = j;
            }
        }
    }
    if (foundRow == -1) {
        cout << "The car with number plate " << plateNumber << " is not in the system" << endl;
        return false;
    } else {
        if (carNo > 0) {
            // create a new array to add the new lot in collection
            // increment the lot no
            carNo--;
            // add the lot to the collection

            string tempType;
            if ( cars[foundRow][foundCol].type == "a"){
                tempType = "Light-duty";
                cars[foundRow][foundCol].plateNo = 0;
                cars[foundRow][foundCol].type = " +";
            }
            else {
                tempType = "Heavy-duty";
                cars[foundRow][foundCol].plateNo = 0;
                cars[foundRow-1][foundCol].type = " +";
                cars[foundRow][foundCol].type = " +";
            }

            emptySpc++;
            char tempLetter = letters[foundRow];
            cout << tempType << " car with number plate " << plateNumber << " has been removed from slot " << tempLetter << foundCol << ", lot " << this->id << endl;

        } else {
            // this is the last car the collection has
            carNo = 0;

            string tempType;
            if ( cars[foundRow][foundCol].type == "a"){
                tempType = "Light-duty";
                cars[foundRow][foundCol].plateNo = 0;
                cars[foundRow][foundCol].type = " +";
            }
            else {
                tempType = "Heavy-duty";
                cars[foundRow][foundCol].plateNo = 0;
                cars[foundRow-1][foundCol].type = " +";
                cars[foundRow][foundCol].type = " +";
            }

            emptySpc++;
            char tempLetter = letters[foundRow];
            cout << tempType << " car with number plate " << plateNumber << " has been removed from slot "
                 << tempLetter << foundCol << ", lot " << this->id << endl;
        }
        return true;
    }
}

int ParkingLot::carLocation(string a){
    int temp = 0;
    for ( int i = 0; i < 12; i++) {
        if ( a[0] == letters[i] ) {
            temp = i;
        }
    }
    return temp;
}