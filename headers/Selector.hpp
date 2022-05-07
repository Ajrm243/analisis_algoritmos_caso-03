#include "../headers/main.hpp"
//#include "../headers/Path.hpp"
//#include "../headers/Observer.hpp"

// Se utiliza para escalar con el ratio la proximidad entre puntos
#define MAGNETIC_POWER 50.5
#ifndef SVG_DIMENSION_PATTERN
#define SVG_DIMENSION_PATTERN "0 0 (\\d+(.?\\d+)?) (\\d+(.?\\d+)?)"
#endif

using namespace std;
class Selector : public Observer {
    private:
    // ratio es un numero arbitrario que más o menos expresa qué tan grande es el canvas
    double ratio;
    vector<Path> allPathsList;
    public:
        Selector() {}
        ~Selector() {}

        void update(void* pSelectionProcess) {
            // (int*) = castear el puntero void a puntero a int
            // *(int*) = valor del int al que apunta
            int stepValue = *(int*)pSelectionProcess;
            if (stepValue == 0)
                cout << "Recolectando elementos paths" << endl;
            else if (stepValue == 1)
                cout << "Recolectando paths con coincidencias de color" << endl;
            else if (stepValue == 2)
                cout << "Analizando intersecciones de puntos con valores de paths" << endl;
        }
        void collectPaths(xml_node<>* pNode){
            //vector <Path> capturedPathList;
            //Recognize based on the node tag if the node_element "path" and "g" --> At the moment
            //At the moment they are only being printed until defining the structure that will be used to store them
            bool isRatioSet = false;
            for (pNode = pNode->first_node(); pNode != NULL; pNode = pNode->next_sibling()){
                Path path;
                if (pNode->type() == node_element){
                    string label = pNode->name();
                    path.setTag(label);
                    string d, color, idPath, stringWidth, stringHeight;
                    if (label == "svg") {;
                        // 2 opciones: viewBox o Height & Width
                        xml_attribute<>* lookupAttr = pNode->first_attribute("viewBox");
                        if (lookupAttr != NULL) {
                            // haga regex del viewbox y parsee los 2 puntos
                            smatch viewBoxMatch;
                            string attrValue = static_cast<string>(lookupAttr->value());
                            regex_search(attrValue, viewBoxMatch, static_cast<regex>(SVG_DIMENSION_PATTERN));
                            // se opera por los grupos de captura
                            // el width es grupo 1 y height grupo 3
                            ratio = stod(viewBoxMatch[1].str()) / stod(viewBoxMatch[3].str()) * MAGNETIC_POWER;
                        }
                        else {
                            // se maneja con los atributos width y height
                            stringWidth = pNode->first_attribute("width")->value();
                            stringHeight = pNode->first_attribute("height")->value();
                            // define el ratio de una vez
                            ratio = stod(stringWidth) / stod(stringHeight) * MAGNETIC_POWER;
                        }
                    }
                    if (label == "path"){
                        idPath = pNode->first_attribute("id")->value();
                        path.setId(idPath);
                        d = pNode->first_attribute("d")->value();
                        path.setPath(d);
                        allPathsList.push_back(path);
                        // con color depende del atributo que exista
                        // prioridad: 1-stroke 2-fill 3-opacity
                        if (pNode->first_attribute("stroke") != NULL) {
                            path.setColor(pNode->first_attribute("stroke")->value());
                        } else if (pNode->first_attribute("fill") != NULL) {
                            path.setColor(pNode->first_attribute("fill")->value());
                        } else {
                            path.setColor(pNode->first_attribute("opacity")->value());
                        }
                    }
                }
            }
            
        }
        bool RGBMatch(vector< vector<int> > colorList, vector<int> colorComparar){
            // colorlist[0]=RED, colorlist[1]=GREEN, colorlist[2]=BLUE
            bool matchRangeColor = false;
            for(int i = 0; colorList.size(); i++){
                int redDiference = abs(colorComparar[0] - colorList[i][0]);
                int blueDiference = abs(colorComparar[0] - colorList[i][0]);
                int greenDiference = abs(colorComparar[0] - colorList[i][0]);        
                if (redDiference <= 30 && blueDiference <= 30 && greenDiference <=30){
                    matchRangeColor = true;
                    break;
                }
            }
            return matchRangeColor;
        }

