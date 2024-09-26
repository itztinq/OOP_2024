#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

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

class NoProductFoundException {
private:
    string c;
public:
    NoProductFoundException(const string c="") {
        this->c=c;
    }

    void message() const {
        cout<<"No products from category "<<c<<" were found in the store"<<endl;
    }
};

class Product {
private:
    string name;
    string category;
    int price;
    int availableQuantity;
public:
    Product(string name="", string category="", int price=0, int availableQuantity=0) {
        this->name=name;
        this->category=category;
        this->price=price;
        this->availableQuantity=availableQuantity;
    }

    int totalPrice() const {
        return price*availableQuantity;
    }

    friend ostream &operator<<(ostream &o, const Product &p) {
        o<<p.name<<" ("<<p.category<<") "<<p.availableQuantity<<" x "<<p.price<<" = "<<p.totalPrice()<<endl;
    }

    string &getCategory() {
        return category;
    }

};

class Store {
private:
    Product *products;
    int n;
public:
    Store() {
        n=0;
        products=new Product[n];
    }
    Store(const Store &s) {
        this->n=s.n;
        this->products=new Product[s.n];
        for(int i=0;i<n;i++) {
            this->products[i]=s.products[i];
        }
    }
    ~Store() {
        delete[] products;
    }

    Store &operator+=(const Product &p) {
        Product *tmp=new Product[n+1];
        for(int i=0;i<n;i++) {
            tmp[i]=products[i];
        }
        tmp[n]=p;
        n++;
        delete[] products;
        products=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Store &s) {
        for(int i=0;i<s.n;i++) {
            o<<s.products[i];
        }
        return o;
    }

    Store fromCategory(string &category) {
        int num=0;
        for(int i=0;i<n;i++) {
            if(products[i].getCategory()==category) {
                num++;
            }
        }

        if(num==0) {
            throw NoProductFoundException(category);
        }

        Store categoryProducts;
        for(int i=0;i<n;i++) {
            if(products[i].getCategory()==category) {
                categoryProducts+=products[i];
            }
        }

        return categoryProducts;
    }

};


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    ifstream fin("input.txt");
    if(!fin.is_open()) {
        cout<<"File can not be oppened"<<endl;
        return -1;
    }
    int p, q;
    string n, c;
    while(getline(fin, n)) {
        getline(fin, c);
        fin>>p;
        fin>>q;
        fin.ignore();
        s+=Product(n, c, p, q);
    }

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream fout1("output1.txt");
    fout1<<s;
    fout1.close();

    ofstream fout2("output2.txt");
    try {
        Store categoryStore=s.fromCategory(category);
        fout2<<categoryStore;
    }
    catch (const NoProductFoundException &e) {
        e.message();
    }
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}