#include <iostream>
#include <list>
#include <string>
//#include <bits/stdc++.h>
#include <regex>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
/*
#include "../rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "../rapidxml/rapidxml_utils.hpp" //Clase File
#include "../headers/main.hpp"
#include "../headers/Observer.hpp"
#include "../headers/Selection.hpp"
*/

/*
vector<string> pathDescriptionList;
vector<float, float> pointsList;
*/
using namespace std;

const string pattern("([MLHVCSQTAZmlhvcsqtaz]{1})([^MLHVCSQTAZmlhvcsqtaz]+)");
const string subPat("((\\w{1})-?(\\d+(\\.\\d{1,3})?)[,-](\\d+(\\.\\d{1,3})?))");
const string getNumbersPattern("(,|-)");
const string getNumbersGreedy("[^MLHVCSQTAZmlhvcsqtaz]+");
list<string> positionsFromOnePath;
vector<pair<double, double>> pointsList;
vector<string> pathDescriptionList;

double canvasHeight = 5000;
double canvasWidth = 4129.539;
double ratio = (canvasWidth / canvasHeight) * 50.5; // la idea es que sea una constante a drede que nos ayude a proporcionar más matches o menos según queramos


void listMovementsFromPath(string pPathCommand) {
    cout << pPathCommand << " enters" << endl;
    regex separatorRegex(getNumbersGreedy);
    smatch separatorMatches;
    regex_search(pPathCommand, separatorMatches, separatorRegex);

    char var = pPathCommand.at(0);
    string movementPoints;
    for (sregex_iterator i = sregex_iterator(pPathCommand.begin(), pPathCommand.end(), separatorRegex); i != sregex_iterator(); ++i) {
        smatch movementParameters = *i;
        movementPoints = movementParameters.str();
        cout << movementPoints << endl;
        positionsFromOnePath.push_back(movementPoints);
    }
    //cout << endl << endl;
}

void splitStringIntoList(string pStr, string pDelimiter, pair<double, double>& pPathPoint) {
    // solo toma 2 elementos
    int start = 0;
    int end = pStr.find(pDelimiter);
    pPathPoint.first = stod(pStr.substr(start, end - start));
    start = end + pDelimiter.size();
    end = pStr.find(pDelimiter, start);
    pPathPoint.second = stod(pStr.substr(start, end - start));
}

bool checkProximityBetweenPoints(pair<double, double> pUserPoint, pair<double, double> pPathPoint) {
    double distance = sqrt( pow((pUserPoint.first - pPathPoint.first), 2) + pow((pUserPoint.second - pPathPoint.second), 2) );
    return distance <= ratio;
}

int main() {

    // example point list
    pointsList = {
        {1,1},
        {2,2},
        {3,3},
        {1980, 15}
    };
    // example path d list
    pathDescriptionList = {
        "M1945.305,19.063c0.684,0,0.512,0.35,0.512-1.769c-0.689,0.138-0.557,0.203-0.557-0.174c0.665-0.134,0.473-0.112,0.868-0.112c0,2.465-0.171,2.054,0.512,2.054c0,0.352,0.267,0.264-1.335,0.264V19.063z",
        "M1992.138,14.639c1.82,0,2.354,1.722,2.354,3.535c0,1.82-0.541,3.531-2.354,3.531c-1.813,0-2.354-1.71-2.354-3.531C1989.784,16.362,1990.318,14.639,1992.138,14.639z M1992.138,15.369c-1.23,0-1.428,1.576-1.428,2.805c0,1.227,0.199,2.801,1.428,2.801c1.232,0,1.432-1.565,1.432-2.801C1993.57,16.941,1993.373,15.369,1992.138,15.369z",
        "M2035.019,22.756h2.626v-9.065l-2.857,0.573v-1.464c3.412-0.688,2.424-0.573,4.449-0.573v10.529h2.626v1.353h-6.844V22.756z"
    };

    string test = "M1945.305,19.063c1023.10,0";
    string p = "[A-Za-z](.*)[A-Za-z]";
    regex testReg = regex(p, regex_constants::ECMAScript);
    smatch testMatches;
    string pointValues;

    for (string path : pathDescriptionList) {
        regex_search(path, testMatches, testReg);
        pointValues = string(testMatches[1]);
        pair<double, double> pathSearchPoint;
        splitStringIntoList(pointValues, ",", pathSearchPoint);
        cout << "Path to Search: " << pathSearchPoint.first << ", " << pathSearchPoint.second << endl;
        for (pair<double, double> userPoint : pointsList) {
            cout << "Point to Search: " << userPoint.first << ", " << userPoint.second << endl;
            if(checkProximityBetweenPoints(userPoint, pathSearchPoint)){
                cout << "(" + to_string(userPoint.first) + ", " + to_string(userPoint.second) + ") found a match!" << endl;
            }
        }

    }


    return 0;
}