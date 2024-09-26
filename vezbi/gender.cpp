#include<iostream>
#include<cstring>
using namespace std;

enum GENDER {
    MALE,  //0
    FEMALE //1
};

class Person {
protected:
    string name;
    int age;
    GENDER gender;
public:
    Person(string name="", int age=0, GENDER gender=MALE) {
        this->name=name;
        this->age=age;
        this->gender=gender;
    }

    friend ostream &operator<<(ostream &o, const Person &p) {
        o<<"name: "<<p.name<<" age: "<<p.age<<" gender: "<<(p.gender==MALE? "MALE" : "FEMALE");
        return o;
    }
};

class Student : public Person {
private:
    int index;
    int year;
    double GPA;
public:
    Student(string name="", int age=0, GENDER gender=MALE, int index=0, int year=0, double GPA=0.0)
    : Person(name, age, gender) {
        this->index=index;
        this->year=year;
        this->GPA=GPA;
    }

    friend  ostream &operator<<(ostream &o, const Student &s) {
        o<<static_cast<const Person &>(s)<<" index: "<<s.index<<" year: "<<s.year<<" GPA: "<<s.GPA;
        return o;
    }
};

int main() {
    Person p("Lana", 22, FEMALE);
    cout<<p<<endl;

    Student s("Lana", 19, FEMALE, 122457, 1, 9.5);
    cout<<s<<endl;

    Person second=s;
    cout<<second<<endl;
    return 0;
}