#include "../headers/main.hpp"
#include <math.h>
#include <cmath>
#define PI 3.14159265
double numberToCompare = (100 / 100)*1.8;


double radianesAGrados(double radianes)
{
  return radianes * 180 / PI;
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
      yEnd = yStart;
      distance = width - xStart;
    }
    else{
    adjacentAngle = degree;
    oppositeDistance = (width - xStart) *tan((adjacentAngle*PI)/180);
    yEnd = yStart - oppositeDistance;
    xEnd = width;
    distance = sqrt(pow(width - xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree > 45 && degree <=90){
    if(degree == 90){ //linear Movement
      xEnd = xStart;
      yEnd = 0;
      distance = -yStart;
    }
    else{
    adjacentAngle =90 - degree;
    oppositeDistance = yStart * tan(adjacentAngle);
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
    oppositeDistance = (yStart) *tan((adjacentAngle*PI)/180);
    yEnd = 0;
    xEnd = xStart - oppositeDistance;
    distance = - sqrt(pow(yStart,2) + pow(oppositeDistance,2));
  }
  if(degree > 135 && degree <=180){
    if(degree == 180){ //linear Movement
      xEnd = 0;
      yEnd = yStart;
      distance = - xStart;
    }
    else{
    adjacentAngle =180 - degree;
    oppositeDistance = (xStart) * tan((adjacentAngle*PI)/180);
    yEnd = yStart - oppositeDistance;
    xEnd = 0;
    distance = - sqrt(pow(xStart,2) + pow(oppositeDistance,2));
    }
  }
  if(degree == 135){ //Middle 
    distance = - sqrt(pow(xStart,2) + pow(yStart,2)); //Pythagoras
    xEnd = 0;
    yEnd = 0;
  }
  xMovements = distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

vector<double> ThirdQuadrant(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  if(degree>180 && degree < 225){
    adjacentAngle = degree - 180;
    oppositeDistance = (xStart) *tan((adjacentAngle*PI)/180);
    yEnd = yStart + oppositeDistance;
    xEnd = 0;
    distance = -(sqrt(pow(xStart,2) + pow(oppositeDistance,2)));

  }
  if(degree > 225 && degree <=270){
    if(degree == 270){ //linear Movement
      xEnd = xStart;
      yEnd = height;
      distance = height -  yStart ;
    }
    else{
    adjacentAngle =270 - degree;
    oppositeDistance = (height - yStart) * tan((adjacentAngle*PI)/180);
    yEnd = height ;
    xEnd = xStart - oppositeDistance;
    distance = -( sqrt(pow(height - yStart,2) + pow(oppositeDistance,2)));
    cout<<"d "<<distance<<endl;
    }
  }
  if(degree == 225){ //Middle 
    distance = - sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    xEnd = 0;
    yEnd = height;
  }
  xMovements =distance / numFrames;
  return {xMovements,xEnd,yEnd};
}

vector<double> FourthQuadrant(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
  double xStart = path.getIntersectionPoint().first;
  double yStart = path.getIntersectionPoint().second;
  double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
  float pendiente,radian;
  cout<<"degree "<<degree<<endl;
  cout<<"xs "<<xStart<<endl;

  if(degree>270 && degree < 315){
    adjacentAngle = degree - 270;
    cout<<adjacentAngle<<endl;
    oppositeDistance = (height - yStart) *tan((adjacentAngle*PI)/180);
    cout<<oppositeDistance<<endl;
    yEnd = height;
    xEnd = xStart + oppositeDistance;
    distance = sqrt(pow(yStart,2) + pow(oppositeDistance,2));
  }
  if(degree > 315 && degree <=360){
    if(degree == 360){ //linear Movement
      xEnd = width;
      yEnd = yStart;
      oppositeDistance = width - xStart;
    }
    else{
      adjacentAngle =360 - degree;
      oppositeDistance = (width - xStart) * tan((adjacentAngle*PI)/180);
      yEnd = yStart + oppositeDistance;
      xEnd = width;
      distance = sqrt(pow(width-xStart,2) + pow(oppositeDistance,2));
      oppositeDistance = distance;
    }
  }
  if(degree == 315){ //Middle 
    distance = sqrt(pow(width-xStart,2) + pow(height-yStart,2)); //Pythagoras
    oppositeDistance = width-xStart;
    xStart = width;
    yStart = height;
  }
  xMovements = oppositeDistance / numFrames;
  return {xMovements,xEnd,yEnd};
}

 //Obtain the curve points using the de Casterljau's Algorithm
 //It uses linear interpolation between four points
void DeCastreljauAlgortithm(double xStart, double yStart, double xEnd, double yEnd){

}

//Obtains the linear point of the path
//It uses linear interpolation to obtain each pair of points
vector<pair<double, double>> LineMovements(Path path,  vector<double> respuesta, double numFrames){ //Receives also the path to use getters and setters
  vector<pair<double, double>> LinearMovements;
  pair <double, double> MovementPoint;
  double x0 = path.getIntersectionPoint().first;
  double y0 = path.getIntersectionPoint().second;
  double xp = path.getIntersectionPoint().first;
  double x1= respuesta[1],y1=respuesta[2],yp=0,sumMove=respuesta[0];

  while(numFrames > 0 ){

    if(abs(sumMove) < numberToCompare){
      MovementPoint.first = xp;
      MovementPoint.second = yp;
      LinearMovements.push_back(MovementPoint);
      sumMove+=respuesta[0];
    }
    else{
      xp += sumMove;
      yp = y0 + ((y1-y0)/(x1-x0)) * (xp - x0);
      if(xp >= path.getWidth()){
        xp = path.getWidth();
      }
      if(yp >= path.getHeight()){
        yp = path.getHeight();
      }
      if(xp <=0){xp=0;}
      if(yp<=0){yp=0;}
      MovementPoint.first = xp;
      MovementPoint.second = yp;
      //cout<<xp<<" "<<yp<<endl;
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
  if(degree > 90 && degree <=180){respuesta = SecondQuadrant(path,degree,width,heigth,numFrames);}
  if(degree >180 && degree <=270){respuesta = ThirdQuadrant(path,degree,width,heigth,numFrames);}
  if(degree >270 && degree <=360){respuesta = FourthQuadrant(path,degree,width,heigth,numFrames);}
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
void PrintVector(vector<Path> ejemplo){
  for(int i=0;i<ejemplo.size();i++){
    double move = ejemplo[i].getLinearMovement()[1].first;
    cout<<move<<endl;
  }
}
vector<Path> DeclareSolution(vector<Path>, double degree,double width,double heigth,double numFrames){
    pair<double, double> intersecc1;
    pair<double, double> intersecc2;
    vector<pair<double, double>> respuesta;
    for(int i = 0; selectedPathList.size();i++){
        intersecc2 = selectedPathList[i].getIntersectionPoint();

        if(intersecc1 == intersecc2){
          selectedPathList[i].setLinearMovements(respuesta);
          intersecc1 = intersecc2;
        }
        else{
          respuesta = CalculateRoute(selectedPathList[i],degree,width,heigth,numFrames);
          intersecc1 = intersecc2;
        }
    }
    return selectedPathList;
}
void Routing(vector<Path> &selectedPathList, int start, int end, double degree, double width, double heigth,double numFrames){
    if(start < end){
        int mitad = start + (end - start)/2;
        Routing(selectedPathList,start,mitad,degree,width,heigth,numFrames);
        Routing(selectedPathList,mitad+1,end,degree,width,heigth,numFrames);
        CombineRouting(selectedPathList,start,mitad,end,degree,width,heigth,numFrames);
    }

}
