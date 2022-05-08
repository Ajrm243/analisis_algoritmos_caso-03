
//#include <bits/stdc++.h>
#include "../headers/main.hpp"
#include "../headers/Processor.hpp"

//using namespace std;
//using namespace rapidxml;

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

int main() {
    // instancias de las clases
    Processor mainProcess = Processor();
    Selector selectionObserver = Selector();
    //Router routingObserver = Router();
    //Generator generationObserver = Generator();
    mainProcess.attachSelector(&selectionObserver);

    // prepara user info
    infoPacket newPacket;
    newPacket.packetPhase = 1;  // default 1 at start
    newPacket.angleMod = 120;   // user angle
    newPacket.frameMod = 20;    // user frames
    newPacket.hexColorListMod = {
        "FFFFFF",
        "AABBCC",
        "000000",
        "9FBBCF"
    };
    newPacket.rgbColorListMod = {
        {255, 255, 255},
        {170, 187, 204},
        {0,0,0},
        {159, 187, 207}
    };
    newPacket.pointListMod = {
        {2000, 30},
        {1500, 150},
        {2340, 680},
        {3377, 137}
    };
    // prepara nodo padre del arbol
    rapidxml::file<> svgFile("ejemplos_svg/EjemploComplejo1.svg");
    rapidxml::xml_document<> svgDoc;
    svgDoc.parse<0>(svgFile.data());
    rapidxml::xml_node<>* svgRootNode = svgDoc.first_node();
    newPacket.nodeMod = svgRootNode;
    mainProcess.notify(1, &newPacket);

    return 0;
}