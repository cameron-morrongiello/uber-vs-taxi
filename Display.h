//
// Created by Cameron Morrongiello on 8/4/20.
//

#include "HashMap.h"
#include "TreeMap.h"

#include <vector>
#include <iostream>
#include <string>

#ifndef UBER_VS_TAXI_DISPLAY_H
#define UBER_VS_TAXI_DISPLAY_H



class Display{

public:

    static void perMonthTree(TreeMap<long long ,std::vector<long long >> &taxiTreeMap, TreeMap<long long ,std::vector<long long >> &uberTreeMap);
    static void perMonthHash(HashMap<long long ,std::vector<long long >> &taxiHashMap, HashMap<long long ,std::vector<long long >> &uberHashMap);


    static void
    timeDayTree(TreeMap<long long , std::vector<long long >> &taxiTreeMap, TreeMap<long long , std::vector<long long >> &uberTreeMap, long long hour);
    static void
    timeDayHash(HashMap<long long ,std::vector<long long >> &taxiHashMap, HashMap<long long ,std::vector<long long >> &uberHashMap, long long hour);

    static void avgTripTree(TreeMap<long long ,std::vector<long long >> &taxiTreeMap, TreeMap<long long ,std::vector<long long >> &uberTreeMap);
    static void avgTripHash(HashMap<long long ,std::vector<long long >> &taxiHashMap, HashMap<long long ,std::vector<long long >> &uberHashMap);



private:


    // Helpers
    static int getHourNum(long long datelong);
    static int getMonthNum(long long datelong);
    static int getTotalSeconds(long long datelong);

    // Hash
    static std::vector<int > calcPerMonthHash(HashMap<long long ,std::vector<long long >> &hashMap);
    static std::vector<long long > calcTimeHash(HashMap<long long ,std::vector<long long >> &hashMap, long long hour);
    static int  calcAvgTripHash(HashMap<long long ,std::vector<long long >> &hashMap);


    // Tree
    static std::vector<int > calcPerMonthTree(TreeMap<long long , std::vector<long long >> &treeMap);
    static std::vector<long long > calcTimeTree(TreeMap<long long , std::vector<long long >> &treeMap, long long hour);
    static int  calcAvgTripTree(TreeMap<long long , std::vector<long long >> &treeMap);

    // Tree Helper
    static void treeIterate(TreeMap<long long , std::vector<long long >> &treeMap, std::vector<std::pair<long long , std::vector<long long >>> &data);
    static void treeIterate(TreeMap<long long ,std::vector<long long >>::Node* root, std::vector<std::pair<long long , std::vector<long long >>> &data);


};

void Display::perMonthTree(TreeMap<long long , std::vector<long long >> &taxiTreeMap, TreeMap<long long , std::vector<long long >> &uberTreeMap) {
    std::vector<int > resTaxi = calcPerMonthTree(taxiTreeMap);
    std::vector<int > resUber = calcPerMonthTree(uberTreeMap);

    std::cout << "Total trips per month (Feb - Aug)" << std::endl;
    std::cout << "Month  |   Uber   |   Taxi " << std::endl;
    std::cout << "Feb    |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;
    std::cout << "Mar    |   " << resUber.at(2) << "    |   " << resTaxi.at(2) << std::endl;
    std::cout << "Apr    |   " << resUber.at(3) << "    |   " << resTaxi.at(3) << std::endl;
    std::cout << "May    |   " << resUber.at(4) << "    |   " << resTaxi.at(4) << std::endl;
    std::cout << "Jun    |   " << resUber.at(5) << "    |   " << resTaxi.at(5) << std::endl;
    std::cout << "Jul    |   " << resUber.at(6) << "    |   " << resTaxi.at(6) << std::endl;
    std::cout << "Aug    |   " << resUber.at(7) << "    |   " << resTaxi.at(7) << std::endl;
    std::cout << "Sep    |   " << resUber.at(8) << "    |   " << resTaxi.at(8) << std::endl;

}

