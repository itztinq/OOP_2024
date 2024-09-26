#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Student {
private:
    string indeks;
    string ime;
    string prezime;
    int poeni;
public:
    Student (string indeks = "", string ime = "", string prezime = "", int poeni = 0) {
        this->indeks = indeks;
        this->ime = ime;
        this->prezime = prezime;
        this->poeni = poeni;
    }

    int grade() const {
        if(poeni < 50) return 5;
        else if(poeni < 60) return 6;
        else if(poeni < 70) return 7;
        else if(poeni < 80) return 8;
        else if(poeni < 90) return 9;
        else return 10;
    }

    friend ostream &operator<<(ostream &o, const Student &s) {
        return o<<s.indeks<<" "<<s.ime<<" "<<s.prezime<<" "<<s.poeni<<" Grade: "<<s.grade()<<endl;
    }

    int getPoeni() const {
        return poeni;
    }
    string getIndeks() const {
        return indeks;
    }
};

class StudentFailedException {
private:
    string ind;
public:
    StudentFailedException(string ind = "") {
        this->ind = ind;
    }
    void message() {
        cout<<"Student with id "<<ind<<" failed the course"<<endl;
    }
};

class Results {
private:
    Student *studenti;
    int n;
public:
    Results () {
        n = 0;
        studenti = nullptr;
    }

    Results (const Results &r) {
        this->n = r.n;
        this->studenti = new Student[r.n];
        for (int i = 0; i < r.n; i++) {
            this->studenti[i] = r.studenti[i];
        }
    }

    Results (Student *studenti, int n) {
        this->n = n;
        this->studenti = new Student[n];
        for (int i = 0; i < n; i++) {
            this->studenti[i] = studenti[i];
        }
    }

    Results &operator=(const Results &r) {
        if (this != &r) {
            delete [] studenti;
            this->n = r.n;
            this->studenti = new Student[r.n];
            for (int i = 0; i < r.n; i++) {
                this->studenti[i] = r.studenti[i];
            }
        }
    }

    ~Results () {
        delete[] studenti;
    }

    Results &operator += (Student &s) {
        if(s.getPoeni() < 50 ) {
            throw StudentFailedException(s.getIndeks());
        }

        Student *nov = new Student[n+1];
        for (int i = 0; i < n; i++) {
            nov[i] = studenti[i];
        }
        nov[n++] = s;
        delete [] studenti;
        studenti = nov;
        return *this;
    }

    Results withGrade(int grade) {
        Results filtered;
        for (int i = 0; i < n; i++) {
            if(studenti[i].grade() == grade) {
                filtered += studenti[i];
            }
        }
        return filtered;
    }

    bool empty() const {
        return n == 0;
    }

    friend ostream &operator<<(ostream &o, const Results &r) {
        for (int i = 0; i < r.n; i++) {
            o<<r.studenti[i];
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

    ifstream ifs("input.txt");
    string indeks, ime, prezime;
    int poeni;

    while(ifs>>indeks>>ime>>prezime>>poeni) {

        try {
            Student student (indeks, ime, prezime, poeni);
            results += student;
        } catch (StudentFailedException &e) {
            e.message();
        }
    }
    ifs.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream ofs1 ("output1.txt");
    ofs1<<results;
    ofs1.close();

    ofstream ofs2 ("output2.txt");
    Results results2 = results.withGrade(grade);
    if(results2.empty()) {
        ofs2<<"None"<<endl;
    } else {
        ofs2<<results2;
    }
    ofs2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}