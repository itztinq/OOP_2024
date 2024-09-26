#include<iostream>
#include<cstring>
using namespace std;

class Animal {
protected:
    string name;
    int age;
public:
    Animal(string name="", int age=0) {
        this->name=name;
        this->age=age;
    }

    virtual void makeSound()=0;
};

class Cat : public Animal {
public:
    Cat(string name="", int age=0) : Animal(name, age) {}

    void makeSound() {
        cout<<"The cat with name "<<name<<" and age "<<age<<" makes the sound MJAUUU"<<endl;
    }
};

class Dog : public Animal {
public:
    Dog(string name="", int age=0) : Animal(name, age) {}

    void makeSound() {
        cout<<"The dog with name "<<name<<" and age "<<age<<" makes the sound AFF-AFF"<<endl;
    }
};

void printStatistics(Animal **animals, int n) {
    int cats=0;
    int dogs=0;
    for(int i=0;i<n;i++) {
        Cat *castedCat=dynamic_cast<Cat*>(animals[i]);
        if(castedCat) {
            cats++;
        } else {
            dogs++;
        }
    }
    cout<<"Cats: "<<cats<<endl;
    cout<<"Dogs: "<<dogs<<endl;
}

int main() {
    int n;
    cin>>n;
    Animal **animals = new Animal *[n];

    for(int i=0; i<n; i++) {
        int type, age;
        string name;
        cin>>type>>name>>age;
        if(type == 1) {
            animals[i] = new Cat(name, age);
        } else {
            animals[i] = new Dog(name, age);
        }
    }

    for(int i=0; i<n; i++) {
        animals[i]->makeSound();
    }
    printStatistics(animals, n);
    return 0;
}