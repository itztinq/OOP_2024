#include<iostream>
#include<cstring>
using namespace std;

class Product{
protected:
    string ime;
    float cena;
public:
    Product(string ime="", const float cena=0){
        this->ime=ime;
        this->cena=cena;
    }
    float getCena(){
        return cena;
    }
};

class Discount{
public:
    virtual float getCena()=0;
    virtual float getCenaPopust()=0;
};

class FoodProduct: public Product, public Discount{
private:
    float kalorii;
public:
    FoodProduct(string ime="", const float cena=0, float kalorii=0)
    : Product(ime, cena){
        this->kalorii=kalorii;
    }
    float getCena(){
        return Product::getCena();
    }
    float getCenaPopust(){
        return getCena()*0.8; //popust 20%
    }
};

class DigitalProduct: public Product, public Discount{
private:
    float golemina;
public:
    DigitalProduct(string ime="", const float cena=0, float golemina=0)
    : Product(ime, cena){
        this->golemina=golemina;
    }
    float getCena(){
        return Product::getCena();
    }
    float getCenaPopust(){
        return getCena()*0.9; //popust 10%
    }
};

float total_discount(Discount **d, int n){
    float cena=0;
    for(int i=0;i<n;i++){
        cena+=d[i]->getCena();
    }
    float popust=0;
    for(int i=0;i<n;i++){
        popust+=d[i]->getCenaPopust();
    }
    return cena-popust;
}

int main(){
    Discount **d=new Discount * [3];
    d[0]=new FoodProduct("Sirenje", 450, 1200);
    d[1]=new FoodProduct("Vino", 800, 250);
    d[2]=new DigitalProduct("WOW", 380, 400);
    cout<<"Razlika: "<<total_discount(d,3)<<endl;
    for(int i=0;i<3;i++){
        delete d[i];
    }
    delete[]d;
    return 0;
}