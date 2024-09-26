#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class StudentFailedException {
private:
    string id;
public:
    StudentFailedException(string id="") {
        this->id=id;
    }
    void message() {
        cout<<"Student with id "<<id<<" failed the course"<<endl;
    }
};

class Student {
private:
    string index;
    string firstname;
    string lastname;
    int points;
public:
    Student(string index="", string firstname="", string lastname="", int points=0) {
        this->index=index;
        this->firstname=firstname;
        this->lastname=lastname;
        this->points=points;
    }

    int grade() {
        if(points>=0 && points<=49) {
            return 5;
        } else if(points>=50 && points<=59) {
            return 6;
        } else if(points>=60 && points<=69) {
            return 7;
        } else if(points>=70 && points<=79) {
            return 8;
        } else if(points>=80 && points<=89) {
            return 9;
        } else if(points>=90 && points<=100) {
            return 10;
        }
        return -1;
    }

    friend ostream &operator<<(ostream &o, Student &s) {
        return o<<s.index<<" "<<s.firstname<<" "<<s.lastname<<" "<<s.points<<" Grade: "<<s.grade()<<endl;
    }

    int getPoints() const {
        return points;
    }
    string getIndex() const {
        return index;
    }

};

class Results {
private:
    Student *students;
    int n;
public:
    Results() {
        n=0;
        students=new Student[0];
    }
    Results(const Results &r) {
        this->n=r.n;
        this->students=new Student[r.n];
        for(int i=0;i<n;i++) {
            this->students[i]=r.students[i];
        }
    }
    ~Results() {
        delete[] students;
    }

    Results &operator+=(const Student &s) {
        if(s.getPoints()<50) {
                throw StudentFailedException(s.getIndex());
        }

        Student *tmp=new Student[n+1];
        for(int i=0;i<n;i++) {
            tmp[i]=students[i];
        }
        tmp[n]=s;
        n++;
        delete[] students;
        students=tmp;
        return *this;
    }

    Results withGrade(int grade) {
        Results list;
        for(int i=0;i<n;i++) {
            if(students[i].grade()==grade) {
                list+=students[i];
            }
        }
        return list;
    }

    int getNumberOfStudents() const {
        return n;
    }

    friend ostream &operator<<(ostream &o, const Results &r) {
        for(int i=0;i<r.n;i++) {
            o<<r.students[i];
        }
        return o;
    }

};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
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

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`

    ifstream fin("input.txt");
    if(!fin.is_open()) {
        cout<<"File cannot be opened"<<endl;
        return 1;
    }

    string id, name, surname;
    int points;
    while(fin>>id>>name>>surname>>points) {
        try {
            results+=Student(id, name, surname, points);
        }
        catch (StudentFailedException &e) {
            e.message();
        }
    }

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream fout1("output1.txt");
    fout1<<results;
    fout1.close();

    Results results1=results.withGrade(grade);
    if(results1.getNumberOfStudents() > 0) {
        ofstream fout2("output2.txt");
        fout2<<results1;
        fout2.close();
    } else {
        ofstream fout2("output2.txt");
        fout2<<"None"<<endl;
        fout2.close();
    }



    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}