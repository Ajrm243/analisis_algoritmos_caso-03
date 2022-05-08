#ifndef ROUTER_H
#define ROUTER_H
#ifndef PI
#define PI 3.1459
#endif
#include "../headers/main.hpp"
#include "../headers/Processor.hpp"
#ifndef MINIMUM_FRAME_MOVEMENT
#define MINIMUM_FRAME_MOVEMENT 1.8
#endif

double radianesAGrados(double radianes)
{
  return radianes * 180 / PI;
}
/*
vector<Path> Routing(vector<Path> selected_paths, double width, double height, double degree ){

 return 0;
}
*/
class Router : public Observer {
    private:
        double cHeight;
        double cWidth;
        double movementPerFrame;
    public:
        Router(){};
        ~Router(){};
        void update(void* pObj) {
            infoPacket* castedPacket = (static_cast<infoPacket*>(pObj));
        }
        void update(infoPacket* pUserPacket) {
            cout << "Llega en el Router Class" << endl;
            cout << "Dimensiones: (" << pUserPacket->canvasWidth << ", " << pUserPacket->canvasHeight << ")" << endl;
            cHeight = pUserPacket->canvasHeight;
            cWidth = pUserPacket->canvasWidth;
            movementPerFrame = (cWidth / cHeight) * MINIMUM_FRAME_MOVEMENT;
            cout << "minimumMovementPerFrame: " << movementPerFrame << endl;
            infoPacket workingPacket = *pUserPacket;
            routing(workingPacket.pathListMod, 0, workingPacket.pathListMod.size()-1, workingPacket.angleMod, workingPacket.canvasWidth, workingPacket.canvasHeight, workingPacket.frameMod);
            for (Path p : pUserPacket->pathListMod) {
                cout << "Movement at frame 0: (";
                cout << p.getLinearMovement().at(0).first << ", " << p.getLinearMovement().at(0).second << ")" << endl;
            }
        }
        vector<double> firstQuadrantMovementCalculation(Path path, double degree, double width, double height, double numFrames){//From 0 to 90 degree angle
            double xStart = path.getIntersectionPoint().first;
            double yStart = path.getIntersectionPoint().second;
            double distance, oppositeDistance, xMovements, xEnd,yEnd,adjacentAngle;
            if(degree>=0 && degree < 45){
                if(degree == 0 ){
                    xEnd = width;
                    yEnd = yStart;
                    distance = width - xStart;
                } else{
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
                } else{
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
        vector<double> secondQuadrantMovementCalculation(Path path, double degree, double width, double height, double numFrames){//From 90 to 180 degree angle
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
                } else {
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
        vector<double> thirdQuadrantMovementCalculation(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
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
                } else{
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
        vector<double> fourthQuadrantMovementCalculation(Path path, double degree, double width, double height, double numFrames){//From 270 to 360 degree angle
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


        //Obtains the linear point of the path
        //It uses linear interpolation to obtain each pair of points
        vector<pair<double, double>> lineMovements(Path path, vector<double> respuesta, double numFrames){ //Receives also the path to use getters and setters
            vector<pair<double, double>> LinearMovements;
            pair <double, double> MovementPoint;
            double x0 = path.getIntersectionPoint().first;
            double y0 = path.getIntersectionPoint().second;
            double xp = path.getIntersectionPoint().first;
            double x1 = respuesta[1],y1=respuesta[2],yp=0,sumMove=respuesta[0];
            cout << "Sum move: " << sumMove << endl;
            while(numFrames > 0 ){
                if(abs(sumMove) < movementPerFrame){  // cambiar por el double que sea atributo de la clase que se modifica multiplicando por esta constante
                    MovementPoint.first = xp;
                    MovementPoint.second = yp;
                    LinearMovements.push_back(MovementPoint);
                    sumMove+=respuesta[0];
                } else{
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

        vector<pair<double, double>> calculateRoute(Path path, double degree, double width, double heigth,double numFrames){
            cout << "Llega a calculateRoute" << endl;
            vector<double> respuesta;
            vector<pair<double, double>> LinearMovements;
            if (degree >=0 && degree <=90){respuesta = firstQuadrantMovementCalculation(path,degree,width,heigth,numFrames);}
            if(degree > 90 && degree <=180){respuesta = secondQuadrantMovementCalculation(path,degree,width,heigth,numFrames);}
            if(degree >180 && degree <=270){respuesta = thirdQuadrantMovementCalculation(path,degree,width,heigth,numFrames);}
            if(degree >270 && degree <=360){respuesta = fourthQuadrantMovementCalculation(path,degree,width,heigth,numFrames);}
            LinearMovements = lineMovements(path, respuesta,numFrames);
            return LinearMovements;
        }
        void combineRouting(vector<Path> &selectedPathList,int inicio, int mitad, int final, double degree, double width, double heigth,double numFrames){
            cout << "Entra a combineRouting" << endl;
            int leftIndex,rigthIndex,k;
            int leftElements = mitad - inicio + 1;
            int rightElements = final - mitad;
            vector<pair<double, double>> respuesta;
            vector<Path> leftHalf(leftElements);
            vector<Path> rightHalf(rightElements);
            for(int i = 0; i < leftElements; i++){
                leftHalf[i] = selectedPathList[inicio+i];
            }
            for(int j = 0; j < rightElements; j++){
                rightHalf[j] = selectedPathList[mitad + 1 + j];
            }
            leftIndex = 0;
            rigthIndex = 0;
            k = inicio;
            double intersectionLeft, intersectionRigth;
            while(leftIndex < leftElements && rigthIndex < rightElements){
                intersectionLeft = leftHalf[leftIndex].getIntersectionPoint().first;
                intersectionRigth = rightHalf[rigthIndex].getIntersectionPoint().first;
                if(intersectionLeft <= intersectionRigth){
                    cout << "Antes de llamada a calculateRoute" << endl;
                    respuesta = calculateRoute(leftHalf[leftIndex],degree,width,heigth,numFrames);
                    if(intersectionLeft == intersectionRigth){
                    leftHalf[leftIndex].setLinearMovements(respuesta);
                    rightHalf[rigthIndex].setLinearMovements(respuesta);
                    }
                    selectedPathList[k] = leftHalf[leftIndex];
                    selectedPathList[k].setLinearMovements(respuesta);
                    leftIndex++;
                }else{
                    cout << "Antes de llamada a calculateRoute" << endl;
                    respuesta = calculateRoute(rightHalf[rigthIndex],degree,width,heigth,numFrames);
                    rightHalf[rigthIndex].setLinearMovements(respuesta);
                    selectedPathList[k] = rightHalf[rigthIndex];
                    selectedPathList[k].setLinearMovements(respuesta);

                    rigthIndex++;
                }
                k++;
            }

            while(rigthIndex < rightElements){
                respuesta = calculateRoute(rightHalf[rigthIndex],degree,width,heigth,numFrames);
                rightHalf[rigthIndex].setLinearMovements(respuesta);
                selectedPathList[k] = rightHalf[rigthIndex];
                selectedPathList[k].setLinearMovements(respuesta);
                rigthIndex++;
                k++;
            }

            while(leftIndex < leftElements){
                respuesta = calculateRoute(leftHalf[leftIndex],degree,width,heigth,numFrames);
                leftHalf[leftIndex].setLinearMovements(respuesta);
                selectedPathList[k] = leftHalf[leftIndex];
                selectedPathList[k].setLinearMovements(respuesta);
                leftIndex++;
                k++;
            }

            }
        void printVector(vector<Path> ejemplo){
            for(int i=0;i<ejemplo.size();i++){
                double move = ejemplo[i].getLinearMovement()[1].first;
                cout<<move<<endl;
            }
        }
        vector<Path> DeclareSolution(vector<Path> pSelectedPathList, double pDegree,double pWidth,double pHeigth,double pNumFrames){
            pair<double, double> intersecc1;
            pair<double, double> intersecc2;
            vector<pair<double, double>> respuesta;
            for(int i = 0; pSelectedPathList.size();i++){
                intersecc2 = pSelectedPathList[i].getIntersectionPoint();
                if(intersecc1 == intersecc2){
                    pSelectedPathList[i].setLinearMovements(respuesta);
                    intersecc1 = intersecc2;
                }
                else{
                    respuesta = calculateRoute(pSelectedPathList[i],pDegree,pWidth,pHeigth,pNumFrames);
                    intersecc1 = intersecc2;
                }
            }
                return pSelectedPathList;
            }
        void routing(vector<Path>& selectedPathList, int start, int end, double degree, double width, double heigth, double numFrames){
            cout << "Entra routing" << endl;
            if(start < end){
                int mitad = start + (end - start)/2;
                routing(selectedPathList,start,mitad,degree,width,heigth,numFrames);
                routing(selectedPathList,mitad+1,end,degree,width,heigth,numFrames);
                combineRouting(selectedPathList,start,mitad,end,degree,width,heigth,numFrames);
            }
        }
};


#endif