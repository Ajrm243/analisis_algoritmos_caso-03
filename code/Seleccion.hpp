#include "main.hpp"


//Lista de colores dadas por el usuario
list <string> lista_colores = {"red","yellow"};

//Recorrer y reconocer los paths
void extractData(xml_node<>* node){
    //Reconocer con base en la etiqueta del nodo si los node_element "path" y "g" --> Por el momento
    //Por el momento unicamente se estan imprimiendo hasta definir la estructura que se utilizara para almacenarlas
    for (node = node->first_node(); node != NULL; node = node->next_sibling()){
        
        if (node->type() == node_element){
        string etiqueta = node->name();
        string relleno, color;
        xml_attribute<>* attrib;
        if (etiqueta == "path"){

            cout << "Etiqueta: " << node->name() << endl;
            attrib = node->first_attribute("stroke");
            color = attrib->value();
            list<string>::iterator findIter = find(lista_colores.begin(), lista_colores.end(), color);
            if(findIter != lista_colores.end()){
                cout<<"Coincidencia encontrada"<<endl;
            }

            /*
            for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
                relleno = attrib->name();
                if (relleno == "stroke"){
                    color  = attrib->value();           
                    list<string>::iterator findIter = find(lista_colores.begin(), lista_colores.end(), color);
                    if(findIter != lista_colores.end()){
                        cout<<"Coincidencia encontrada"<<endl;
                    }
                }
                */
                }
        
        
        if (etiqueta == "g")
        {
            cout << "Etiqueta: " << node->name() << endl;
            attrib = node->first_attribute("fill");
            color = attrib->value();
            list<string>::iterator findIter = find(lista_colores.begin(), lista_colores.end(), color);
            if(findIter != lista_colores.end()){
                cout<<"Coincidencia encontrada"<<endl;
            }
            /*
            for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
                relleno = attrib->name();
                if (relleno == "fill"){
                    cout << " Atributo: " << attrib->name() << endl;
                    cout << "\tValor: " << attrib->value() << endl;
                    
                    color  = attrib->value();
                
                    list<string>::iterator findIter = find(lista_colores.begin(), lista_colores.end(), color);
                    if(findIter != lista_colores.end()){
                        cout<<"Coincidencia encontrada"<<endl;
                    }
                    
                }
                
                }*/
        }
        extractData(node);
        }
        
        }
    }


void extractPath(xml_document<>* doc){
    xml_node<>* node = doc->first_node();

    cout << "Etiqueta: " << node->name() << endl;
    cout<< node->name()<<endl;
    for (xml_attribute<>* attrib = node->first_attribute(); attrib != NULL; attrib = attrib->next_attribute()){
        //Reconocer y guardar valores del svg como el height y el width
        cout << " Atributo: " << attrib->name() << endl;
        cout << "\tValor: " << attrib->value() << endl;
    }

    extractData(node);
    }

