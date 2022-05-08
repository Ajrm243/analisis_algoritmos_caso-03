#ifndef SELECTOR_H
#define SELECTOR_H
#include "../headers/main.hpp"
#include "../headers/Processor.hpp"
// Se utiliza para escalar con el ratio la proximidad entre puntos
#define MAGNETIC_POWER 1800
// Se utiliza para aproximar por un valor de color con cierta tolerancia
#define DALTONISM_INDICATOR 30
#ifndef SVG_DIMENSION_PATTERN
#define SVG_DIMENSION_PATTERN "0 0 (\\d+(.?\\d+)?) (\\d+(.?\\d+)?)"
#endif
#ifndef PATH_D_POINT_PATTERN
#define PATH_D_POINT_PATTERN "(\\d+(\\.\\d+)?),(\\d+(\\.\\d+)?)|(\\d+(\\.\\d)?)(\\s)?(\\d+(\\.\\d)?)"
#endif

using namespace std;
class Selector : public Observer {
    private:
    // ratio es un numero arbitrario que más o menos expresa qué tan grande es el canvas
    double ratio;
    double canvasHeight;
    double canvasWidth;
    vector<Path> allPathsList;
    vector<Path> filteredPathList;
    vector<Path> selectedPathList;
    // {R,G,B}, {R,G,B}
    vector<vector<int>> allColorsByChannel;
    public:
        Selector() {}
        ~Selector() {}
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

           //cout << pUserPacket->filePathMod << endl;
            string filePathContents = pUserPacket->filePathMod;
            rapidxml::file<> svgFile(filePathContents.c_str()); // cuidado con los tipos de datos
            rapidxml::xml_document<> myDoc; //Raíz del árbol DOM
            myDoc.parse<0>(svgFile.data()); //Parsea el XML en un DOM
            rapidxml::xml_node<>* rootNode = myDoc.first_node();
            //cout << rootNode->name() << endl;
            //cout << rootNode->first_attribute()->name() << endl;

            rapidxml::xml_attribute<>* lookupAttr = rootNode->first_attribute("viewBox");
            smatch viewBoxMatch;
            string attrValue = static_cast<string>(lookupAttr->value());
            regex_search(attrValue, viewBoxMatch, static_cast<regex>(SVG_DIMENSION_PATTERN));
            // se opera por los grupos de captura
            // el width es grupo 1 y height grupo 3
            //cout << "Valor del match 1: " << viewBoxMatch[1].str() << endl;
            //cout << "Valor del match 3: " << viewBoxMatch[3].str() << endl;
            ratio = (stod(viewBoxMatch[1].str()) / stod(viewBoxMatch[3].str())) * MAGNETIC_POWER;
            //cout << "Ratio: " << ratio << endl;

