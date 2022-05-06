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


double radianesAGrados(double radianes)
{
  double PI = 2 * acos(0.0);
  return radianes * 180 / PI;
}
/*
vector<Path> Routing(vector<Path> selected_paths, double width, double height, double degree ){

 return 0;
}
*/


vector<pair<double, double>> FirstQuadrant(double xInicial, double yInicial, double degree,double width, double heigth, double numFrames){ //From 0 to 90 degree angle
  double xFinal, yFinal;//Guardarán los valores del punto final al que se moverá la función 
  double x0= width;
  double y0=yInicial;
  double xMovements, yMovements;

  double distance;

  distance = degree;


  yFinal = yInicial + distance;
  double discountX;

  if (yFinal> heigth){
    discountX = yFinal-heigth;
    yFinal-=discountX;

    xFinal = abs( discountX - x0 );

  }

  else{
    xFinal = width;
  }
  xMovements = (heigth - xInicial);
  xMovements=xMovements/numFrames; //Set value into xMovements

  yMovements = (yFinal-yInicial);
  yMovements = yMovements/numFrames; //Set value into yMovements

  vector<pair<double, double>> linearMovementPoints;
  double xChanges = xInicial;
  double yChanges = yInicial;
  pair <double, double> MovementPoint;
  while(numFrames>0){
    xChanges = xChanges +xMovements;
    yChanges = yChanges +yMovements;
    MovementPoint.first = xChanges;
    MovementPoint.second = yChanges;
    cout<< xChanges <<" , "<<yChanges<<endl;
    linearMovementPoints.push_back(MovementPoint);
    numFrames --;
  }

  return linearMovementPoints;
}
vector<pair<double, double>> SecondQuadrant(double xInicial, double yInicial, double degree,double width, double heigth, double numFrames){//From 90 to 180 degree angle
  double xFinal, yFinal;//Guardarán los valores del punto final al que se moverá la función
  double x90= xInicial;
  double y90=heigth;
  double xMovements, yMovements;

  double distance;

  distance = abs(90-degree);

  xFinal = xInicial + distance;
  double discountY;

  if (xFinal> width){
    discountY = xFinal-width;
    xFinal-=discountY;

    yFinal = abs( discountY - y90 );
  }

  else{
    yFinal = heigth;
  }

  xMovements = (heigth - xInicial);
  xMovements=xMovements/numFrames; //Set value into xMovements

  yMovements = (yFinal-yInicial);
  yMovements = yMovements/numFrames; //Set value into yMovements

  vector<pair<double, double>> linearMovementPoints;
  double xChanges = xInicial;
  double yChanges = yInicial;
  pair <double, double> MovementPoint;
  while(numFrames>0){
    xChanges = xChanges +xMovements;
    yChanges = yChanges +yMovements;
    MovementPoint.first = xChanges;
    MovementPoint.second = yChanges;
    cout<< xChanges <<" , "<<yChanges<<endl;
    linearMovementPoints.push_back(MovementPoint);
    numFrames --;
  }

  return linearMovementPoints;

}
vector<pair<double, double>> ThridQuadrant(double xInicial, double yInicial, double degree,double width, double heigth, double numFrames){//From 180 to 270 degree angle
  double xFinal, yFinal;//Guardarán los valores del punto final al que se moverá la función 
  double x180= width;
  double y180=yInicial;
  double xMovements, yMovements;

  double distance;

  distance = abs(180-degree);


  yFinal = yInicial + distance;
  double discountX;

  if (yFinal> heigth){
    discountX = yFinal-heigth;
    yFinal-=discountX;

    xFinal = abs( discountX - x180 );

  }

  else{
    xFinal = width;
  }
  xMovements = (heigth - xInicial);
  xMovements=xMovements/numFrames; //Set value into xMovements

  yMovements = (yFinal-yInicial);
  yMovements = yMovements/numFrames; //Set value into yMovements

  vector<pair<double, double>> linearMovementPoints;
  double xChanges = xInicial;
  double yChanges = yInicial;
  pair <double, double> MovementPoint;
  while(numFrames>0){
    xChanges = xChanges +xMovements;
    yChanges = yChanges +yMovements;
    MovementPoint.first = xChanges;
    MovementPoint.second = yChanges;
    cout<< xChanges <<" , "<<yChanges<<endl;
    linearMovementPoints.push_back(MovementPoint);
    numFrames --;
  }

  return linearMovementPoints;
}
vector<pair<double, double>> FourthQuadrant(double xInicial, double yInicial, double degree,double width, double heigth, double numFrames){//From 270 to 360 degree angle
  double xFinal, yFinal;//Guardarán los valores del punto final al que se moverá la función
  double x270= xInicial;
  double y270=heigth;
  double xMovements, yMovements;

  double distance;

  distance = abs(270-degree);
  xFinal = xInicial + distance;
  double discountY;

  if (xFinal> width){
    discountY = xFinal-width;
    xFinal-=discountY;

    yFinal = abs( discountY - y270 );
  }

  else{
    yFinal = heigth;
  }

  xMovements = (heigth - xInicial);
  xMovements=xMovements/numFrames; //Set value into xMovements

  yMovements = (yFinal-yInicial);
  yMovements = yMovements/numFrames; //Set value into yMovements

  vector<pair<double, double>> linearMovementPoints;
  double xChanges = xInicial;
  double yChanges = yInicial;
  pair <double, double> MovementPoint;
  while(numFrames>0){
    xChanges = xChanges +xMovements;
    yChanges = yChanges +yMovements;
    MovementPoint.first = xChanges;
    MovementPoint.second = yChanges;
    cout<< xChanges <<" , "<<yChanges<<endl;
    linearMovementPoints.push_back(MovementPoint);
    numFrames --;
  }

  return linearMovementPoints;
}

