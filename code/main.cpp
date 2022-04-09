#include <iostream>
#include <list>
#include <bits/stdc++.h>
#include "headers/observers.hpp"

//using namespace std;
class Operator : public Subject{

    private:
    std::list<Observer*> ObserverList;

    public:

    void attach(Observer* pObserver) {
        ObserverList.push_back(pObserver);
    }

    void detach(Observer* pObserver) {
        ObserverList.remove(pObserver);
    }

};


class Selector : public Observer {
    
};

int main() {
    return 0;
}