            rapidxml::xml_node<>* firstGroupNode = rootNode->first_node("g");
            //getSVGInfo();
            collectPaths(rootNode);
            //cout << "Filter color...\n";
            filterColor(pUserPacket->rgbColorListMod);
/*
            //cout << "Filtered paths:" << endl;
            for (auto p : filteredPathList) {
                //cout << p.getPath() << endl;
            }
*/
            selectFinalPathContestants(pUserPacket->pointListMod);
            // ROUTING necesita la lista de paths seleccionados
            //cout << "Selected paths:" << endl;
            pUserPacket->pathListMod = selectedPathList;
            for (auto path : selectedPathList) {
                cout << path.getPath() << endl;
            }
            // magia oscura para llamar a Router y enviar el selectedPathList
        }

        pair<double, double> collectProperPoint(string pathDescriptor) {
            // hace regex del string y captura los 2 puntos del moveto
            smatch descriptorMatch;
            regex_search(pathDescriptor, descriptorMatch, static_cast<regex>(PATH_D_POINT_PATTERN));
            // el regex tiene grupos de captura, 1 es X y 3 es Y
            return {stod(descriptorMatch[1].str()) , stod(descriptorMatch[3].str())};
        }

        // 1
        void collectPaths(xml_node<>* pNode){
            //vector <Path> capturedPathList;
            //Recognize based on the node tag if the node_element "path" and "g" --> At the moment
            //At the moment they are only being printed until defining the structure that will be used to store them
            for (pNode = pNode->first_node(); pNode != NULL; pNode = pNode->next_sibling()){
                Path path;
                if (pNode->type() == node_element){
                    string label = pNode->name();
                    //cout << "Entra con el label: " << label << endl;
                    path.setTag(label);
                    string d, color, idPath, stringWidth, stringHeight;
                    if (label == "path"){
                        //cout << "encuentra path\n";
/*
                        idPath = pNode->first_attribute("id")->value();
                        path.setId(idPath);
*/
                        d = pNode->first_attribute("d")->value();
                        path.setPath(d);
                        // con color depende del atributo que exista
                        // prioridad: 1-stroke 2-fill 3-opacity
                        if (pNode->first_attribute("stroke") != NULL) {
                            path.setColor(pNode->first_attribute("stroke")->value());
                        } else if (pNode->first_attribute("fill") != NULL) {
                            path.setColor(pNode->first_attribute("fill")->value());
                        } else if (pNode->first_attribute("opacity") != NULL) {
                            path.setColor(pNode->first_attribute("opacity")->value());
                        } else {
                            path.setColor("#000000"); // negro default
                        }

                        // saca el punto propio de comparacion
                        pair<double, double> pathPair = collectProperPoint(path.getPath());
                        path.setProperPoint(pathPair);
                        // push a la lista de paths
                        allPathsList.push_back(path);
                        //cout << "Collect count: " << allPathsList.size() << endl;
                    }
                }
            }
            
        }

        bool matchRGB(vector<vector<int>> colorList, vector<int> colorToCompare){
            // colorlist[0]=RED, colorlist[1]=GREEN, colorlist[2]=BLUE
            bool matchRangeColor = false;
            for(vector<int> pathColor : colorList){
                int redDiference = abs(colorToCompare[0] - pathColor[0]);
                int blueDiference = abs(colorToCompare[1] - pathColor[1]);
                int greenDiference = abs(colorToCompare[2] - pathColor[2]);
                if (redDiference <= DALTONISM_INDICATOR && blueDiference <= DALTONISM_INDICATOR && greenDiference <= DALTONISM_INDICATOR){
                    matchRangeColor = true;
                    break;
                }
            }
            return matchRangeColor;
        }

        int convertHexToDec(string hexVal) {
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

        vector<int> convertHexColorToRGB(string hexValue){
            int r,g,b;
            string subR = (hexValue.substr(1,2));
            r = convertHexToDec(subR);
            string subG = (hexValue.substr(2,2));
            g = convertHexToDec(subG);
            string subB = (hexValue.substr(5,2));
            b = convertHexToDec(subB);
/*
            cout<<"Sub R "<<subR<<endl;
            cout<<"Sub G "<<subG<<endl;
            cout<<"Sub B "<<subB<<endl;
*/
            return {r,g,b};
        }

        // 2
        void filterColor(vector<vector<int>> pColorList){
            //cout << "Entro a filter color" << endl;
            string color;
            for (Path path : allPathsList){
                //cout << "path: " << path.getColor() << endl;
                color = path.getColor();    // "#01AA25"
                vector<int> rgbValues = convertHexColorToRGB(color);
                if (matchRGB(pColorList,rgbValues)){
                    filteredPathList.push_back(path);
                }
            }
        }

        bool checkProximityBetweenTwoPoints(Path pathInfo, pair<double, double> pPathPoint, pair<double, double> pUserPoint) {
            double distance = sqrt( pow((pUserPoint.first - pPathPoint.first), 2) + pow((pUserPoint.second - pPathPoint.second), 2) );
            //cout << "Distancia calculada: " << distance << endl;
            //cout << "Ratio actual: " << ratio << endl;
            // chequea con el ratio que creó en base a las dimensiones del svg
            if (distance <= ratio){
                // esto es importante para Routing y Generation
                pathInfo.setIntersectionPoint(pUserPoint);
                return true;
            }
            return false;
        }



        // 3
        void selectFinalPathContestants(vector<pair<double, double>> pUserPoints) {
            //cout << "Entro a funcion?" << endl;
            // Greedy: solo chequea con el primer Moveto de cada path
            for (Path p : filteredPathList) {
                //cout << "AQUI EXISTE UN PATH FILTRADO" << endl;
                for(pair<double, double> userPoint : pUserPoints) {
                    //cout << "Intenta encontrar " << userPoint.first << ", " << userPoint.second << " en " << p.getTag() << endl;
                    if (checkProximityBetweenTwoPoints(p, p.getProperPoint(), userPoint)) {
                        //cout << "Eureka!" << endl;
                        selectedPathList.push_back(p);
                        break; // solo tome un punto por match de punto
                    }
                }
            }
        }
};
#endif