#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TreeMap.h"
#include "HashMap.h"

using namespace std;

void readTaxiData(bool selection, TreeMap<int, vector<int>> &treeMap, HashMap<int, vector<int>> &hashMap);

void readUberData(bool selection, TreeMap<int, vector<int>> &treeMap, HashMap<int, vector<int>> &hashMap);

int main() {
    TreeMap<int, vector<int>> taxiTreeMap;
    TreeMap<int, vector<int>> uberTreeMap;
    HashMap<int, vector<int>> taxiHashMap;
    HashMap<int, vector<int>> uberHashMap;

    bool selection = true; //hash or tree map

    readTaxiData(selection, taxiTreeMap, taxiHashMap);
    readUberData(selection, uberTreeMap, uberHashMap);

    return 0;
}

void readTaxiData(bool selection, TreeMap<int, vector<int>> &treeMap, HashMap<int, vector<int>> &hashMap) {
    ifstream taxiData("TaxiTripDataCSV.csv");
    string line;
    istringstream line_stream;
    getline(taxiData, line, '\n');


    for (int i = 1; i < 8001; i++) {
        string pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix, token;
        vector<int> tripInfo;
        getline(taxiData, line, '\n');
        line_stream.str(line);
        getline(line_stream, token, ',');
        getline(line_stream, pickupFull, ',');
        for (int j = 0; j < pickupFull.length(); j++) {
            if(pickupFull[i] == '/' && pickupFull[i+2] == '/'){
                pickupFix += '0';
            }
            else if (pickupFull[j] != '/' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                pickupFix += pickupFull[j];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ',');
        for (int k = 0; k < dropoffFull.length(); k++) {
            if(dropoffFull[i] == '/' && dropoffFull[i+2] == '/'){
                dropoffFix += '0';
            }
            else if (dropoffFull[k] != '/' && dropoffFull[k] != ' ' && dropoffFull[k] != ':') {
                dropoffFix += dropoffFull[k];
            }
        }
        int dropoff = stoi(dropoffFix);
        tripInfo.push_back(dropoff);
        getline(line_stream, token, ',');
        getline(line_stream, token, ',');
        getline(line_stream, token, ',');
        getline(line_stream, token, ',');
        getline(line_stream, pickupID, ',');
        int pickupIDint = stoi(pickupID);
        tripInfo.push_back(pickupIDint);
        getline(line_stream, dropoffID, ',');
        int dropoffIDint = stoi(dropoffID);
        tripInfo.push_back(dropoffIDint);

        if (selection)
            treeMap[pickup] = tripInfo;
        else
            hashMap[pickup] = tripInfo;
    }

    taxiData.close();
}

void readUberData(bool selection, TreeMap<int, vector<int>> &treeMap, HashMap<int, vector<int>> &hashMap) {
    ifstream uberData("UberTripDataCSV.csv");
    string line;
    istringstream line_stream;
    getline(uberData, line, '\n');

    for (int i = 1; i < 8001; i++) {
        string licenseNum, dispatchBase, pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix;
        vector<int> tripInfo;
        getline(uberData, line, '\n');
        line_stream.str(line);
        getline(line_stream, licenseNum, ',');
        if (licenseNum != "HV0003") {
            continue;
        }
        getline(line_stream, dispatchBase, ',');
        getline(line_stream, pickupFull, ',');
        for (int j = 0; j < pickupFull.length(); j++) {
            if(pickupFull[i] == '/' && pickupFull[i+2] == '/'){
                pickupFix += '0';
            }
            else if (pickupFull[j] != '/' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                pickupFix += pickupFull[j];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ',');
        for (int k = 0; k < dropoffFull.length(); k++) {
            if(dropoffFull[i] == '/' && dropoffFull[i+2] == '/'){
                dropoffFix += '0';
            }
            else if (dropoffFull[k] != '/' && dropoffFull[k] != ' ' && dropoffFull[k] != ':') {
                dropoffFix += dropoffFull[k];
            }
        }
        int dropoff = stoi(dropoffFix);
        tripInfo.push_back(dropoff);
        getline(line_stream, pickupID, ',');
        int pickupIDint = stoi(pickupID);
        tripInfo.push_back(pickupIDint);
        getline(line_stream, dropoffID, ',');
        int dropoffIDint = stoi(dropoffID);
        tripInfo.push_back(dropoffIDint);

        if (selection)
            treeMap[pickup] = tripInfo;
        else
            hashMap[pickup] = tripInfo;
    }

    uberData.close();
}
