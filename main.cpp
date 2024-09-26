//ZADACHA 1
/*#include <iostream>
#include <cstring>
using namespace std;
class Discount{
public:
    static float euro;
    static float dollar;
    virtual float discount_price()=0;
    virtual float price()=0;
    virtual void print_rule()=0;
};
float Discount::euro=61.5;
float Discount::dollar=55;

class NegativeValueException{ //klasa za iskluchoci, najcesto ima edna podatochna chlenka najchesto nekoja poraka/tekst
private:
    string text;
public:
    NegativeValueException(string text){
        this->text=text;
    }
    void print(){
        cout<<text<<endl;
    }
};

class Product{
protected:
    string name;
    float price;
public:
    Product(string name="", float price=0){
        this->name=name;
        this->price=price;
    }
    float getPrice(){
        return price;
    }
    void print(){
        cout<<"Produkt: "<<name<<" "<<price<<endl;
    }
    void changePrice(float new_price){
        if(new_price<0){
            throw NegativeValueException("Vnesena e negativna vrednost za cena!"); //frlanje iskluchok
        }else{
            this->price=new_price;
        }
    }
};

class FoodProduct: public Product, public Discount{
private:
    float callories;
public:
    FoodProduct(string name="", float price=0, float callories=0)
    :Product(name,price){
        this->callories=callories;
    }
    float discount_price(){
        return getPrice();
    }
    float price(){
        return getPrice();
    }
    void print_rule(){
        cout<<"Nema popust za proizvodite od tip na hrana"<<endl;
    }
};

class Drinks: public Product, public Discount{
private:
    bool alcoholic;
    string brand;
public:
    Drinks(string name="", float price=0, bool alcoholic=1, string brand="")
    :Product(name,price){
        this->alcoholic=alcoholic;
        this->brand=brand;
    }
    float discount_price(){
        if(alcoholic && (getPrice()/Discount::euro)>20){
            return getPrice()*0.95;
        }
        if(!alcoholic && (brand=="Coca-Cola")){
            return getPrice()*0.9;
        }
        return getPrice();
    }
    float price(){
        return getPrice();
    }
    void print_rule(){
        cout<<"A&&>20->5%, !A&&Coca-Cola->10%"<<endl;
    }
};

class Cosmetics: public Product, public Discount{
private:
    float weight;
public:
    Cosmetics(string name="", float price=0, float weight=0)
    :Product(name,price){
        this->weight=weight;
    }
    float discount_price(){
        if(getPrice()/Discount::dollar>20){
            return getPrice()*0.86;
        }
        if(getPrice()/Discount::euro>5){
            return getPrice()*0.88;
        }
        return getPrice();
    }
    float price(){
        return getPrice();
    }
    void print_rule(){
        cout<<">5E->12%, >$20->14%"<<endl;
    }
};

int main(){
    int n;
    cin>>n;
    Discount **d = new Discount * [n];
    int type;
    //string name, brand;
    //bool alcoholic;
    //float price, callories, weight;
    for(int i=0;i<n;i++){
        cin>>type;
        if(type==1){//FoodProduct
            //cin>>name>>price>>callories;
            d[i] = new FoodProduct("Food", 50, 200);
        }else if(type==2){
            d[i] = new Drinks("Drinks", 500, 1);
        }else{
            d[i] = new Cosmetics("Cosmetics", 200,300);
        }
    }
    float new_price;
    for(int i=0;i<n;i++){
        Cosmetics *c = dynamic_cast<Cosmetics *>(d[i]);
        if(c){
            c->print();
            cin>>new_price;
            try {
                c->changePrice(new_price);//try blokot se postavuva okolu funkcijata koja frla iskluchok
            }
            catch (NegativeValueException i){ //go lovime iskluchokot
                i.print(); //ja pechati porakata text
            }
        }
    }
}*/



//ZADACHA 2
/*#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

int main(){
    ifstream fin("C:\\Users\\tinas\\CLionProjects\\OOP-23-24\\Primer.txt");
    if(!fin.is_open()){
        cout<<"Datotekata ne e otvorena"<<endl;
        return -1;
    }
    int samoglaski_red=0, samoglaski_datoteka=0, n_redovi=0;
    char c;
    while(fin.get(c)){ //kje vrti se dodeka ima znaci vo datotekata
        c=tolower(c);
        if(c =='a' || c=='e' || c=='i' || c=='o' || c=='u'){
            samoglaski_datoteka++;
            samoglaski_red++;
        }
        if(c == '\n'){
            if(samoglaski_red>=10){
                n_redovi++;
            }
            samoglaski_red=0;
        }
    }
    cout<<samoglaski_datoteka<<endl;
    cout<<samoglaski_red<<endl;
}*/