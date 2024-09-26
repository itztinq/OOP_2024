#include <iostream>
#include <cstring>
#include<fstream>
using namespace std;

class Product {
private:
    string name;
    string category;
    int price;
    int availableQuantity;
public:
    Product (string name = "", string category = "", int price = 0, int availableQuantity = 0) {
        this->name = name;
        this->category = category;
        this->price = price;
        this->availableQuantity = availableQuantity;
    }

    int totalPrice() const {
        return price * availableQuantity;
    }

    friend ostream &operator<<(ostream &o, const Product &p) {
        return o<<p.name<<" ("<<p.category<<") "<<p.availableQuantity<<" x "<<p.price<<" = "<<p.totalPrice()<<endl;
    }

    string getCategory() const {
        return category;
    }
};

class NoProductFoundException {
private:
    string c;
public:
    NoProductFoundException(string c) {
        this->c = c;
    }
    void message() {
        cout<<"No products from category "<<c<<" were found in the store"<<endl;
    }
};

class Store {
private:
    Product *products;
    int n;
public:
    Store () {
        n = 0;
        products = nullptr;
    }

    Store (Product *products, int n) {
        this->n = n;
        this->products = new Product[n];
        for (int i = 0; i < n; i++) {
            this->products[i] = products[i];
        }
    }

    Store &operator = (const Store &s) {
        if (this != &s) {
            delete [] products;
            this->n = s.n;
            this->products = new Product[s.n];
            for (int i = 0; i < s.n; i++) {
                this->products[i] = s.products[i];
            }
        }
        return *this;
    }

    ~Store () {
        delete [] products;
    }

    Store &operator += (const Product &p) {
        Product *tmp = new Product[n+1];
        for (int i = 0; i < n; i++) {
            tmp[i] = products[i];
        }
        tmp[n++] = p;
        delete [] products;
        products = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Store &s) {
        for (int i = 0; i < s.n; i++) {
            o<<s.products[i];
        }
        return o;
    }

    Store fromCategory (string &category) {
        Store newStore;
        for (int i = 0; i < n; i++) {
            if(products[i].getCategory() == category) {
                newStore += products[i];
            }
        }

        if(newStore.n == 0) {
            throw NoProductFoundException(category);
        }
        return newStore;
    }

};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    ifstream ifs ("input.txt");

    string name, c;
    int price, quantity;

    while (getline(ifs, name)) {
        getline(ifs, c);
        ifs>>price;
        ifs>>quantity;
        ifs.ignore();

        Product p (name, c, price, quantity);
        s+=p;
    }
    ifs.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream ofs1 ("output1.txt");
    ofs1<<s;
    ofs1.close();

    ofstream ofs2 ("output2.txt");
    try{
        Store newStore = s.fromCategory(category);
        ofs2<<newStore;
    } catch(NoProductFoundException &e) {
        e.message();
    }
    ofs2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}