

#include "../rapidxml/rapidxml_ext.hpp" //Clases para manejo del DOM
#include "../rapidxml/rapidxml_utils.hpp" //Clase File
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
//#include <ObserverPattern.h>
//#include <../headers/ObserverPattern.h>
#include "../headers/Path.hpp"
using namespace std;
using namespace rapidxml; //Namespace de la librería

void extractXMLData(xml_document<>* doc);

void extractNodeData(xml_node<>* node);
