##include <iostream>
#include <list>
#include "../rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "../rapidxml/rapidxml_utils.hpp" //Clase File
#include "../headers/main.hpp"
#include "../headers/Observer.hpp"
#include "../headers/Selection.hpp"



/*
*****************
*    GLOBALES   *
*****************
*/
int frames, angulo, height, width;
list <xml_node<>* > selected_paths; //Unicamente agregar los node_element con etiquetas"path" y/o "g"

vector <Path> capturedPathList;
vector <Path> selectedPathList;


//Recorre el elemento raíz del documento
void extractXMLData(xml_document<>* doc){
  xml_node<>* node = doc->first_node();

  cout << "Etiqueta: " << node->name() << endl;
  for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
    cout << " Atributo: " << attrib->name() << endl;
    cout << "\tValor: " << attrib->value() << endl;
  }

  extractNodeData(node);
}

//Recorre el resto de elementos del documento
void extractNodeData(xml_node<>* node){
  for (node = node->first_node(); node != NULL; node = node->next_sibling()){
    if (node->type() == node_element){
      cout << "Etiqueta: " << node->name() << endl;

      for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
        cout << "\tAtributo: " << attrib->name() << endl;
        cout << "\t-Valor: " << attrib->value() << endl;
      }

      extractNodeData(node);
    }
  }
}

/*
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
*/
int main() {
    //Leer XML
    file<> file("../svganimation/images/svg/wifi-2.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    //extractXMLData(&myDoc);
    xml_node<> *root = myDoc.first_node("svg");
    // Get root node

    cout << endl;
    //extractPath(&myDoc);

    //Modificar un atributo existente
    //Modifica el atributo indicado del primer elemento <path> que se encuentre
    //xml_node<> *modifyNode = myDoc.first_node()->first_node("path")

    return 0;
}