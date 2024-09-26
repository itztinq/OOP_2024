#include<iostream>
#include<cstring>
using namespace std;

class Product {
protected:
    string name;
    int price;
public:
    Product(string name="", int price=0) {
        this->name=name;
        this->price=price;
    }
};

class Discount {
public:
    virtual int getPrice()=0;
    virtual int getPriceWithDiscount()=0;

    int getDiscount() {
        return getPrice()-getPriceWithDiscount();
    }

    virtual void print()=0;
};

class FoodProduct : public Product, public Discount {
private:
    int calories;
public:
    FoodProduct(string name="", int price=0, int calories=0)
    : Product(name, price) {
        this->calories=calories;
    }

    int getPrice() {
        return price;
    }

    int getPriceWithDiscount() {
        if(calories>1000) {
            return int(price*0.8); //20% discount
        } else if(calories>500) {
            return int(price*0.9); //10% discount
        } else {
            return price;
        }
    }

    void print() {
        cout<<"Food product: "<<name<<" "<<price<<" "<<calories<<" "<<"("<<getPriceWithDiscount()<<")"<<endl;
    }

};

class DigitalProduct : public Product, public Discount {
private:
     float size; //MB
public:
    DigitalProduct(string name="", int price=0, float size=0.0)
    : Product(name, price) {
        this->size=size;
    }

    int getPrice() override {
        return price;
    }

    int getPriceWithDiscount() override {
        double discountCeof=1.0;

        if(size<5*1024) {
            discountCeof-=0.2;
        } else if(size<10*1024) {
            discountCeof-=0.1;
        }

        if(name.find("HP")!=-1) {
            discountCeof-=0.5;
        }
        return int(price*discountCeof);
    }

    void print() override {
        cout<<"Digital product: "<<name<<" "<<price<<" "<<size<<"MB "<<"("<<getPriceWithDiscount()<<")"<<endl;
    }
};

int totalDiscount(Discount **products, int n) {
    int sum=0;
    for(int i=0;i<n;i++) {
        sum+=(products[i]->getDiscount());
    }
    return sum;
}

int main() {
    int n;
    cin>>n;
    Discount **products=new Discount *[n];

    for(int i=0;i<n;i++) {
        int type;
        string name;
        int price;
        cin>>type>>name>>price;
        if(type==1) {
            int calories;
            cin>>calories;
            products[i]=new FoodProduct(name, price, calories);
        } else {
            int size;
            cin>>size;
            products[i]=new DigitalProduct(name, price, size);
        }
    }

    for(int i=0;i<n;i++) {
        products[i]->print();
    }

    cout<<"TOTAL DISCOUNT: "<<totalDiscount(products,n);
    return 0;
}