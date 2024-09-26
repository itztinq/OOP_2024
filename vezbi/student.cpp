#include<iostream>
#include<cstring>
using namespace std;

class Student {
private:
    char *name;
    float average;
    int year;
public:
    Student(char *name="", float average=0, int year=0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name,name);
        this->average=average;
        this->year=year;
    }
    Student(const Student &s){
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name,s.name);
        this->average=s.average;
        this->year=s.year;
    }
    ~Student() {
        delete[] name;
    }

    float getAverage(){
        return average;
    }

    Student &operator=(const Student &s){
        if(this!=&s){
            delete[] name;
            this->name = new char[strlen(s.name) + 1];
            strcpy(this->name,s.name);
            this->average=s.average;
            this->year=s.year;
        }
        return *this;
    }

    Student &operator++() {
        year++;
        return *this;
    }

    Student &operator++(int){
        Student s(*this);
        year++;
        return s;
    }

    friend ostream &operator<<(ostream &o, const Student &s) {
        return o<<"Name: "<<s.name<<", Average: "<<s.average<<", Year: "<<s.year<<endl;
    }

    friend bool operator>(const Student &s1, const Student &s2) {
        return (s1.average>s2.average);
    }
};

class Class {
private:
    Student *students;
    int n;
public:
    Class() {
        this->n=n;
        students=new Student[n];
        for(int i=0;i<n;i++){
            this->students[i]=students[i];
        }
    }

    Class(const Class &c) {
        this->n=c.n;
        students=new Student[c.n];
        for(int i=0;i<n;i++){
            this->students[i]=c.students[i];
        }
    }

    ~Class(){
        delete[] students;
    }

    Class &operator+=(Student &s) {
        Student *tmp=new Student[n+1];
        for(int i=0;i<n;i++) {
            tmp[i]=students[i];
        }
        tmp[n++]=s;
        delete[] students;
        students=tmp;
        return *this;
    }

    Class &operator++() {
        for(int i=0;i<n;i++) {
            students[i]++;
        }
        return *this;
    }

    Class &operator++(int) {
        Class c(*this);
        for(int i=0;i<n;i++) {
            students[i]++;
        }
        return c;
    }

    friend ostream &operator<<(ostream &o, const Class &c) {
        for(int i=0;i<c.n;i++) {
            o<<c.students[i]<<endl;
        }
        return o;
    }

    void reward(){
        for(int i=0;i<n;i++) {
            if(students->getAverage()==10.0) {
                cout<<students[i];
            }
        }
    }

    void bestAverage() {
        Student tmp=students[0];
        for(int i=0;i<n;i++) {
            if(students[i]>tmp){
                tmp=students[i];
            }
        }
        cout<<"the best average in the class is: "<<tmp.getAverage()<<endl;
    }
};

int main() {
    Student s1("Ana Ankovska", 10, 3);
    Student s2("Petar Petreski", 7.5, 3);
    Student s3("Nina Ninovska", 9.5, 3);

    Class c;
    c+=s1;
    c+=s2;
    c+=s3;
    cout<<c;

    cout<<"Rewarded: "<<endl;
    c.reward();
    cout<<endl;
    c.bestAverage();
    cout<<endl;

    s2++;
    cout<<c;
    cout<<endl;
    c++;
    cout<<c;

    return 0;
}