        int hexadecimalToDecimal(string hexVal) {
            int len = hexVal.size();
            // Initializing base value to 1, i.e 16^0
            int base = 1;
            int dec_val = 0;

            for (int i = len - 1; i >= 0; i--) {

                if (hexVal[i] >= '0' && hexVal[i] <= '9') {
                    dec_val += (int(hexVal[i]) - 48) * base;

                    base = base * 16;
                }

                else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
                    dec_val += (int(hexVal[i]) - 55) * base;
        
                    base = base * 16;
                }
            }
            return dec_val;
        }
        vector<int> RGBConverter(string hexValue){
            int r,g,b;
            string subR = (hexValue.substr(1,2));
            r = hexadecimalToDecimal(subR);
            string subG = (hexValue.substr(2,2));
            g = hexadecimalToDecimal(subG);
            string subB = (hexValue.substr(5,2));
            b = hexadecimalToDecimal(subB);

            cout<<"Sub R "<<subR<<endl;
            cout<<"Sub G "<<subG<<endl;
            cout<<"Sub B "<<subB<<endl;
            return {r,g,b};
        }

        void ColorFilter(vector<Path> pCapturedPathList, vector <vector<int>> pColorList){
            int pathNumber;
            string color;
            vector <Path> filteredPaths;
            for (pathNumber=0; pathNumber<allPathsList.size(); pathNumber++){
                Path path = allPathsList.at(pathNumber);
                color = path.getColor();
                vector<int> rgbValues = RGBConverter(color);
                bool matchDetected = RGBMatch(pColorList,rgbValues);
                if (matchDetected){
                    filteredPaths.push_back(path);
                }
            }
        }

        void splitStringIntoList(string pStr, string pDelimiter, pair<double, double>& pPathPoint) {
            // solo toma 2 elementos
            int start = 0;
            int end = pStr.find(pDelimiter);
            pPathPoint.first = stod(pStr.substr(start, end - start));
            start = end + pDelimiter.size();
            end = pStr.find(pDelimiter, start);
            pPathPoint.second = stod(pStr.substr(start, end - start));
        }

        bool checkProximityBetweenPoints(pair<double, double> pUserPoint, pair<double, double> pPathPoint) {
            double distance = sqrt( pow((pUserPoint.first - pPathPoint.first), 2) + pow((pUserPoint.second - pPathPoint.second), 2) );
            return distance <= ratio; // chequear como hacer que mantenga el ratio
        }
};



//Lista de colores dadas por el usuario
//list <string> colorList = {"red","yellow"};




/*


Analisis de los elementos del svg 


*****************
*   Rectangle   *
*****************
Manera1
<rect x="10" y="10" width="30" height="30"/>



Manera2
<rect x="60" y="10" rx="10" ry="10" width="30" height="30"/>

Manera3
<rect width="300" height="100" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />




*****************
*    Circle     *
*****************
Manera1
<circle cx="25" cy="75" r="20" fill="red"/>    --> r=radio, cy & cx punto central del circulo






*****************
*    Ellipse    *
*****************
Manera1
<ellipse cx="75" cy="75" rx="20" ry="5"/>



Manera2
 <ellipse cx="200" cy="80" rx="100" ry="50" style="fill:yellow;stroke:purple;stroke-width:2" />  --> etiqueta "style" para relleno

    -rx = radio horizontal
    -ry = radio vertical
    -cx & cy = punto central del elipse





*****************
*      Line     *
*****************
Manera1
<line x1="10" x2="50" y1="110" y2="150" stroke="black" stroke-width="5"/>





*****************
*    Polygon    *
*****************
Manera1
<polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />



Grupos de puntos separados por un espacio



*****************
*    Polyline   *
*****************
Manera1
<polyline points="60, 110 65, 120 70, 115 75, 130 80, 125 85, 140 90, 135 95, 150 100, 145"/>



Grupos de puntos separados por un espacio



*****************
*      Path     *
*****************
    @ AYUDA 
        Visualizador de paths = https://svg-path-visualizer.netlify.app/



    Atributo a buscar = "d"  --> define el trazado que va a dibujarse

    Comandos de ruta de acceso:

            ~MOVE TO  (M, m):



                M = M 250 50 
                    Coordenadas donde empieza el trazado.
                m = m  0,10
                    "Mueva el punto actual desplazando la última posición conocida del trazado a lo 
                    largo del eje x y a lo largo del eje y"
            
            ~LINE TO (L,l,H,h,V,v):



                L, V, H --> Utilizan coordenadas absolutas

                L = L 90,90
                    Coloque el lápiz y dibuje una línea a { x: 90, y: 90 }

                V = V 10
                    Mover verticalmente a 10

                H = H 50
                    Mover horizontalmente a 50



                l,v,h --> utilizan coordenadas relativas
                
                L = L 80,80
                    Coloque el bolígrafo y mueva a la derecha 80 y 80 inferior desde la posición actual


                V = V -80
                    Mover el top 80 de la posición actual


                H = H -40
                    Mover a la izquierda 40 de la posición actual
            
            ~Curva cúbica de Bézier (C,c,S,s):



                C & S --> Utilizan coordenadas absolutas

                C = C 30,90 25,10 50,10
                    Trazar una linea curva que involucre los puntos

                S = S 70,90 90,90
                    Suavizar la curva atravesando los puntos

                c & s --> Utilizan coordenadas relativas

                c = c 20,0 15,-80 40,-80
                    Coloque el lápiz y dibuje una curva de Bézier desde el punto actual hasta un nuevo punto { x: punto anterior + 40, y: punto anterior - 80 }



                s = s 20,80 40,80
                    Dibujar una curva de Bézier suave desde el punto actual hasta un nuevo punto { x: punto anterior + 40, y: punto anterior + 80 }
                    
            ~Curva cuadrática de Bézier (Q,q, T,t):



                Q & T --> Utilizan coordenadas absolutas

                Q 25,25 40,50
                    Coloque el lápiz y dibuje una curva de Bézier cuadrática desde el punto actual hasta un nuevo punto { x: 40, y: 50 }

                    El punto de control es { x: 25, y: 25 }  
                

                q & t --> Utilizan coordenadas relativas



                t 30,0 30,0 30,0 30,0 30,0
                t 30,0
                Dibujar una curva de Bézier cuadrática desde el punto actual hasta un nuevo punto { x: punto anterior + 30, y: punto anterior + 0 }
                El punto de control es el reflejo del punto de control final del comando de curva anterior




*************************
*     SWITCH DE CASO    *
*************************
*/