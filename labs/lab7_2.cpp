#include<iostream>
#include<cmath>
using namespace std;

class Shape{
protected:
    int side;
public:
    Shape(){
    }
    Shape(int a){
        this->side=a;
    }
    virtual double plostina()=0;
    virtual void pecati()=0;
    virtual int getType()=0;
};

class Square:public Shape{
public:
    Square(int a):Shape(a){}
    double plostina(){
        return side*side;
    }
    void pecati(){
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }
    int getType(){
        return 1;
    }
};

class Circle:public Shape{
public:
    Circle(int a):Shape(a){}
    double plostina(){
        return 3.14*side*side;
    }
    void pecati(){
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }
    int getType(){
        return 2;
    }
};

class Triangle:public Shape{
public:
    Triangle(int a):Shape(a){}
    double plostina(){
        return (sqrt(3)/4)*side*side;
    }
    void pecati(){
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }
    int getType(){
        return 3;
    }
};

void checkNumTypes(Shape** niza, int n){
    int squareCount=0, circleCount=0, triangleCount=0;
    for(int i=0;i<n;i++){
        switch(niza[i]->getType()){
            case 1:
                squareCount++;
                break;
            case 2:
                circleCount++;
                break;
            case 3:
                triangleCount++;
                break;
        }
    }
    cout<<"Broj na kvadrati vo nizata = "<<squareCount<<endl;
    cout<<"Broj na krugovi vo nizata = "<<circleCount<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<triangleCount<<endl;
}

int main(){
    int n;
    cin >> n;
    //TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape
    Shape** niza = new Shape*[n];
    //TODO: alociraj memorija so golemina n za prethodno navedenata niza
    int classType;
    int side;
    //TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
    for(int i = 0; i < n; ++i){
        cin >> classType;
        cin >> side;
        switch(classType){
            case 1:
                niza[i] = new Square(side);
                break;
            case 2:
                niza[i] = new Circle(side);
                break;
            case 3:
                niza[i] = new Triangle(side);
                break;
        }
    }
    for(int i = 0; i < n; ++i){
        niza[i]->pecati();
    }
    checkNumTypes(niza, n);
    return 0;
}