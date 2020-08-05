#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> linesFromFiles;


void readFile(string fileName){
    ifstream file(fileName);
    int i = 0;
    string line;
    while(!file.eof()){
        getline(file,line);
        if(i%332432423 == 0){ //this is the randomizing part(may not be the best way to do it)
            linesFromFiles.push_back(line);
        }
        i++;
    }
    file.close();
}

int main() {
    readFile("fhvhv_tripdata_2019-02.csv");
    readFile("fhvhv_tripdata_2019-03.csv");
    readFile("fhvhv_tripdata_2019-04.csv");
    readFile("fhvhv_tripdata_2019-05.csv");
    readFile("fhvhv_tripdata_2019-06.csv");
    readFile("fhvhv_tripdata_2019-07.csv");
    readFile("fhvhv_tripdata_2019-08.csv");
    readFile("fhvhv_tripdata_2019-09.csv");

    ofstream newFile("UberData.csv");
    for(int i; linesFromFiles.size(); i++){
        newFile << linesFromFiles[i];
    }
    newFile.close();
    return 0;
}
