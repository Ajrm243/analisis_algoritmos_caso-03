#include <iostream>
#include <list>
#include <string>
//#include <bits/stdc++.h>
#include <regex>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include "../headers/Path.hpp"

using namespace std;
vector<string> pathDescriptionList;

/*
*************************************************ENRUTAMIENTO*************************************************************
*/



double radiansToDegrees(double radians) {
    return radians * 180 / M_PI;

}
/*
vector<Path> Routing(vector<Path> selected_paths, double width, double height, double degree ){

 return 0;
}
*/


vector<double> FirstQuadrant(Path path, double degree, double width, double height, double numFrames){//From 0 to 90 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  if(degree>=0 && degree < 45){
    if(degree == 0 ){
      xEnd = width;
      yEnd = height - yStart;
      distance = width - xStart;
    }
    else{
    adjacentAngle = degree;
    oppositeDistance = (width - xStart) *tan(adjacentAngle);
    yEnd = height - oppositeDistance;
    xEnd = width;
    distance = sqrt(pow(width - xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree > 45 && degree <=90){
    if(degree == 90){ //linear Movement
      xEnd = xStart;
      yEnd = 0;
      distance = height;
    }
    else{
    adjacentAngle =90 - degree;
    oppositeDistance = height * tan(adjacentAngle);
    yEnd = 0;
    xEnd = xStart + oppositeDistance;
    distance = sqrt(pow(width-xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree == 45){ //Middle 
    distance = sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    xStart = width;
    yStart = 0;
  }
  xMovements = distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

vector<double> SecondQuadrant(Path path, double degree, double width, double height, double numFrames){//From 90 to 180 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  if(degree>90 && degree < 135){
    adjacentAngle = degree - 90;
    oppositeDistance = (yStart) *tan(adjacentAngle);
    yEnd = 0;
    xEnd = xStart - oppositeDistance;
    distance = sqrt(pow(yStart,2) + pow(oppositeDistance,2));
  }
  if(degree > 135 && degree <=180){
    if(degree == 180){ //linear Movement
      xEnd = 0;
      yEnd = yStart;
      distance = xStart;
    }
    else{
    adjacentAngle =180 - degree;
    oppositeDistance = (xStart) * tan(adjacentAngle);
    yEnd = yStart - oppositeDistance;
    xEnd = 0;
    distance = sqrt(pow(xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree == 135){ //Middle 
    distance = sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    xStart = 0;
    yStart = 0;
  }
  xMovements = distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

vector<double> ThirdQuadrant(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  if(degree>270 && degree < 315){
    adjacentAngle = degree - 270;
    oppositeDistance = (height - yStart) *tan(adjacentAngle);
    yEnd = height;
    xEnd = xStart + oppositeDistance;
    distance = sqrt(pow(height-yStart,2) + pow(oppositeDistance,2));
  }
  if(degree > 315 && degree <=360){
    if(degree == 360){ //linear Movement
      xEnd = width;
      yEnd = yStart;
      distance = width - xStart;
    }
    else{
    adjacentAngle =360 - degree;
    oppositeDistance = (width - xStart) * tan(adjacentAngle);
    yEnd = yStart + oppositeDistance;
    xEnd = width;
    distance = sqrt(pow(width-xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree == 315){ //Middle 
    distance = sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    xStart = width;
    yStart = height;
  }
  xMovements = distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

vector<double> FourthQuadrant(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  if(degree>270 && degree < 315){
    adjacentAngle = degree - 270;
    oppositeDistance = (height - yStart) *tan(adjacentAngle);
    yEnd = height;
    xEnd = xStart + oppositeDistance;
    distance = sqrt(pow(height-yStart,2) + pow(oppositeDistance,2));
  }
  if(degree > 315 && degree <=360){
    if(degree == 360){ //linear Movement
      xEnd = width;
      yEnd = yStart;
      distance = width - xStart;
    }
    else{
    adjacentAngle =360 - degree;
    oppositeDistance = (width - xStart) * tan(adjacentAngle);
    yEnd = yStart + oppositeDistance;
    xEnd = width;
    distance = sqrt(pow(width-xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree == 315){ //Middle 
    distance = sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    xStart = width;
    yStart = height;
  }
  xMovements = distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

 //Obtain the curve points using the de Casterljau's Algorithm
 //It uses linear interpolation between four points
void DeCastreljauAlgortithm(double xStart, double yStart, double xEnd, double yEnd){

}

//Obtains the linear point of the path
//It uses linear interpolation to obtain each pair of points
vector<pair<double, double>> LineMovements(Path path,  vector<double> respuesta, double numFrames){ //Receives also the path to use getters and setters
  cout<<"hola"<<endl;
  vector<pair<double, double>> LinearMovements;
  pair <double, double> MovementPoint;
  double x0 = path.getIntersectionPoint().first;
  double y0 = path.getIntersectionPoint().second;
  double xp = path.getIntersectionPoint().first;
  double x1= respuesta[1],y1=respuesta[2],yp=0,sumMove=respuesta[0];
  while(numFrames > 0 ){
    if(sumMove < numberToCompare){
      MovementPoint.first = xp;
      MovementPoint.second = yp;
      LinearMovements.push_back(MovementPoint);
      sumMove+=respuesta[0];
    }
    else{
      xp += sumMove;
      yp = y0 + ((y1-y0)/(x1-x0)) * (xp - x0);
      MovementPoint.first = xp;
      MovementPoint.second = yp;
      cout<<xp<<" "<<yp<<endl;
      LinearMovements.push_back(MovementPoint);

      sumMove = respuesta[0];
    }
  numFrames --;
  }
  return LinearMovements;
}

vector<pair<double, double>> CalculateRoute(Path path, double degree, double width, double heigth,double numFrames){
  vector<double> respuesta;
  vector<pair<double, double>> LinearMovements;
  if (degree >=0 && degree <=90){respuesta = FirstQuadrant(path,degree,width,heigth,numFrames);}
  if(degree > 90 && degree <=180){respuesta = FirstQuadrant(path,degree,width,heigth,numFrames);}
  if(degree >180 && degree <=270){respuesta = FirstQuadrant(path,degree,width,heigth,numFrames);}
  if(degree >270 && degree <=360){respuesta = FirstQuadrant(path,degree,width,heigth,numFrames);}
  LinearMovements = LineMovements(path, respuesta,numFrames);
  return LinearMovements;
}


void CombineRouting(vector<Path> &selectedPathList,int inicio, int mitad, int final, double degree, double width, double heigth,double numFrames){
    int i,j,k;
    int elementosIzq = mitad - inicio + 1;
    int elementosDer = final - mitad;
    vector<pair<double, double>> respuesta;
    vector<Path> izquierda(elementosIzq);
    vector<Path> derecha(elementosDer);

    for(int i = 0; i < elementosIzq; i++){
        izquierda[i] = selectedPathList[inicio+i];
    }
    for(int j = 0; j < elementosDer; j++){
        derecha[j] = selectedPathList[mitad + 1 + j];
    }

    i = 0;
    j = 0;
    k = inicio;
    double intersectionLeft, intersectionRigth;
    while(i < elementosIzq && j < elementosDer){
      intersectionLeft = izquierda[i].getIntersectionPoint().first;
      intersectionRigth = derecha[j].getIntersectionPoint().first;
      if(intersectionLeft <= intersectionRigth){
          if(intersectionLeft == intersectionRigth){
            respuesta = CalculateRoute(izquierda[i],degree,width,heigth,numFrames);
            izquierda[i].setLinearMovements(respuesta);
            derecha[j].setLinearMovements(respuesta);
          }
          selectedPathList[k] = izquierda[i];
          i++;
      }else{
          selectedPathList[k] = derecha[j];
          respuesta = CalculateRoute(derecha[j],degree,width,heigth,numFrames);
          derecha[j].setLinearMovements(respuesta);
          j++;
      }
      k++;
    }

    while(j < elementosDer){
        respuesta = CalculateRoute(derecha[j],degree,width,heigth,numFrames);
        derecha[j].setLinearMovements(respuesta);
        selectedPathList[k] = derecha[j];
        j++;
        k++;
    }

    while(i < elementosIzq){
        respuesta = CalculateRoute(izquierda[i],degree,width,heigth,numFrames);
        izquierda[i].setLinearMovements(respuesta);
        selectedPathList[k] = izquierda[i];
        i++;
        k++;
    }

}

void Routing(vector<Path> &selectedPathList, int start, int end, double degree, double width, double heigth,double numFrames){
    if(start < end){
        int mitad = start + (end - start)/2;
        Routing(selectedPathList,start,mitad,degree,width,heigth,numFrames);
        Routing(selectedPathList,mitad+1,end,degree,width,heigth,numFrames);
        CombineRouting(selectedPathList,start,mitad,end,degree,width,heigth,numFrames);
    }
}

void PrintVector(vector<Path> ejemplo){
  for(int i=0;i<ejemplo.size();i++){
    pair <double,double> interseccion = ejemplo[i].getIntersectionPoint();
    vector<pair<double, double>> Movements = ejemplo[i].getLinearMovement();
    cout<<interseccion.first<<" "<<Movements[1].first<< Movements[2].first<<endl;
  }
}


int main() {


    // example path d list
    pathDescriptionList = {
        "M1945.305,19.063c0.684,0,0.512,0.35,0.512-1.769c-0.689,0.138-0.557,0.203-0.557-0.174c0.665-0.134,0.473-0.112,0.868-0.112c0,2.465-0.171,2.054,0.512,2.054c0,0.352,0.267,0.264-1.335,0.264V19.063z",
        "M1992.138,14.639c1.82,0,2.354,1.722,2.354,3.535c0,1.82-0.541,3.531-2.354,3.531c-1.813,0-2.354-1.71-2.354-3.531C1989.784,16.362,1990.318,14.639,1992.138,14.639z M1992.138,15.369c-1.23,0-1.428,1.576-1.428,2.805c0,1.227,0.199,2.801,1.428,2.801c1.232,0,1.432-1.565,1.432-2.801C1993.57,16.941,1993.373,15.369,1992.138,15.369z",
        "M2035.019,22.756h2.626v-9.065l-2.857,0.573v-1.464c3.412-0.688,2.424-0.573,4.449-0.573v10.529h2.626v1.353h-6.844V22.756z"
    };

    
    return 0;
}