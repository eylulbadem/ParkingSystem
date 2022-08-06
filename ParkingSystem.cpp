#include <iostream>
using namespace std;
#include "ParkingSystem.h"

// Default constructor
ParkingSystem::ParkingSystem(){
    // empty collection
    this->lotNo = 0;
    this->lots = NULL;
}

// Copy Constructor
ParkingSystem::ParkingSystem(const ParkingSystem& psToCopy){
    lotNo = psToCopy.lotNo;
    if (lotNo > 0) {
        // deep copy lot objects
        lots = new ParkingLot*[lotNo];
        for (int i = 0; i < lotNo; i++) {
            lots[i] = psToCopy.lots[i];
        }
    } else {
        lots = NULL;
    }
}

// Destructor
ParkingSystem::~ParkingSystem(){
    // avoid memory leaks
    if (lots) {
        for ( int i = 0; i < lotNo; i++){
            delete this->lots[i];
        }
        delete [] this;
        lotNo = 0;
    }
}

// Copy Constructor
ParkingSystem::ParkingSystem(const ParkingSystem& psToCopy){
    lotNo = psToCopy.lotNo;
    if (lotNo > 0) {
        // deep copy lot objects
        lots = new ParkingLot*[lotNo];
        for (int i = 0; i < lotNo; i++) {
            lots[i] = psToCopy.lots[i];
        }
    } else {
        lots = NULL;
        lotNo = 0;
    }
}

/**
 *  @brief Adds a lot to the parking system's collection
 *  @param id a unique id for the lot
 *  @param rows row no of the lot
 *  @param columns column no of the lot
 */
void ParkingSystem::createLot(int id, int rows, int columns){
    if (rows > 12 || columns > 12 ) {
        cout << "Cannot create the parking lot " << id << ", dimensions exceed acceptable bounds" << endl;
        return;
    }

    // try finding the lot with the given id
    bool check = true;
    for (int i = 0; i < lotNo; i++) {
        if (lots[i]->getIdPL() == id) {
            check = false;
        }
    }

    if (check) {
        if (lotNo == 0) {
            lotNo++;
            lots = new ParkingLot*[lotNo]; // this automatically creates a lot
            lots[0] = new ParkingLot(id, rows, columns);
            cout << "Parking lot with ID " << id << " and dimensions (" << rows << "," << columns << ") has been added to the system" << endl;
        }
        else {
            lotNo++;
            ParkingLot** temp;
            ParkingLot* temp2 = new ParkingLot(id,rows,columns);
            temp = new ParkingLot*[lotNo];

            // copy over the previous lots
            for (int i = 0; i < lotNo-1; i++) {
                temp[i] = lots[i];
            }
            temp[lotNo-1] = temp2;
            // add the lot to the collection

            cout << "Parking lot with ID " << id << " and dimensions (" << rows << "," << columns << ") has been added to the system" << endl;
            // deallocate previous array
            delete[] lots;
            lots = temp;
        }
    } else {
        cout << "Cannot create the parking lot " << id << ", a lot with this ID already exists" << endl;
        return;
    }
}


/**
 *  @brief Removes Lot from the collection
 *  @param id a unique id for the lot to remove
 */