void Display::perMonthHash(HashMap<long long , std::vector<long long >> &taxiHashMap, HashMap<long long , std::vector<long long >> &uberHashMap) {

    std::vector<int> resTaxi = calcPerMonthHash(taxiHashMap);
    std::vector<int> resUber = calcPerMonthHash(uberHashMap);

    std::cout << "Total trips per month (Feb - Aug)" << std::endl;
    std::cout << "Month  |   Uber   |   Taxi " << std::endl;
    std::cout << "Feb    |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;
    std::cout << "Mar    |   " << resUber.at(2) << "    |   " << resTaxi.at(2) << std::endl;
    std::cout << "Apr    |   " << resUber.at(3) << "    |   " << resTaxi.at(3) << std::endl;
    std::cout << "May    |   " << resUber.at(4) << "    |   " << resTaxi.at(4) << std::endl;
    std::cout << "Jun    |   " << resUber.at(5) << "    |   " << resTaxi.at(5) << std::endl;
    std::cout << "Jul    |   " << resUber.at(6) << "    |   " << resTaxi.at(6) << std::endl;
    std::cout << "Aug    |   " << resUber.at(7) << "    |   " << resTaxi.at(7) << std::endl;
    std::cout << "Sep    |   " << resUber.at(8) << "    |   " << resTaxi.at(8) << std::endl;



}

void Display::timeDayTree(TreeMap<long long , std::vector<long long >> &taxiTreeMap, TreeMap<long long , std::vector<long long >> &uberTreeMap,
                          long long hour) {

    std::vector<long long> resTaxi = calcTimeTree(taxiTreeMap, hour);
    std::vector<long long> resUber = calcTimeTree(uberTreeMap, hour);

    std::cout << "Total trips before and after " << hour << " o'clock (Feb - Aug)" << std::endl;
    std::cout << "Hour   |   Uber   |   Taxi " << std::endl;
    std::cout << "Before |   " << resUber.at(0) << "    |   " << resTaxi.at(0) << std::endl;
    std::cout << "After  |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;



}

void Display::timeDayHash(HashMap<long long , std::vector<long long >> &taxiHashMap, HashMap<long long , std::vector<long long >> &uberHashMap,
                          long long hour) {

    std::vector<long long > resTaxi = calcTimeHash(taxiHashMap, hour);
    std::vector<long long > resUber = calcTimeHash(uberHashMap, hour);

    std::cout << "Total trips before and after " << hour << " o'clock (Feb - Aug)" << std::endl;
    std::cout << "Hour   |   Uber   |   Taxi " << std::endl;
    std::cout << "Before |   " << resUber.at(0) << "    |   " << resTaxi.at(0) << std::endl;
    std::cout << "After  |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;

}


void Display::avgTripTree(TreeMap<long long , std::vector<long long >> &taxiTreeMap, TreeMap<long long , std::vector<long long >> &uberTreeMap) {
    long long resTaxi = calcAvgTripTree(taxiTreeMap);
    long long resUber = calcAvgTripTree(uberTreeMap);

    std::cout << "Total trips average duration (Feb - Aug)" << std::endl;
    std::cout << "Avg Trip Time in Min  |   Uber   |   Taxi " << std::endl;
    std::cout << "Avg Trip              |   " << resUber << "     |   " << resTaxi << std::endl;


}

void Display::avgTripHash(HashMap<long long , std::vector<long long >> &taxiHashMap, HashMap<long long , std::vector<long long >> &uberHashMap) {

    long long resTaxi = calcAvgTripHash(taxiHashMap);
    long long resUber = calcAvgTripHash(uberHashMap);

    std::cout << "Total trips average duration (Feb - Aug)" << std::endl;
    std::cout << "Avg Trip Time in Min  |   Uber   |   Taxi " << std::endl;
    std::cout << "Avg Trip              |   " << resUber << "     |   " << resTaxi << std::endl;

}

int Display::getMonthNum(long long datelong) {
    std::string dateString = std::to_string(datelong);

    return stoi(dateString.substr(4, 2));
}

int Display::getTotalSeconds(long long datelong) {

    std::string dateString = std::to_string(datelong);

    int hour = stoi(dateString.substr(8, 2));
    int min = stoi(dateString.substr(10, 2));
    int sec = stoi(dateString.substr(12, 2));

    return (hour * 3600) + (min * 60) + sec;
}

int Display::getHourNum(long long datelong) {

    std::string dateString = std::to_string(datelong);

    std::string hour = dateString.substr(8, 2);

    return stoi(hour);
}



