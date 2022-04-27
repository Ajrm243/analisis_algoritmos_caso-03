#include "../headers/main.hpp"
#include "../headers/Observer.hpp"

/*
    *****Posible acomodo de la clase Seleccion ******
*/

class Seleccion : public Observer {
public:
    Seleccion() {}
    ~Seleccion() {}

    void update(void* procesoSeleccion) {
        // (int*) = castear el puntero void a puntero a int
        // *(int*) = valor del int al que apunta
        int value = *(int*)procesoSeleccion;

        if (value == 0)
            cout << "Recolectando elementos paths" << endl;
        else if (value == 1)
            cout << "Recolectando paths con coincidencias de color" << endl;
        else if (value == 2)
            cout << "Analizando intersecciones de puntos con valores de paths" << endl;
    }
};

extern vector <Path> capturedPathList;
extern vector <Path> selectedPathList;

//Lista de colores dadas por el usuario
list <string> lista_colores = {"red","yellow"};

void recolectarPaths(xml_node<>* node){
    //Reconocer con base en la etiqueta del nodo si los node_element "path" y "g" --> Por el momento
    //Por el momento unicamente se estan imprimiendo hasta definir la estructura que se utilizara para almacenarlas
    
    for (node = node->first_node(); node != NULL; node = node->next_sibling()){
        Path path;
        
        if (node->type() == node_element){
        string etiqueta = node->name();
        path.setEtiqueta(etiqueta);
        string d, color, idPath;
        if (etiqueta == "path"){
            idPath = node->first_attribute("id")->value();
            path.setId(idPath);
            color = node->first_attribute("opacity")->value();
            path.setColor(color);
            d =  node->first_attribute("d")->value();
            path.setPath(d);

            capturedPathList.push_back(path);
        }
        
        }
        
    }
}



void FiltrarColor(){
    int numeroPath;
    string color;
    for (numeroPath=0; numeroPath<capturedPathList.size(); numeroPath++){
        Path path = capturedPathList.at(numeroPath);
        color = path.getColor();
        list<string>::iterator findIter = find(lista_colores.begin(), lista_colores.end(), color);
            if(findIter != lista_colores.end()){
                //Seleccionar path para la siguiente fase de seleccion
                cout<<"Coincidencia encontrada"<<endl; //Hacer el append del elemenot path
                selectedPathList.push_back(path);
            }
    }
}


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