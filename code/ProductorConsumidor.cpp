#include <queue>
#include <iostream>
#include <fstream>
#include <thread> //Permite ejecutar varias tareas (hilos)
#include <unistd.h>

using namespace std;
int opcion;
queue<string> cola;//Declarando la cola de strings

void menu(){
    cout<<"\n\n*******************************************Menu*******************************************\n \
    \n1. Hola Mundo \n2. La casa es roja \n3. Labios color cereza \n4. Finalizar \nSeleccione una opcion: ";
}

void productor(){
    int salida=false;
    while(!salida){
        sleep(1);
        menu();
        cin>>opcion;

        switch(opcion){
            case 1:
                cola.push("Hola Mundo\n");
                break;
            case 2:
                cola.push("La casa es roja\n");
                break;
            case 3:
                cola.push("Labios color cereza\n");
                break;
            case 4:
                cola.push("Salir");
                salida=true;
                break;
            default:
                cout<<"Opcion invalida";
                break;
        }
        cout<<"Producto generado...\n";
    }

}

void consumidor(){
    bool salir=false;
    ofstream file;
    file.open("archivo.txt",ios_base::app | ios_base::in);
    while(!salir){
        sleep(4);
        if(!cola.empty()){
            if(cola.front()!="Salir"){
                file << cola.front();
                cola.pop();
                cout<<"\n\nProcesando producto...\n";
            }
            else{
                break;
            }
        }
        else{
            cout<<"\n\nCola vacia, esperando producto...\nSeleccione una opcion: ";
            //menu();
        }

    }
    file.close();
    cout<<"Archivo cerrado";
}


int main(){
    //Declarando los hilos
    //thread hilo1(productor);

    thread hilo2(consumidor);
    productor();

    //join permite que un hilo espere a que otro termine su ejecución
    //hilo1.join();
    hilo2.join();

}