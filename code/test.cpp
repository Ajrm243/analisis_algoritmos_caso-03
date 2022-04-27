#include <iostream>
#include <list>
#include <string>
#include <bits/stdc++.h>
#include <regex>
#include <vector>
#include <utility>
#include <algorithm>
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

void checkIntersections() {
    regex pathPointsSeparatorRegex;
    smatch separatedPathPoints;
    list<double> currentPathPoints;
    for (pair<double, double> point : pointsList) {
        switch (positionsFromOnePath.size()) {
            case 1: {}
            case 2: {
                
            }
            case 4: {}
            case 6: {}
            default: {
                break;
            }
        }
    }
}

int main() {

    // example point list
    pointsList = {
        {1,1},
        {2,2},
        {3,3}
    };
    // example path d list
    pathDescriptionList = {
        "M1945.305,19.063c0.684,0,0.512,0.35,0.512-1.769c-0.689,0.138-0.557,0.203-0.557-0.174c0.665-0.134,0.473-0.112,0.868-0.112c0,2.465-0.171,2.054,0.512,2.054c0,0.352,0.267,0.264-1.335,0.264V19.063z",
        "M1992.138,14.639c1.82,0,2.354,1.722,2.354,3.535c0,1.82-0.541,3.531-2.354,3.531c-1.813,0-2.354-1.71-2.354-3.531C1989.784,16.362,1990.318,14.639,1992.138,14.639z M1992.138,15.369c-1.23,0-1.428,1.576-1.428,2.805c0,1.227,0.199,2.801,1.428,2.801c1.232,0,1.432-1.565,1.432-2.801C1993.57,16.941,1993.373,15.369,1992.138,15.369z",
        "M2035.019,22.756h2.626v-9.065l-2.857,0.573v-1.464c3.412-0.688,2.424-0.573,4.449-0.573v10.529h2.626v1.353h-6.844V22.756z"
    };

    // do magic
    string toFind = pathDescriptionList.at(0);
    string movementStr;
    bool copied = false;
    regex rx(pattern);
    regex subrx(subPat);
    /*
    for(sregex_iterator i = sregex_iterator(toFind.begin(), toFind.end(), rx); i != sregex_iterator(); ++i) {
        smatch movement = *i;
        cout << movement.str() << " at position: " << movement.position() << endl;
        smatch coordinates;
        movementStr = movement.str();
        regex_search(movementStr, coordinates, subrx);
        for (auto coord : coordinates) {
            cout << coord << endl;
        }
        cout << "----" << endl;
    }
   */

    for (string pathDescription : pathDescriptionList) {
        listMovementsFromPath(pathDescription);
        checkIntersections();
        pathDescriptionList.clear();
    }

    


    //listMovementsFromPath(pointsList.at(0), pathDescriptionList.at(0));
    // checkIntersection
    // vaciar lista


    return 0;
}