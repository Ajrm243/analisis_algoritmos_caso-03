#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../headers/main.hpp"
#include "../headers/Selector.hpp"
#include "../headers/Router.hpp"
#include "../headers/Generator.hpp"
class Processor: public Subject {
    private:
        int observerCount = 0;
        Selector* selectorObserver;
        Router* routerObserver;
        //Generator* generatorObserver;
        vector<Path> selectionResult;
        infoPacket* mainPacket;
    public:
        Processor() = default;
        ~Processor(){};
        void attach(Observer* pObserver) {
            cout << "stinky virtual method with obj: " << pObserver << endl;
        }
        void attachSelector(Selector* pSelectorObj) {
            selectorObserver = pSelectorObj;
        }
        void attachRouter(Router* pRouterObj) {
            routerObserver = pRouterObj;
        }
        void detach(Observer* pObserver) {
            cout << "detach not implemented with obj: " << pObserver << endl;
        }
        void notify(void* pPackageInfo) {
            cout << "Notify with void pointer: " << pPackageInfo << endl;
        }
        void notify(int pPhase, infoPacket* pPacket) {
            // hacer algo con los notify
            switch (pPhase)
            {
            case 1:
                // SELECTION
                // envia el paquete como puntero a vacío
                cout << "Llego a Selection" << endl;
                selectionResult = selectorObserver->update(pPacket);
                mainPacket = pPacket;
                break;
            case 2:
                // ROUTING
                // envia el paquete como puntero a vacío
                cout << "Llego a Routing" << endl;
                routerObserver->update(pPacket);
                break;
            case 3:
                // GENERATION
                cout << "Llego a Generation" << endl;
                // envia el paquete como puntero a vacío
                //observerList.at(2).update(static_cast<void*>(&pPacket));
                break;
            default:
                // no debería entrar aquí
                break;
            }
        }
};
#endif