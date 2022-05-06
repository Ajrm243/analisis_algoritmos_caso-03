#include <iostream>

using namespace std;

class Path {
  private:
    // Private attribute
    string Id;
    string Etiqueta; 
    string dPath;
    string color;

    //Igual para todos //Sacar valor de SVG y que todos tengan acceso
    string heightSVG;
    string widthSVG;

    pair<double,double> intersectionPoint;
    vector<pair<double,double>> linearMovement;
  public:
    
    Path() { }//Constructor con parametros
    //~Path() {}
    
    // Setter Id
    void setId(string s) {Id = s;}
    // Getter Id
    string getId() {return Id;}

    // Setter Etiqueta
    void setEtiqueta(string s) {Etiqueta = s;}
    // Getter Etiqueta
    string getEtiqueta() {return Etiqueta;}

    // Setter dPath
    void setPath(string s) {dPath = s;}
    // Getter dPath
    string getPath() {return dPath; }

    // Setter Color
    void setColor(string s) {color = s;}
    // Getter Color
    string getColor() {return color;}

    // Setter Height
    void setHeight(string s) {heightSVG = s;}
    // Getter Height
    string getHeight() {return heightSVG;}

    // Setter Width
    void setWidth(string s) {widthSVG = s;}
    // Getter Width
    string getWidth() {return widthSVG;}
    
    void setIntersectionPoint(pair<double,double> intersection){intersectionPoint = intersection;}
    pair<double,double> getIntersectionPoint(){return intersectionPoint;}

    void setLinearMovements(vector<pair<double,double>> Movements){linearMovement = Movements;}
    vector<pair<double,double>> getLinearMovement(){return linearMovement;}
};