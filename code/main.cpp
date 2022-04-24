#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
//#include "headers/observers.hpp"
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

//Recorrer y Extraer los paths
void extractPath(xml_node<>* node){
  for (xml_node<> * student_node = node->first_node(); student_node; student_node = student_node->next_sibling())
    {
        cout << "\nStudent Type =   " << student_node->first_attribute("d")->value();
        cout << endl;
        if (node->type() == node_element){
          cout << "Etiqueta: " << node->name() << endl;

          for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
            cout << "\tAtributo: " << attrib->name() << endl;
            cout << "\t-Valor: " << attrib->value() << endl;
      }   
            // Interate over the Student Names
        cout << endl;
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
    file<> file("ejemplos_svg/EjemploSimple2.svg"); // Lee y carga el archivo en memoria
    xml_document<> myDoc; //Raíz del árbol DOM
    myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

    //Recorrer elementos y atributos
    //extractXMLData(&myDoc);
    xml_node<> *root = myDoc.first_node("svg");
    cout << endl;
    extractPath(root);
    //Modificar un atributo existente
    //Modifica el atributo indicado del primer elemento <path> que se encuentre
    //xml_node<> *modifyNode = myDoc.first_node()->first_node("path");
    


    return 0;
}