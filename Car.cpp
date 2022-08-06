#include <iostream>
using namespace std;
#include "Car.h"

// Empty Constructor
Car::Car(){
    this->type = " +";
    this->plateNo = 0;
}

// Default Constructor
Car::Car( string type, int plateNo ){
    this->type = type;
    this->plateNo = plateNo;
}

/**
 *  @brief Returns car type
 */
string Car::getType(){
    return this->type;
}

/**
 *  @brief Returns car plate no
 */
int Car::getPlateNo(){
    return this->plateNo;
}

/**
 *  @brief Sets car type
 */
void Car::setType(string a){
    this->type = a;
}

/**
 *  @brief Sets car plate no
 */
void Car::setPlateNo(int plate){
    this->plateNo = plate;
}