void ParkingSystem::removeLot(int id){
    // try finding the lot with the given id
    int found = -1;
    for (int i = 0; i < lotNo; i++) {
        if (lots[i]->getIdPL() == id) {
            found = i;
        }
    }
    if (found == -1) {
        // lot not found throw an exception
        cout << "Lot " << id << " is not in the system" << endl;
        return;
    } else {
        // check size
        if (lotNo  == 1) {
            // only 1 lot

            // deallocate the memory
            for ( int i = 0; i < lots[0]->getRows(); i++ ) {
                for (int j = 0; j < lots[0]->getColumns(); j++) {
                    int tempPlate = lots[0]->getCars()[i][j].getPlateNo();
                    if (tempPlate != 0)
                        lots[0]->removeCarPL(tempPlate);
                }
            }

            lots[0]->rows = 0;
            lots[0]->columns = 0;

            cout << "Lot " << id << " has been successfully removed from the system" << endl;

            lots[0] = NULL;
            lotNo = 0;
        } else {
            //remove the lot
            lotNo--;
            // temporary array to store the lots
            // do not call with lotNo 0
            ParkingLot** temp;
            temp = new ParkingLot*[lotNo];
            // copy over elements until the lot we want to remove
            int idx = 0;
            for (int i = 0; i < lotNo + 1; i++) {
                // skip over the lot to remove
                if (i < found) {
                    temp[idx] = lots[i];
                }

                if( i > found){
                    temp[i - 1] = lots[i];
                }
            }

            // deallocate the memory
            for ( int i = 0; i < lots[found]->getRows(); i++ ){
                for ( int j = 0; j < lots[found]->getColumns(); j++ ){
                    int tempPlate = lots[found]->getCars()[i][j].getPlateNo();
                    if ( tempPlate != 0 )
                        lots[found]->removeCarPL(tempPlate);
                }
            }

            cout << "Lot " << id << " has been successfully removed from the system" << endl;

            delete [] lots;
            lots = temp;
        }
    }
}

void ParkingSystem::listLots(){
    if ( lots == NULL ) {
        cout << "No lots to list";
    }
    else {
        for ( int i = 0; i < lotNo; i++) {
            int tempId = lots[i]->id;
            int tempRow = lots[i]->rows;
            int tempColumn = lots[i]->columns;
            int tempSpc = lots[i]->emptySpc;
            cout << "ID: " << tempId << ", Dim: (" << tempRow << "," << tempColumn << "), number of empty parking spaces: " << tempSpc << endl;
        }
    }
}

void ParkingSystem::lotContents(int id){
    int found = -1;
    for (int i = 0; i < lotNo; i++) {
        if (lots[i]->id == id) {
            found = i;
        }
    }
    if (found == -1) {
        cout << "Lot " << id << " is not in the system" << endl;
        return;
    } else {
        int tempId = lots[found]->id;
        int tempRow = lots[found]->rows;
        int tempColumn = lots[found]->columns;
        int tempSpc = lots[found]->emptySpc;
        cout << "ID: " << tempId << ", (" << tempRow << "," << tempColumn << "), empty slots: " << tempSpc << ", parked cars: ";

        if ( lots[found]->getCarNo() == 0 )
            cout << "No cars yet";

        int count = 0;
        for (int j = 0; j < lots[found]->getRows(); j++) {
            for (int k = 0; k < lots[found]->getColumns(); k++) {
                if ( lots[found]->getCars()[j][k].getPlateNo() != 0 ) {
                    count++;
                    if ( count < lots[found]->getCarNo() ) {
                        cout << lots[found]->getCars()[j][k].getPlateNo() << ", ";
                    } else {
                        cout << lots[found]->getCars()[j][k].getPlateNo();
                    }
                }

            }
        }

        cout << endl << endl;
        lots[found]->lotContentsPL();
    }
}

void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber){
    // try finding the lot with the given id
    int found = -1;
    for (int i = 0; i < this->lotNo; i++) {
        if (lots[i]->getIdPL() == lotId) {
            found = i;
        }
    }

    if (found == -1) {
        cout << "Lot " << lotId << " is not in the system" << endl;
    } else {
        lots[found]->parkCarPL(location,carType,plateNumber);
    }
}

void ParkingSystem::findCar(int plateNumber){
    bool tempBool = false;
    for ( int i = 0; i < lotNo; i++ ){
        tempBool = lots[i]->findCarPL(plateNumber);
    }

    if ( !tempBool ) {
        cout << "The car with number plate " << plateNumber << " is not in the system" << endl;
    }
}

void ParkingSystem::removeCar(int plateNumber){
    // try finding the car with the given plate number
    bool tempBool = false;
    int lotInd = 0;
    for ( int i = 0; i < lotNo; i++ ){
        tempBool = lots[i]->findCarWOT(plateNumber);

        if ( tempBool ) {
            lotInd = i;
        }
    }

    if ( !tempBool ) {
        cout << "The car with number plate " << plateNumber << " is not in the system" << endl;
    }
    else {
        lots[lotInd]->removeCarPL(plateNumber);
    }
}


