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


void readTaxiData(bool selection, TreeMap<long long,vector<long long>> &treeMap,  HashMap<long long,vector<long long>> &hashMap);
void readUberData(bool selection, TreeMap<long long,vector<long long>> &treeMap,  HashMap<long long,vector<long long>> &hashMap);

int main() {
    TreeMap<long long, vector<long long>> taxiTreeMap;
    TreeMap<long long, vector<long long>> uberTreeMap;
    HashMap<long long, vector<long long>> taxiHashMap;
    HashMap<long long, vector<long long>> uberHashMap;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
            "Welcome to Uber vs Yellow Taxi, a program to visualize the trends between the two market leaders in New York City, 2019.\n"
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
                "[4] Total trips from Pickup Location\n"
                "[0] Exit" << endl;

        long long displaySelection;

        cin >> displaySelection;

        if (mapSelection) { // Tree

            switch(displaySelection) {

                case 0 :
                    cout << "Thank you for using Uber vs Yellow Taxi Data Visualization Experience!"  << endl;
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
                case 4:
                    cout << "Select a neighborhood id:\n" << endl;
                    int neighborhood;
                    cin >> neighborhood;
                    Display::perNeighborhoodTree(taxiTreeMap, uberTreeMap, neighborhood);
                    break;
                default:
                    cout << "Please select a correct value" << endl;
            }

        }
        else { // Hash

            switch(displaySelection) {

                case 0 :
                    cout << "Thank you for using Uber vs Yellow Taxi Data Visualization Experience!"  << endl;
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
                case 4:
                    cout << "Select a neighborhood id:\n" << endl;
                    int neighborhood;
                    cin >> neighborhood;
                    Display::perNeighborhoodHash(taxiHashMap, uberHashMap, neighborhood);
                    break;
                default:
                    cout << "Please select a correct value" << endl;
            }
        }
    }

    return 0;
}

void readTaxiData(bool selection, TreeMap<long long,vector<long long>> &treeMap,  HashMap<long long,vector<long long>> &hashMap){
    ifstream taxiData("TaxiData.csv");
    if(taxiData.is_open()) {
        string line;
        istringstream line_stream;

        while (!taxiData.eof()) {
            string pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix, token;
            long long pickup, dropoff, pickupIDlong, dropoffIDlong;
            vector<long long> tripInfo;
            getline(taxiData, line, '\n');
            line_stream.str(line);
            getline(line_stream, token, ',');
            getline(line_stream, pickupFull, ',');


            for (int j = 0; j < pickupFull.length(); j++) {
                if (pickupFull[j] != '-' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                    pickupFix += pickupFull[j];
                }
            }
            try {
                pickup = stoll(pickupFix);
            } catch (invalid_argument &) {
                pickup = 0;
            }

            getline(line_stream, dropoffFull, ',');
            for (int k = 0; k < dropoffFull.length(); k++) {
                if (dropoffFull[k] != '-' && dropoffFull[k] != ' ' && dropoffFull[k] != ':') {
                    dropoffFix += dropoffFull[k];
                }
            }
            try {
                dropoff = stoll(dropoffFix);
            } catch (invalid_argument &) {
                dropoff = 0;
            }
            tripInfo.push_back(dropoff);
            getline(line_stream, token, ',');
            getline(line_stream, token, ',');
            getline(line_stream, token, ',');
            getline(line_stream, token, ',');
            getline(line_stream, pickupID, ',');
            try {
                pickupIDlong = stoll(pickupID);
            } catch (invalid_argument &) {
                pickupIDlong = 264;
            }
            tripInfo.push_back(pickupIDlong);
            getline(line_stream, dropoffID, ',');
            try {
                dropoffIDlong = stoll(dropoffID);
            } catch (invalid_argument &) {
                dropoffIDlong = 264;
            }
            tripInfo.push_back(dropoffIDlong);

            if (selection)
                treeMap[pickup] = tripInfo;
            else
                hashMap[pickup] = tripInfo;
        }

        taxiData.close();
    }
}

void readUberData(bool selection, TreeMap<long long, vector<long long>> &treeMap, HashMap<long long, vector<long long>> &hashMap) {
    ifstream uberData("UberData.csv");
    if(uberData.is_open()) {
        string line;
        istringstream line_stream;

        while (!uberData.eof()) {
            string dispatchBase, pickupFull, dropoffFull, pickupID, dropoffID, pickupFix, dropoffFix;
            long long pickup, dropoff, pickupIDlong, dropoffIDlong;
            vector<long long> tripInfo;
            getline(uberData, line, '\n');
            line_stream.str(line);

            getline(line_stream, dispatchBase, ',');
            getline(line_stream, pickupFull, ',');

            for (int j = 0; j < pickupFull.length(); j++) {
                if (pickupFull[j] != '-' && pickupFull[j] != ' ' && pickupFull[j] != ':') {
                    pickupFix += pickupFull[j];
                }
            }
            try {
                pickup = stoll(pickupFix);
            } catch (invalid_argument &) {
                pickup = 0;
            }
            getline(line_stream, dropoffFull, ',');
            for (int k = 0; k < dropoffFull.length(); k++) {
                if (dropoffFull[k] != '-' && dropoffFull[k] != ' ' && dropoffFull[k] != ':') {
                    dropoffFix += dropoffFull[k];
                }
            }
            try {
                dropoff = stoll(dropoffFix);
            } catch (invalid_argument &) {
                dropoff = 0;
            }
            tripInfo.push_back(dropoff);
            getline(line_stream, pickupID, ',');
            try {
                pickupIDlong = stoll(pickupID);
            } catch (invalid_argument &) {
                pickupIDlong = 264;
            }

            tripInfo.push_back(pickupIDlong);
            getline(line_stream, dropoffID, ',');

            try {
                dropoffIDlong = stoll(pickupID);
            } catch (invalid_argument &) {
                dropoffIDlong = 264;
            }

            tripInfo.push_back(dropoffIDlong);

            if (selection)
                treeMap[pickup] = tripInfo;
            else
                hashMap[pickup] = tripInfo;
        }

        uberData.close();
    }
}
