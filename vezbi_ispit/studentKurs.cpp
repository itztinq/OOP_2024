#include<iostream>
#include<cstring>
using namespace std;

class StudentKurs {
protected:
    char ime[30];
    int ocena;
    bool daliUsno;
    static int MAX;
    static const int MINOCENKA = 6;
public:
    StudentKurs(char *ime = "", int ocena = 6, bool daliUsno = false){
        strcpy(this->ime,ime);
        this->ocena = ocena;
        this->daliUsno = daliUsno;
    }
    //дополни ја класата

    static void setMAX(int max) {
        MAX = max;
    }
    static int getMAX() {
        return MAX;
    }
    static int getMINOCENKA() {
        return MINOCENKA;
    }

    bool getDaliUsno() const {
        return daliUsno;
    }

    virtual int ocenka() const {
        return ocena;
    }

    char *getIme() {
        return ime;
    }

    friend ostream &operator << (ostream &o, const StudentKurs &sk) {
        return o<<sk.ime<<" --- "<<sk.ocenka();
    }

};
int StudentKurs::MAX = 10;

//вметни го кодот за StudentKursUsno

class BadInputException {
public:
    void message() {
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

class StudentKursUsno :public StudentKurs {
private:
    char *opisna;
public:
    StudentKursUsno (char *ime = "", int ocena = 6, bool daliUsno = false, char *opisna = "")
        : StudentKurs(ime, ocena) {
        opisna = new char[strlen(opisna) + 1];
        strcpy(this->opisna, opisna);
    }

    ~StudentKursUsno() {
        delete[] opisna;
    }

    void validirajOpisna(const char *opisna) {
        for(int i = 0; opisna[i] != '\0'; i++) {
            if(~isalpha(opisna[i])) {
                throw BadInputException();
            }
        }
    }

    int finalnaOcenka(const char *opisna) {
        if(strcmp(opisna, "odlicen") == 0) {
            return min(ocena + 2, StudentKurs::getMAX());
        }
        if(strcmp(opisna, "dobro") == 0) {
            return min(ocena + 1, StudentKurs::getMAX());
        }
        if(strcmp(opisna, "losho") == 0) {
            return max(ocena - 1, 1);
        }
        return ocena;
    }

    void setOpisnaOcenka(const char *opisna) {
        finalnaOcenka(opisna);
        delete [] opisna;
        opisna = new char[strlen(opisna) + 1];
        strcpy(this->opisna, opisna);
        ocena = finalnaOcenka(opisna);
    }

    int ocenka() const override {
        return ocena;
    }

    friend ostream &operator << (ostream &o, const StudentKursUsno &sku) {
        return o<<(StudentKurs&)sku<<" --- "<<sku.ocenka();
    }

    StudentKursUsno &operator += (const char *opisna) {
        try {
            setOpisnaOcenka(opisna);
        } catch (BadInputException &e) {
            e.message();
        }

        char *koregirana = new char[strlen(opisna) + 1];
        int j = 0;
        for(int i = 0; opisna[i] != '\0'; i++) {
            if(isalpha(opisna[i])) {
                koregirana[j++] = opisna[i];
            }
        }
        koregirana[j] = '\0';
        setOpisnaOcenka(koregirana);
        delete [] koregirana;
        return *this;
    }
};


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата

    void pecatiStudenti() {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for (int i = 0; i < broj; i++) {
            if(studenti[i]->ocenka() >= studenti[i]->getMINOCENKA()) {
                cout<<*studenti[i]<<endl;
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisna) {
        for(int i = 0; i < broj; i++) {
            if(strcmp(studenti[i]->getIme(), ime) == 0 && studenti[i]->getDaliUsno()) {
                StudentKursUsno *sku = dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(sku) {
                    *sku += opisna;
                }
                return;
            }
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();
    return 0;
}