std::vector<int> Display::calcPerMonthHash(HashMap<long long , std::vector<long long >> &hashMap) {
    int jan = 0, feb = 0, mar = 0, apr = 0, may = 0, jun = 0, jul = 0 , aug = 0 , sep = 0;

    auto taxiHashTable = hashMap.getHashTable();
    for(auto &list : taxiHashTable){
        for(auto &element : list){
            std::cout << (element.first) <<std::endl;
            std::cout << getHourNum(element.first) <<std::endl;
            switch (getMonthNum(element.first)){
                case 1 :
                    ++jan;
                    break;
                case 2 :
                    ++feb;
                    break;
                case 3 :
                    ++mar;
                    break;
                case 4 :
                    ++apr;
                    break;
                case 5 :
                    ++may;
                    break;
                case 6 :
                    ++jun;
                    break;
                case 7 :
                    ++jul;
                    break;
                case 8 :
                    ++aug;
                    break;
                case 9 :
                    ++sep;
                    break;

            }
        }
    }

    return std::vector<int > {jan, feb, mar, apr, may, jun, jul, aug, sep};

}



std::vector<long long > Display::calcTimeHash(HashMap<long long , std::vector<long long >> &hashMap, long long hour) {

    long long before = 0, after = 0;

    auto hashTable = hashMap.getHashTable();
    for(auto &list : hashTable) {
        for (auto &element : list) {

            if (getHourNum(element.first) > hour){
                ++after;
            } else {
                ++before;
            }
        }
    }

    return std::vector<long long > {before, after};
}


int Display::calcAvgTripHash(HashMap<long long , std::vector<long long >> &hashMap) {

    int seconds = 0;
    int trips = 0;
    auto hashTable = hashMap.getHashTable();
    for (auto &list : hashTable) {
        for (auto &element : list) {

            int start = getTotalSeconds(element.first);
            int end = getTotalSeconds(element.second.at(0));

            int total = end - start;

            if (total >= 0) { // get ride of next day rides
                seconds += total;
                ++trips;
            }
        }

    }
    return ((seconds / 60) / trips);
}

std::vector<int > Display::calcPerMonthTree(TreeMap<long long , std::vector<long long >> &treeMap) {

    std::vector<std::pair<long long , std::vector<long long >>> data;
    treeIterate(treeMap, data);


    int jan = 0, feb = 0, mar = 0, apr = 0, may = 0, jun = 0, jul = 0 , aug = 0 , sep = 0;

    for (auto &element : data) {
        switch (getMonthNum(element.first)) {
            case 1 :
                ++jan;
                break;
            case 2 :
                ++feb;
                break;
            case 3 :
                ++mar;
                break;
            case 4 :
                ++apr;
                break;
            case 5 :
                ++may;
                break;
            case 6 :
                ++jun;
                break;
            case 7 :
                ++jul;
                break;
            case 8 :
                ++aug;
                break;
            case 9 :
                ++sep;
                break;

        }
    }
    return std::vector<int > {jan, feb, mar, apr, may, jun, jul, aug, sep};
}


std::vector<long long > Display::calcTimeTree(TreeMap<long long , std::vector<long long >> &treeMap, long long hour) {
    long long before = 0, after = 0;

    std::vector<std::pair<long long , std::vector<long long >>> data;
    treeIterate(treeMap, data);


    for (auto &element : data) {
            if (getHourNum(element.first) > hour){
                ++after;
            } else {
                ++before;
            }
        }


    return std::vector<long long > {before, after};
}

int Display::calcAvgTripTree(TreeMap<long long , std::vector<long long >> &treeMap) {
    int seconds = 0;
    int trips = 0;

    std::vector<std::pair<long long , std::vector<long long >>> data;
    treeIterate(treeMap, data);

    for (auto &element : data) {

        int start = getTotalSeconds(element.first);
        int end = getTotalSeconds(element.second.at(0));

        int total = end - start;

            if (total >= 0) { // get ride of next day rides
                seconds += total;
                ++trips;
            }
    }
    return ((seconds / 60) / trips);
}

void Display::treeIterate(TreeMap<long long , std::vector<long long >>::Node *root, std::vector<std::pair<long long , std::vector<long long >>> &data) {

    if (!root)
        return;

    treeIterate(root->left, data);
    std::pair<long long , std::vector<long long >> pair (root->key, root->data);
    data.push_back(pair);
    treeIterate(root->right, data);

}

void Display::treeIterate(TreeMap<long long , std::vector<long long >> &treeMap, std::vector<std::pair<long long , std::vector<long long >>> &data) {
    auto root = treeMap.getRoot();
    treeIterate(root, data);
}


#endif //UBER_VS_TAXI_DISPLAY_H
