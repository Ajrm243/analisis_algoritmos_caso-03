#include <iostream>
#include <list>
#include <bits/stdc++.h>
#include "rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "rapidxml/rapidxml_utils.hpp" //Clase File
#include "headers/observers.hpp"

//using namespace std;
class Operator : public Subject{

    private:
    std::list<Observer*> ObserverList;

    public:

    void attach(Observer* pObserver) {
        ObserverList.push_back(pObserver);
    }

    void detach(Observer* pObserver) {
        ObserverList.remove(pObserver);
    }

};


class Selector : public Observer {

};

class Router : public Observer {

};

class Generator : public Observer {

};

int main() {
    /*
    //Leer XML
    file<> file("ejemplos_svg/EjemploSimple1.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    //extractXMLData(&myDoc);
    xml_node<> *root = myDoc.first_node("svg");
    // Get root node

    cout << endl;
    extractPath(&myDoc);

    //Modificar un atributo existente
    //Modifica el atributo indicado del primer elemento <path> que se encuentre
    //xml_node<> *modifyNode = myDoc.first_node()->first_node("path");
    */
   


    return 0;
}