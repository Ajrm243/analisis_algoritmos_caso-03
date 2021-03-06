class Observer {
    public:
        Observer(){};
        virtual ~Observer(){};
        virtual void update(void* element) = 0;
};

class Subject {
    public:
        Subject(){};
        virtual ~Subject(){};
        virtual void attach(Observer* observer) = 0;
        virtual void detach(Observer* observer) = 0;
        virtual void notify(void* element) = 0;
};