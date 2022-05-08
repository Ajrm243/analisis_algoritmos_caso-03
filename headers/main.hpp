#ifndef MAIN_HPP
#define MAIN_HPP
#include "../rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "../rapidxml/rapidxml_utils.hpp" //Clase File
//#include "../rapidxml/rapidxml_print.hpp" //Clase de impresion
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
#include <regex>
#include <utility>
#include <thread>
#include <bits/stdc++.h>
#include "../headers/Path.hpp"
#include "../headers/Observer.hpp"


using namespace std;
using namespace rapidxml; //Namespace de la librería
void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

typedef struct infoPacket {
    // tiene elementos modulares
    int packetPhase;
    int frameMod;           // solo para frame data
    string filePathMod;       // algun string pertinente
    double angleMod;        // solo para angle data
    /*
    rapidxml::file<> xmlFileMod;
    rapidxml::xml_document<> xmlMod;
    rapidxml::xml_node<>* nodeMod;    // nodo padre del svg
    */
    // listas de elementos
    vector<string> hexColorListMod;
    vector<vector<int>> rgbColorListMod;
    vector<pair<double, double>> pointListMod;
    vector<Path> pathListMod;
    vector<xml_node<>*> nodeListMod;
    infoPacket() = default;
};

#endif