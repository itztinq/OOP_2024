#include<iostream>
#include<cstring>
using namespace std;

enum typeC {
    standard, loyal, vip
};

int MAX = 100;

class Customer {
private:
    char name[MAX];
    char email[MAX];
    typeC tc;
    static int baseDiscount; //vo procenti
    const static int discount; //vo procenti
    int nProducts;
public:
    Customer (char *name = "", char *email = "", typeC tc = standard, int nProducts = 0) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->tc = tc;
        this->nProducts = nProducts;
    }

    int getApplocableDiscount() const {
        if(tc == standard) {
            return 0;
        } else if(tc == loyal) {
            return baseDiscount;
        } else if(tc == vip) {
            return baseDiscount + discount;
        }
        return 0;
    }

    friend ostream &operator << (ostream &o, const Customer &c) {
        o<<c.name<<endl<<c.email<<endl<<c.nProducts<<endl<<c.tc<<" ";
        switch (c.tc) {
            case standard: o<<"Standard"<<endl; break;
            case loyal: o<<"Loyal"<<endl; break;
            case vip: o<<"VIP"<<endl; break;
        }
        o<<c.getApplocableDiscount()<<endl;
        return o;
    }

    static void setDiscount1 (int newDiscount) {
        baseDiscount = newDiscount;
    }

    char *getName () {
        return name;
    }

    char *getEmail() {
        return email;
    }

    int getProducts() const {
        return nProducts;
    }

    typeC getType() const {
        return tc;
    }

    static int getBaseDiscount () {
        return baseDiscount;
    }

    static int getDiscount () {
        return discount;
    }
};

int Customer::baseDiscount = 10;
const int Customer::discount = 20;

class UserExistsException {
public:
    void message() {
        cout<<"The user already exists in the list"<<endl;
    }
};

class FINKI_bookstore {
private:
    Customer *customers;
    int numberOfCustomers;
public:
    FINKI_bookstore (Customer *customers = nullptr, int numberOfCustomers = 0) {
        this->numberOfCustomers = numberOfCustomers;
        this->customers = new Customer[numberOfCustomers];
        for (int i = 0; i < numberOfCustomers; i++) {
            this->customers[i] = customers[i];
        }
    }

    FINKI_bookstore (const FINKI_bookstore &fb) {
        this->numberOfCustomers = fb.numberOfCustomers;
        customers = new Customer[fb.numberOfCustomers+1];
        for (int i = 0; i < numberOfCustomers; i++) {
            this->customers[i] = fb.customers[i];
        }
    }

    FINKI_bookstore &operator = (const FINKI_bookstore &fb) {
        if (this != &fb) {
            delete[] customers;
            this->numberOfCustomers = fb.numberOfCustomers;
            customers = new Customer[fb.numberOfCustomers+1];
            for (int i = 0; i < numberOfCustomers; i++) {
                this->customers[i] = fb.customers[i];
            }
        }
        return *this;
    }

    void setCustomers (Customer *c, int n) {
        delete[] customers;
        numberOfCustomers = n;
        customers = new Customer[n];
        for (int i = 0; i < n; i++) {
            customers[i] = c[i];
        }
        numberOfCustomers = n;
    }

    ~FINKI_bookstore() {
        delete[] customers;
    }

    FINKI_bookstore &operator += (Customer &c) {
        for(int i = 0; i < numberOfCustomers; i++) {
            if(strcmp(customers[i].getEmail(), c.getEmail()) == 0) {
                throw UserExistsException();
            }
        }

        Customer *newCustomers = new Customer[numberOfCustomers+1];
        for (int i = 0; i < numberOfCustomers; i++) {
            newCustomers[i] = customers[i];
        }
        newCustomers[numberOfCustomers++] = c;
        delete[] customers;
        customers = newCustomers;
        return *this;
    }

    void update() {
        for (int i = 0; i < numberOfCustomers; i++) {
            if(customers[i].getProducts() > 10 && customers[i].getType() == loyal) {
                customers[i] = Customer (customers[i].getName(), customers[i].getEmail(), vip, customers[i].getProducts());
            }
            else if(customers[i].getProducts() > 5 && customers[i].getType() == standard) {
                customers[i] = Customer (customers[i].getName(), customers[i].getEmail(), loyal, customers[i].getProducts());
            }
        }
    }

    friend ostream &operator << (ostream &o, const FINKI_bookstore &fb) {
        for (int i = 0; i < fb.numberOfCustomers; i++) {
            o<<fb.customers[i]<<endl;
        }
        return o;
    }
};

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);

    try {
        fc+=c;
        cout << fc;
    } catch(UserExistsException &e) {
        e.message();
    }
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;

      Customer c(name, email, (typeC) tC, numProducts);
    try {
        fc+=c;
        cout << fc;
    } catch (UserExistsException &e) {
        e.message();
    }
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}