void LineMovements(double distancia, double xInicial, double yInicial, double xFinal, double yFinal, double numFrames, double xMovements, double yMovements){ //Receives also the path to use getters and setters
  vector<pair<double, double>> linearMovementPoints;
  double xChanges, yChanges;
  pair <double, double> MovementPoint;
  while(numFrames>0){
    xChanges = xChanges +xMovements;
    yChanges = yChanges +yMovements;
    MovementPoint.first = xChanges;
    MovementPoint.second = yChanges;
    
    linearMovementPoints.push_back(MovementPoint);
  }
  //When al the sums are done we set the value for linearMovementPoints

}
void CombineRouting(vector<Path> selectedPathList, int start, int middlePoint, int end ){
//Conquer phase of the algorithm
  vector<Path> temporarySortedPath(end-start +1);

  int copyStart = start;
  int copyMiddlePoint = middlePoint +1;
  int mergeInsertionIndex = 0;

  while(copyStart <= middlePoint && copyMiddlePoint <= end){ //When both sides of the vector still have paths to compare
    pair<double,double> LeftSortIntersection = selectedPathList[copyStart].getIntersectionPoint();
    double xIntersectLeft = LeftSortIntersection.first;

    pair<double,double> rigthSortIntercetion = selectedPathList[copyMiddlePoint].getIntersectionPoint();
    double xIntersectRigth = rigthSortIntercetion.first;

    if(xIntersectLeft <= xIntersectRigth){
      temporarySortedPath[mergeInsertionIndex++] = selectedPathList[copyStart++];
      //copyStart++;
      //mergeInsertionIndex++;
    }
    else{
      temporarySortedPath[mergeInsertionIndex++] = selectedPathList[copyMiddlePoint++];
    }
  }
  //If the right sub-group has run out of values
  // Then add the rest of the values from the left side into the result
  while(copyStart <= middlePoint){
    temporarySortedPath[mergeInsertionIndex] = selectedPathList[copyStart];
    mergeInsertionIndex++, copyStart++;
  }
  //If the left sub-group has run out of values
  //then add the rest of the values from the rigth side into the result
  while(copyMiddlePoint <= end){
    temporarySortedPath[mergeInsertionIndex] = selectedPathList[copyMiddlePoint];
    mergeInsertionIndex++, copyMiddlePoint++;
  }
 //Merge Phase for the algoritm
 //Overwrite the original selectedPathList
  for( int indexMerge = start; indexMerge <= end; indexMerge++ ){
    selectedPathList[indexMerge] = temporarySortedPath[indexMerge - start];
  }

  }
  
//Divide and Conquer approach 
void Routing(vector<Path> selectedPathList, int start, int end){
  if(start <end){
    int middlePoint = (start + end)/2;
    //Divide phase of the algorithm
    Routing(selectedPathList, start, middlePoint); //Analice left side of the vector with the paths
    Routing(selectedPathList,middlePoint +1, end); //Analice right side of the vector with the paths
  
    CombineRouting(selectedPathList,start,middlePoint,end); 
  }
  
}

void PrintVector(vector<Path> ejemplo){
  for(int i=0;i<ejemplo.size();i++){
    pair <double,double> interseccion = ejemplo[i].getIntersectionPoint();
    cout<<interseccion.first<<endl;
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