#include<iostream>
#include<cstring>
using namespace std;

class Student {
private:
    char *name;
    int *grades;
    int nGrades;
    int year;
public:
    Student (const char *name="", int year=2000) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->year = year;
        nGrades = 0;
        grades = new int[0];
    }

    Student (const Student &s) {
        this->name = new char[strlen(s.name)+1];
        strcpy(this->name, s.name);
        this->year = s.year;
        this->nGrades = s.nGrades;
        grades = new int[this->nGrades];
        for (int i = 0; i < this->nGrades; i++) {
            grades[i] = s.grades[i];
        }
    }

    Student & operator=(const Student &s) {
        if (this != &s) {
            delete [] name;
            delete [] grades;
            this->name = new char[strlen(s.name)+1];
            strcpy(this->name, s.name);
            this->year = s.year;
            this->nGrades = s.nGrades;
            grades = new int[this->nGrades];
            for (int i = 0; i < this->nGrades; i++) {
                grades[i] = s.grades[i];
            }
        }
        return *this;
    }

    ~Student() {
        delete [] name;
        delete [] grades;
    }

    Student &operator++ () {
        ++year;
        return *this;
    }

    Student &operator++ (int) {
        Student result (*this); //kopija so this objektot
        ++year;
        return result;
    }

    Student &operator+= (int grade) {
        int *tmp = new int[nGrades+1];
        for (int i = 0; i < nGrades; i++) {
            tmp[i] = grades[i];
        }
        tmp[nGrades++] = grade;
        delete [] grades;
        grades = tmp;
        return *this;
    }

    bool operator > (const Student &s) {
        return this->getAverage()>s.getAverage();
    }

    double getAverage() const {
        if(nGrades==0) {
            return 5.0;
        }
        int sum=0;
        for (int i = 0; i < nGrades; i++) {
            sum += grades[i];
        }
        return (double)sum/nGrades;
    }

    friend ostream &operator<< (ostream &o, const Student &s) {
        o<<s.name<<" "<<s.year<<" "<<s.getAverage()<<endl;
        return o;
    }

};

class Faculty {
private:
    Student *students;
    int n;
public:
    Faculty() {
        n = 0;
        students = new Student[n];
    }

    Faculty(const Faculty &f) {
        this->n = f.n;
        this->students = new Student[f.n];
        for (int i = 0; i < f.n; i++) {
            this->students[i] = f.students[i];
        }
    }

    Faculty &operator = (const Faculty &f) {
        if(this != &f) {
            delete [] students;
            this->n = f.n;
            this->students = new Student[f.n];
            for (int i = 0; i < f.n; i++) {
                this->students[i] = f.students[i];
            }
        }
        return *this;
    }

    ~Faculty() {
        delete [] students;
    }

    Faculty &operator += (const Student &s) {
        Student *tmp = new Student[n+1];
        for (int i = 0; i < n; i++) {
            tmp[i] = students[i];
        }
        tmp[n++] = *students;
        delete [] students;
        students = tmp;
        return *this;
    }

    Faculty &operator ++ () {
        for (int i = 0; i < n; i++) {
            ++students[i];
        }
        return *this;
    }

    friend ostream &operator<< (ostream &o, const Faculty &f) {
        for (int i = 0; i < f.n; i++) {
            o<<f.students[i];
        }
        return o;
    }

    void prize() const {
        for (int i = 0; i < n; i++) {
            if(students[i].getAverage() == 10.0) {
                cout<<students[i];
            }
        }
    }

    void highestAverage()const  {
        Student max = students[0];
        for (int i = 0; i < n; i++) {
            if(students[i] > max) {
                max = students[i];
            }
        }
        cout<<max;
    }
};

int main() {
    Student s("Martina", 1);
    //cout<<s;
    s+=6;
    s+=8;
    s+=10;
    Faculty faculty;
    faculty+=s;
    cout<<faculty;

    return 0;
}
