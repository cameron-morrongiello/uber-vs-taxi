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

    static void perMonthTree(TreeMap<int,std::vector<int>> &taxiTreeMap, TreeMap<int,std::vector<int>> &uberTreeMap);
    static void perMonthHash(HashMap<int,std::vector<int>> &taxiHashMap, HashMap<int,std::vector<int>> &uberHashMap);


    static void
    timeDayTree(TreeMap<int, std::vector<int>> &taxiTreeMap, TreeMap<int, std::vector<int>> &uberTreeMap, int hour);
    static void
    timeDayHash(HashMap<int,std::vector<int>> &taxiHashMap, HashMap<int,std::vector<int>> &uberHashMap, int hour);

    static void avgTripTree(TreeMap<int,std::vector<int>> &taxiTreeMap, TreeMap<int,std::vector<int>> &uberTreeMap);
    static void avgTripHash(HashMap<int,std::vector<int>> &taxiHashMap, HashMap<int,std::vector<int>> &uberHashMap);



private:

    static std::string getDateString(int dateInt);
    static  int getHourNum(int dateInt);
    static  int getMonthNum(int dateInt);
    static int getTotalSeconds(int dateInt);

    // Hash
    static std::vector<int> calcPerMonthHash(HashMap<int,std::vector<int>> &hashMap);
    static std::vector<int> calcTimeHash(HashMap<int,std::vector<int>> &hashMap, int hour);
    static int  calcAvgTripHash(HashMap<int,std::vector<int>> &hashMap);



    // Tree
    static std::vector<int> calcPerMonthTree(TreeMap<int, std::vector<int>> &treeMap);
    static std::vector<int> calcTimeTree(TreeMap<int, std::vector<int>> &treeMap, int hour);
    static int  calcAvgTripTree(TreeMap<int, std::vector<int>> &treeMap);

    // Tree Helper
    static void treeIterate(TreeMap<int, std::vector<int>> &treeMap, std::vector<std::pair<int, std::vector<int>>> &data);
    static void treeIterate(TreeMap<int,std::vector<int>>::Node* root, std::vector<std::pair<int, std::vector<int>>> &data);


};

