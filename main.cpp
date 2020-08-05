#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "TreeMap.h"
#include "HashMap.h"
#include "Display.h"

using namespace std;
using namespace std::chrono;


void readTaxiData(bool selection, TreeMap<int,vector<int>> &treeMap,  HashMap<int,vector<int>> &hashMap);
void readUberData(bool selection, TreeMap<int,vector<int>> &treeMap,  HashMap<int,vector<int>> &hashMap);

int main() {
    TreeMap<int, vector<int>> taxiTreeMap;
    TreeMap<int, vector<int>> uberTreeMap;
    HashMap<int, vector<int>> taxiHashMap;
    HashMap<int, vector<int>> uberHashMap;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
            "Welcome to Uber vs Taxi, a program to visualize the trends between the two market leaders in New York City, 2019.\n"
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"
            "Enter [1] to load data in a Red Black Tree Map.\n"
            "Enter [2] to load data in a Hash Map.\n" << endl;

    int loadSelection;
    cin >> loadSelection;

    bool mapSelection;

    mapSelection = loadSelection == 1;

    auto start = high_resolution_clock::now();

    readTaxiData(mapSelection, taxiTreeMap, taxiHashMap);
    readUberData(mapSelection, uberTreeMap, uberHashMap);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Data loaded in " << duration.count() << " milliseconds.\n" << endl;


    bool exit = false;
    while (!exit) {
        cout << "\nData Visualization Menu \n"
                "[1] Total Trips per Month\n"
                "[2] Total Trips After Time of Day\n"
                "[3] Average Trip Duration\n"
                "[0] Exit" << endl;

        int displaySelection;

        cin >> displaySelection;

        if (mapSelection) { // Tree

            switch(displaySelection) {

                case 0 :
                    cout << "Thank you for using Uber vs Taxi Data Visualization Experience!"  << endl;
                    exit = true;
                    break;
                case 1 :
                    Display::perMonthTree(taxiTreeMap, uberTreeMap);
                    break;
                case 2 :
                    cout << "Select an hour of the day to compare trips:\n" << endl;
                    int hour;
                    cin >>  hour;
                    Display::timeDayTree(taxiTreeMap, uberTreeMap, hour);
                    break;
                case 3:
                    Display::avgTripTree(taxiTreeMap, uberTreeMap);
                    break;
            }

        }
        else { // Hash

            switch(displaySelection) {

                case 0 :
                    cout << "Thank you for using Uber vs Taxi Data Visualization Experience!"  << endl;
                    exit = true;
                    break;
                case 1 :
                    Display::perMonthHash(taxiHashMap, uberHashMap);
                    break;
                case 2 :
                    cout << "Select an hour of the day (on 24 hour clock) to compare trips:\n" << endl;
                    int hour;
                    cin >>  hour;
                    Display::timeDayHash(taxiHashMap, uberHashMap, hour);
                    break;
                case 3:
                    Display::avgTripHash(taxiHashMap, uberHashMap);
                    break;
            }
        }
    }

    return 0;
}

void readTaxiData(bool selection, TreeMap<int,vector<int>> &treeMap,  HashMap<int,vector<int>> &hashMap){
    ifstream taxiData("TaxiTripDataCSV.csv");
    string line;
    istringstream line_stream;
    getline(taxiData, line, '\n');


    while(!taxiData.eof()) {
        string pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix, token;
        vector<int> tripInfo;
        getline(taxiData, line, '\n');
        line_stream.str(line);
        getline(line_stream,token, ',');
        getline(line_stream, pickupFull, ',');
        for (int j = 0; j < pickupFull.length(); j++) {
            if(j + 2 < pickupFull.length() && pickupFull[j] == '/' && pickupFull[j+2] == '/'){
                pickupFix += '0';
            }
            else if(j + 2 < pickupFull.length() && pickupFull[j] == ' ' && pickupFull[j+2] == ':'){
                pickupFix += '0';
            }
            else if (pickupFull[j] != '/' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                pickupFix += pickupFull[j];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ',');
        for (int k = 0; k < dropoffFull.length(); k++) {
            if(k + 2 < dropoffFull.length() && dropoffFull[k] == '/' && dropoffFull[k+2] == '/'){
                dropoffFix += '0';
            }
            else if(k + 2 < dropoffFull.length() && dropoffFull[k] == ' ' && dropoffFull[k+2] == ':'){
                dropoffFix += '0';
            }
            else if (dropoffFull[k] != '/' && dropoffFull[k] != ' ' && dropoffFull[k] != ':') {
                dropoffFix += dropoffFull[k];
            }
        }
        int dropoff = stoi(dropoffFix);
        tripInfo.push_back(dropoff);
        getline(line_stream,token, ',');
        getline(line_stream,token, ',');
        getline(line_stream,token, ',');
        getline(line_stream,token, ',');
        getline(line_stream, pickupID, ',');
        int pickupIDint = stoi(pickupID);
        tripInfo.push_back(pickupIDint);
        getline(line_stream, dropoffID, ',');
        int dropoffIDint = stoi(dropoffID);
        tripInfo.push_back(dropoffIDint);

        if(selection)
            treeMap[pickup] = tripInfo;
        else
//            hashMap.insert(pickup, tripInfo);
            hashMap[pickup] = tripInfo;
//            hashMap.operator[](pickup) = tripInfo;
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
            if(j + 2 < pickupFull.length() && pickupFull[j] == '/' && pickupFull[j+2] == '/'){
                pickupFix += '0';
            }
            else if(j + 2 < pickupFull.length() && pickupFull[j] == ' ' && pickupFull[j+2] == ':'){
                pickupFix += '0';
            }
            else if (pickupFull[j] != '/' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                pickupFix += pickupFull[j];
            }
        }
        int pickup = stoi(pickupFix);
        getline(line_stream, dropoffFull, ',');
        for (int k = 0; k < dropoffFull.length(); k++) {
            if(k + 2 < dropoffFull.length() && dropoffFull[k] == '/' && dropoffFull[k+2] == '/'){
                dropoffFix += '0';
            }
            else if(k + 2 < dropoffFull.length() && dropoffFull[k] == ' ' && dropoffFull[k+2] == ':'){
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
//            hashMap.insert(pickup, tripInfo);
//            hashMap.operator[](pickup) = tripInfo;
    }

    uberData.close();
}