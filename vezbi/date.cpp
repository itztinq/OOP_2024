#include<iostream>
#include<cstring>
using namespace std;

class Boy {
private:
    string name;
    string surname;
    int age;
public:
    Boy(string name="", string surname="", int age=0) {
        this->name=name;
        this->surname=surname;
        this->age=age;
    }
    Boy(const Boy &b){
        this->name=b.name;
        this->surname=b.surname;
        this->age=b.age;
    }
    ~Boy(){}

    void print() {
        cout<<"Boy: "<<name<<" "<<surname<<" "<<age<<endl;
    }

    int getAge() {
        return age;
    }
};

class Girl {
private:
    string name;
    string surname;
    int age;
public:
    Girl(string name="", string surname="", int age=0) {
        this->name=name;
        this->surname=surname;
        this->age=age;
    }
    Girl(const Girl &g){
        this->name=g.name;
        this->surname=g.surname;
        this->age=g.age;
    }
    ~Girl(){}

    void print() {
        cout<<"Girl: "<<name<<" "<<surname<<" "<<age<<endl;
    }

    int getAge() {
        return age;
    }
};

class Date {
private:
    Boy b;
    Girl g;
public:
    Date(const Boy b, const Girl g) {
        this->b=b;
        this->g=g;
    }
    ~Date(){}

    void print() {
        cout<<"Date:"<<endl;
        b.print();
        g.print();
    }

    void isCompatible(){
        if(b.getAge() - g.getAge() <= 5) {
            cout<<"They are compatible."<<endl;
        }
        else {
            cout<<"They are not compatible."<<endl;
        }
    }
};

int main() {
    int age;
    string name, surname;

    cout<<"Information for boy: "<<endl;
    cin>>name>>surname>>age;
    Boy b(name, surname, age);
    Boy boy(b);

    cout<<"Information for girl: "<<endl;
    cin>>name>>surname>>age;
    Girl g(name, surname, age);
    Girl girl(g);

    Date d(b, g);
    d.print();
    d.isCompatible();

    return 0;
}