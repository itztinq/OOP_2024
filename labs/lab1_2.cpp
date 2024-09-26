#include<iostream>
using namespace std;

struct Engine{
    int konjskaSila;
    int vrtezenMoment;
};

struct Car{
    char ime[50];
    int godina;
    Engine motor;
};

void print(Car car){
    cout<<"Manufacturer: "<<car.ime<<endl;
    cout<<"Horsepower: "<<car.motor.konjskaSila<<endl;
    cout<<"Torque: "<<car.motor.vrtezenMoment<<endl;
}

void read(Car car[],int n){
    for(int i=0;i<n;i++){
        cin>>car[i].ime>>car[i].godina>>car[i].motor.konjskaSila>>car[i].motor.vrtezenMoment;
    }
}

void printCars(Car car[],int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(car[i].motor.konjskaSila>car[j].motor.konjskaSila){
                swap(car[i],car[j]);
            }
        }
    }
    if(car[0].motor.vrtezenMoment>car[1].motor.vrtezenMoment){
        print(car[0]);
    }else{
        print(car[1]);
    }
}

int main(){
    int n;
    cin>>n;
    Car cars[100];
    read(cars,n);
    printCars(cars,n);
    return 0;
}