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

using namespace std;
using namespace rapidxml; //Namespace de la librería
void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);

typedef struct infoPacket {
    // tiene elementos modulares
    int packetPhase;
    int frameMod;           // solo para frame data
    string stringMod;       // algun string pertinente
    double angleMod;        // solo para angle data
    xml_node<>* nodeMod;    // nodo padre del svg
    // listas de elementos
    vector<string> hexColorListMod;
    vector<vector<int>> rgbColorListMod;
    vector<pair<double, double>> pointListMod;
    vector<Path> pathListMod;
    vector<xml_node<>*> nodeListMod;
};
#include "../headers/Observer.hpp"
#include "../headers/Processor.hpp"
/*
class Processor: public Subject {
    private:
        vector<Observer> observerList;
    public:
        Processor();
        ~Processor();
        void attach(Observer* pObserver) {
            observerList.push_back( *(static_cast<Observer*>(pObserver)) );
        }
        void detach(Observer* pObserver) {
            observerList.erase(remove(observerList.begin(), observerList.end(), *pObserver), observerList.end());
        }
        void notify(void* pPackageInfo) {
        }
        void notify(int pPhase, infoPacket pPacket) {
            // hacer algo con los notify
            switch (pPhase)
            {
            case 1:
                // SELECTION
                // envia el paquete como puntero a vacío
                cout << "Llego a Selection" << endl;
                observerList.at(0).update(static_cast<void*>(&pPacket));
                break;
            case 2:
                // ROUTING
                // envia el paquete como puntero a vacío
                cout << "Llego a Routing" << endl;
                //observerList.at(1).update(static_cast<void*>(&pPacket));
                break;
            case 3:
                // GENERATION
                // envia el paquete como puntero a vacío
                //observerList.at(2).update(static_cast<void*>(&pPacket));
                break;
            default:
                // no debería entrar aquí
                break;
            }
        }
};
*/




#endif