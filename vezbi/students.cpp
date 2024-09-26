#include<iostream>
#include<cstring>
using namespace std;

class Student {
private:
    string name;
    string index;
    double average;
    static int totalStudents;
    static double averageSum;
public:
    Student(string name="", string index="", double average=0) {
        this->name=name;
        this->index=index;
        this->average=average;
        totalStudents++;
        averageSum+=average;
    }
    void print() {
        cout<<index<<" "<<name<<" "<<average<<endl;
    }
    static double averageTotal(){
        return averageSum/totalStudents;
    }

};

int Student::totalStudents=0;
double Student::averageSum=0.0;

int main() {
    int n;
    cout<<"Number of students: ";
    cin>>n;
    Student s[n];
    string name, index;
    double average;

    for(int i=0;i<n;i++) {
        cin>>name>>index>>average;
        s[i]=Student(name, index, average);
    }

    for(int i=0;i<n;i++) {
        s[i].print();
    }

    cout<<"Total average: "<<Student::averageTotal()<<endl;
    return 0;
}