void Display::perMonthTree(TreeMap<int, std::vector<int>> &taxiTreeMap, TreeMap<int, std::vector<int>> &uberTreeMap) {
    std::vector<int> resTaxi = calcPerMonthTree(taxiTreeMap);
    std::vector<int> resUber = calcPerMonthTree(uberTreeMap);

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

void Display::perMonthHash(HashMap<int, std::vector<int>> &taxiHashMap, HashMap<int, std::vector<int>> &uberHashMap) {

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

void Display::timeDayTree(TreeMap<int, std::vector<int>> &taxiTreeMap, TreeMap<int, std::vector<int>> &uberTreeMap,
                          int hour) {

    std::vector<int> resTaxi = calcTimeTree(taxiTreeMap, hour);
    std::vector<int> resUber = calcTimeTree(uberTreeMap, hour);

    std::cout << "Total trips before and after " << hour << " o'clock (Feb - Aug)" << std::endl;
    std::cout << "Hour   |   Uber   |   Taxi " << std::endl;
    std::cout << "Before |   " << resUber.at(0) << "    |   " << resTaxi.at(0) << std::endl;
    std::cout << "After  |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;



}

void Display::timeDayHash(HashMap<int, std::vector<int>> &taxiHashMap, HashMap<int, std::vector<int>> &uberHashMap, int hour) {

    std::vector<int> resTaxi = calcTimeHash(taxiHashMap, hour);
    std::vector<int> resUber = calcTimeHash(uberHashMap, hour);

    std::cout << "Total trips before and after " << hour << " o'clock (Feb - Aug)" << std::endl;
    std::cout << "Hour   |   Uber   |   Taxi " << std::endl;
    std::cout << "Before |   " << resUber.at(0) << "    |   " << resTaxi.at(0) << std::endl;
    std::cout << "After  |   " << resUber.at(1) << "    |   " << resTaxi.at(1) << std::endl;

}

std::string Display::getDateString(int dateInt) {
    std::string dateString = std::to_string(dateInt);

    std::string month = dateString.substr(0, 1);
    std::string day = dateString.substr(1, 2);
    std::string year = dateString.substr(3, 2);
    std::string hour = dateString.substr(5, 2);
    std::string min = dateString.substr(7, 2);

    return month + "-" + day + "-" + year +  " " + hour + ":" + min;
}

int Display::getMonthNum(int dateInt) {
    std::string dateString = std::to_string(dateInt);

    return stoi(dateString.substr(0, 1));
}



std::vector<int> Display::calcPerMonthHash(HashMap<int, std::vector<int>> &hashMap) {
    int jan = 0, feb = 0, mar = 0, apr = 0, may = 0, jun = 0, jul = 0 , aug = 0 , sep = 0;

    auto taxiHashTable = hashMap.getHashTable();
    for(auto &list : taxiHashTable){
        for(auto &element : list){

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

    return std::vector<int> {jan, feb, mar, apr, may, jun, jul, aug, sep};

}

int Display::getHourNum(int dateInt) {

    std::string dateString = std::to_string(dateInt);

    std::string hour = dateString.substr(5, 2);

    return stoi(hour);
}

std::vector<int> Display::calcTimeHash(HashMap<int, std::vector<int>> &hashMap, int hour) {

    int before = 0, after = 0;

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

    return std::vector<int> {before, after};
}

int Display::getTotalSeconds(int dateInt) {

    std::string dateString = std::to_string(dateInt);

    int hour = stoi(dateString.substr(5, 2));
    int min =stoi(dateString.substr(7, 2));

    return ((hour * 3600) + (min * 60));
}

int Display::calcAvgTripHash(HashMap<int, std::vector<int>> &hashMap) {

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

void Display::avgTripHash(HashMap<int, std::vector<int>> &taxiHashMap, HashMap<int, std::vector<int>> &uberHashMap) {

    int resTaxi = calcAvgTripHash(taxiHashMap);
    int resUber = calcAvgTripHash(uberHashMap);

    std::cout << "Total trips average duration (Feb - Aug)" << std::endl;
    std::cout << "Avg Trip Time in Min  |   Uber   |   Taxi " << std::endl;
    std::cout << "Avg Trip              |   " << resUber << "     |   " << resTaxi << std::endl;

}

void Display::avgTripTree(TreeMap<int, std::vector<int>> &taxiTreeMap, TreeMap<int, std::vector<int>> &uberTreeMap) {
    int resTaxi = calcAvgTripTree(taxiTreeMap);
    int resUber = calcAvgTripTree(uberTreeMap);

    std::cout << "Total trips average duration (Feb - Aug)" << std::endl;
    std::cout << "Avg Trip Time in Min  |   Uber   |   Taxi " << std::endl;
    std::cout << "Avg Trip              |   " << resUber << "     |   " << resTaxi << std::endl;


}

std::vector<int> Display::calcPerMonthTree(TreeMap<int, std::vector<int>> &treeMap) {

    std::vector<std::pair<int, std::vector<int>>> data;
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
    return std::vector<int> {jan, feb, mar, apr, may, jun, jul, aug, sep};
}

void Display::treeIterate(TreeMap<int, std::vector<int>>::Node *root, std::vector<std::pair<int, std::vector<int>>> &data) {

    if (!root)
        return;

    treeIterate(root->left, data);
    std::pair<int, std::vector<int>> pair (root->key, root->data);
    data.push_back(pair);
    treeIterate(root->right, data);

}

void Display::treeIterate(TreeMap<int, std::vector<int>> &treeMap, std::vector<std::pair<int, std::vector<int>>> &data) {
    auto root = treeMap.getRoot();
    treeIterate(root, data);
}

std::vector<int> Display::calcTimeTree(TreeMap<int, std::vector<int>> &treeMap, int hour) {
    int before = 0, after = 0;

    std::vector<std::pair<int, std::vector<int>>> data;
    treeIterate(treeMap, data);


    for (auto &element : data) {
            if (getHourNum(element.first) > hour){
                ++after;
            } else {
                ++before;
            }
        }


    return std::vector<int> {before, after};
}

int Display::calcAvgTripTree(TreeMap<int, std::vector<int>> &treeMap) {
    int seconds = 0;
    int trips = 0;

    std::vector<std::pair<int, std::vector<int>>> data;
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


#endif //UBER_VS_TAXI_DISPLAY_H
