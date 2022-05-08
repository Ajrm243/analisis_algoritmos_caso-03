#include "../headers/main.hpp"
#include "../headers/Selector.hpp"
#include "../headers/Router.hpp"
#include "../headers/Generator.hpp"

class Processor: public Subject {
    private:
        int observerCount = 0;
        Selector selectorObserver;
        //Router routerObserver;
        //Generator generatorObserver;
    public:
        Processor();
        ~Processor();
        void attach(Observer* pObserver) {
            cout << "stinky virtual method";
        }
        void attachSelector(Selector pSelectorObj) {
            selectorObserver = pSelectorObj;
        }
        void detach(Observer* pObserver) {
            cout << "detach not implemented";
        }
        void notify(void* pPackageInfo) {
            cout << "" << endl;
        }
        void notify(int pPhase, infoPacket pPacket) {
            // hacer algo con los notify
            switch (pPhase)
            {
            case 1:
                // SELECTION
                // envia el paquete como puntero a vacío
                cout << "Llego a Selection" << endl;
                observerList.at(0).update(static_cast<void*>(&pPacket));
                break;
            case 2:
                // ROUTING
                // envia el paquete como puntero a vacío
                cout << "Llego a Routing" << endl;
                //observerList.at(1).update(static_cast<void*>(&pPacket));
                break;
            case 3:
                // GENERATION
                // envia el paquete como puntero a vacío
                //observerList.at(2).update(static_cast<void*>(&pPacket));
                break;
            default:
                // no debería entrar aquí
                break;
            }
        }
};