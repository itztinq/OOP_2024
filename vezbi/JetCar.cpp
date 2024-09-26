#include<iostream>
#include<cstring>
using namespace std;

//dijamant problem

class Vehicle {
protected:
    int acceleration;
public:
    explicit Vehicle(int acceleration=1) {
        cout<<"VEHICLE CONSTRUCTOR"<<endl;
        this->acceleration=acceleration;
    }
    ~Vehicle() {
        cout<<"VEHICLE DESTRUCTOR"<<endl;
    }

    virtual void accelerate() {
        acceleration+=1;
        cout<<"VEHICLE ACCELERATTING"<<endl;
    }

    virtual int getAcceleration() const {
        return acceleration;
    }
};

class Car : virtual public Vehicle {
public:
    explicit Car(int acceleration=10) : Vehicle(acceleration) {
        cout<<"CAR CONSTRUCTOR"<<endl;
    }
    ~Car() {
        cout<<"CAR DESTRUCTOR"<<endl;
    }

    void accelerate() override {
        acceleration+=2;
        cout<<"CAR ACCELERATTING"<<endl;
    }
};

class Jet : virtual public Vehicle {
public:
    explicit Jet(int acceleration=100) : Vehicle(acceleration) {
        cout<<"JET CONSTRUCTOR"<<endl;
    }
    ~Jet() {
        cout<<"JET DESTRUCTOR"<<endl;
    }

    void accelerate() override {
        acceleration+=50;
        cout<<"JET ACCELERATTING"<<endl;
    }
};

class JetCar : public Jet, public Car {
public:
    explicit JetCar(int a) {
        this->acceleration=a;
        cout<<"JETCAR CONSTRUCTOR"<<endl;
    }

    ~JetCar() {
        cout<<"JETCAR DESTRUCTOR"<<endl;
    }

    void accelerate() override {
        acceleration+=25;
        cout<<"JETCAR ACCELERATTING"<<endl;
    }
};

int main() {
    Vehicle **vehicles=new Vehicle *[4];
    vehicles[0]=new Vehicle(1);
    vehicles[1]=new Car(5);
    vehicles[2]=new Jet(100);
    vehicles[3]=new JetCar(25);

    for(int i=0;i<3;i++) {
        cout<<vehicles[i]->getAcceleration()<<endl;
        vehicles[i]->accelerate();
        cout<<vehicles[i]->getAcceleration()<<endl;
    }
    return 0;
}