#include <iostream>

using namespace std;

class Path {
  private:
    // Private attribute
    string id;
    string tag;
    string dPath;
    string color;

    //Igual para todos //Sacar valor de SVG y que todos tengan acceso
    double heightSVG;
    double widthSVG;

    pair<double,double> intersectionPoint;
    vector<pair<double,double>> linearMovement;
  public:
    
    Path() { }//Constructor con parametros
    //~Path() {}
    
    // Setter Id
    void setId(string s) {id = s;}
    // Getter Id
    string getId() {return id;}

    // Setter Etiqueta
    void setTag(string s) {tag = s;}
    // Getter Etiqueta
    string getTag() {return tag;}

    // Setter dPath
    void setPath(string s) {dPath = s;}
    // Getter dPath
    string getPath() {return dPath; }

    // Setter Color
    void setColor(string s) {color = s;}
    // Getter Color
    string getColor() {return color;}

    // Setter Height
    void setHeight(string s) {heightSVG = stod(s);}
    // Getter Height
    double getHeight() {return heightSVG;}

    // Setter Width
    void setWidth(string s) {widthSVG = stod(s);}
    // Getter Width
    double getWidth() {return widthSVG;}
    
    void setIntersectionPoint(pair<double,double> intersection){intersectionPoint = intersection;}
    pair<double,double> getIntersectionPoint(){return intersectionPoint;}

    void setLinearMovements(vector<pair<double,double>> Movements){linearMovement = Movements;}
    vector<pair<double,double>> getLinearMovement(){return linearMovement;}
};