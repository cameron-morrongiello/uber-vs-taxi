#include <iostream>
#include <fstream>
#include <sstream>
#include "TreeMap.h"
#include "HashMap.h"
using namespace std;


int main() {
    TreeMap<int,vector<int>> treeMap;
    HashMap<int,vector<int>> hashMap;

    bool selection = true; //hash or tree map

    readTaxiData(selection);
    readUberData(selection);

    return 0;
}

void readTaxiData(bool selecteion){
    ifstream taxiData("TaxiTripDataCSV.csv");

    string pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix, line;
    istringstream line_stream;


    for(int i = 1; i< 8001; i++){
        vector<int> tripInfo;
        getline(taxiData, line, '\n');
        line_stream.str(line);
        getline(line_stream,, ",");
        getline(line_stream, pickupFull, ",");
        for(int j = 0; j < pickupFull.length; j++){
            if(pickupFull[i] != '/' && pickupFull[i] != ' ' && pickupFull[i] != ':'){
                pickupFix += pickupFull[i];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ",");
        for(int k = 0; k < dropoffFull.length; k++){
            if(dropoffFull[i] != '/' && dropoffFull[i] != ' ' && dropoffFull[i] != ':'){
                dropoffFix += dropoffFull[i];
            }
        }
        int dropoff = stoi(dropoffFix);
        tripInfo.push_back(dropoff);
        getline(line_stream,, ",");
        getline(line_stream,, ",");
        getline(line_stream,, ",");
        getline(line_stream,, ",");
        getline(line_stream, pickupID, ",");
        int pickupIDint = stoi(pickupID);
        tripInfo.push_back(pickupIDint);
        getline(line_stream, dropoffID, ",");
        int dropoffIDint = stoi(dropoffID);
        tripInfo.push_back(dropoffIDint);

        if(selection == true)
            treeMap[pickup] = tripInfo;
        else
            hashMap[pickup] = tripInfo;
    }

    taxiData.close();
}

void readUberData(bool selection){
    ifstream uberData("UberTripDataCSV.csv");

    string licenseNum, dispatchBase, pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix, line;
    istringstream line_stream;

    for(int i = 1; i< 8001; i++){
        vector<int> tripInfo;
        getline(uberData, line, '\n');
        line_stream.str(line);
        getline(line_stream, licenseNum, ",");
        if(licenseNum != "HV0003"){
            break;
        }
        getline(line_stream, dispatchBase, ",");
        getline(line_stream, pickupFull, ",");
        for(int j = 0; j < pickupFull.length; j++){
            if(pickupFull[i] != '/' && pickupFull[i] != ' ' && pickupFull[i] != ':'){
                pickupFix += pickupFull[i];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ",");
        for(int k = 0; k < dropoffFull.length; k++){
            if(dropoffFull[i] != '/' && dropoffFull[i] != ' ' && dropoffFull[i] != ':'){
                dropoffFix += dropoffFull[i];
            }
        }
        int dropoff = stoi(dropoffFix);
        tripInfo.push_back(dropoff);
        getline(line_stream, pickupID, ",");
        int pickupIDint = stoi(pickupID);
        tripInfo.push_back(pickupIDint);
        getline(line_stream, dropoffID, ",");
        int dropoffIDint = stoi(dropoffID);
        tripInfo.push_back(dropoffIDint);

        if(selection == true)
            treeMap[pickup] = tripInfo;
        else
            hashMap[pickup] = tripInfo;
    }

    uberData.close();
}
