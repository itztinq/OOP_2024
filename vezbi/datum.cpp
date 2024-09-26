#include<iostream>
#include<cstring>
using namespace std;

class Date {
public:
    int day;
    int month;
    int year;
public:
    Date (int day = 1, int month = 1, int year = 1900) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date (const Date &d) {
        this->day = d.day;
        this->month = d.month;
        this->year = d.year;
    }

    ~Date () {}

    void print () {
        cout<<day<<"."<<month<<"."<<year<<endl;
    }

    int compare (Date &date) {
        if(year > date.year) {
            return 1;
        } else if(year < date.year) {
            return -1;
        } else {
            if(month > date.month) {
                return 1;
            } else if(month < date.month) {
                return -1;
            } else {
                if(day > date.day) {
                    return 1;
                } else if(day < date.day) {
                    return -1;
                } else {
                    return 0;
                }
            }
        }
    }
};

class Employee {
public:
    char name[50];
    int salary;
    Date dob;
public:
    Employee () {
        strcpy(this->name,"");
        this->salary = 0;
    }

    Employee (char name[], int salary, Date dob) {
        strcpy(this->name, name);
        this->salary = salary;
        this->dob = dob;
    }

    Employee (const Employee &e) {
        strcpy(this->name, e.name);
        this->salary = e.salary;
        this->dob = e.dob;
    }

    ~Employee () {}

    void print () {
        cout<<name<<" "<<salary<<" ";
        dob.print();
    }

    friend Employee highestPayedEmployee (Employee *employees, int n);
    friend Employee youngestEmployee (Employee *employees, int n);
};

Employee highestPayedEmployee (Employee *employees, int n) {
    Employee max = employees[0];
    for(int i=0;i<n;i++) {
        if(employees[i].salary > max.salary) {
            max = employees[i];
        }
    }
    return max;
}

Employee youngestEmployee (Employee *employees, int n) {
    Employee min = employees[0];
    for(int i=0;i<n;i++) {
        if(employees[i].dob.compare(min.dob) < 0) {
            min = employees[i];
        }
    }
    return min;
}

int main() {
    Employee employees[10]; //10 pati se povikuva default konstruktor
    int n;
    cin>>n;

    for(int i=0;i<n;i++) {
        char name[50];
        int salary;
        int day, month, year;
        cin>>name>>salary>>day>>month>>year;

        Date dob(day,month,year);
        employees[i] = Employee(name,salary,dob);
    }

    highestPayedEmployee(employees, n).print();

    youngestEmployee(employees, n).print();

    return 0;
}