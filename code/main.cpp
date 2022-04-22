#include <iostream>
#include <list>
#include "headers/observers.hpp"
#include "main.hpp"

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
    return 0;
}