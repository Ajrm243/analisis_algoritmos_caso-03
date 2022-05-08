#ifndef GENERATOR_H
#define GENERATOR_H
#include "../headers/main.hpp"

using namespace std;
class Generator : public Observer {
    private:
    // ratio es un numero arbitrario que más o menos expresa qué tan grande es el canvas
    double ratio;
    double canvasHeight;
    double canvasWidth;
    vector<Path> selectedPathList;
    // {R,G,B}, {R,G,B}
    vector<vector<int>> allColorsByChannel;
    public:
        Generator() {}
        ~Generator() {}
        // https://www.plantuml.com/plantuml/svg/PP31JiCm44Jl_efHBgI7_a0aAY5GkQ1o27o0usoe8ROZUmD4LVyTjwcRfFXcUtPsvh7cbl1Q1VBVv94_k-rAX2zjE-cbGU0XVWVsMd5lMd4tVLd7j7MMTz8GNdgbQubIse2teQCVhvcysEkQGARZ0OPCHJu8MKKtgHYgbI6WxAjFYhU3U62MQf-dA2lnH3SFEyUw6VALE0fnsewM6ePhaabHZ0hHE0_Pjd3G5kuo7-8EmAqtxrqjcV8LZe9iVUuXXBOnRoFLZ4MK7rBQ8zBKQNaAdLszCwmtqsI13DUJ2J5MVNHMUM9Aq_JBSVyS0V1CNFAu1oZdbp2gpW__0DnO5yNC9xxttYxdfzvZj2mPf0ePP82A_4pNaY7BOS5bee4htsKohp_svsZA5SMe5WibxgTIwyqixooRGtPHHBwdhX7oBSK5Qyon_m40
        // segun esto los observers tambien pueden tener la referencia del subject
        void update(void* pUserPacket) {
            infoPacket* castedPacket = (static_cast<infoPacket*>(pUserPacket));
            update(castedPacket);
        }
        void update(infoPacket* pUserPacket) {
            /*
            * en el packet interesa:
            * 1- nodo xml (padre) del svg
            * 2- lista de colores del usuario
            * 3- lista de puntos a buscar aproximar
            */

        }
        void generate(){
          
        }
        void writeSVG(){
            //Escribir un nuevo archivo
          file<> file("wifi-1.svg"); // Lee y carga el archivo en memoria
          xml_document<> myDoc; //Raíz del árbol DOM
          myDoc.parse<0>(file.data()); //Parsea el XML en un DOM

          ofstream copyFile("sample2.svg"); //Nuevo archivo
          stringstream ss;
          ss << *myDoc.first_node(); //Pasa el nodo raíz a ss
          string stringXML = ss.str(); //ss.toString
          copyFile << stringXML;
          copyFile.close(); //Escribe y cierra
        }

        void produce(){

        }

        void consumer(){

        }

};
#endif