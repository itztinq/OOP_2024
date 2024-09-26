#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

/*class Momche{
private:
    char name[20];
    char surname[20];
    int age;
public:
    Momche(char *i="", char *p="", int g=0){
        strcpy(name,i);
        strcpy(surname,p);
        age=g;
    }
    ~Momche(){}
    void pechati(){
        cout<<"Momche: "<<name<<" "<<surname<<" "<<age<<endl;
    }
    int get_godini(){
        return age;
    }
};

class Devojche{
private:
    char name[20];
    char surname[20];
    int age;
public:
    Devojche(char *i="", char *p="", int g=0){
        strcpy(name,i);
        strcpy(surname,p);
        age=g;
    }
    ~Devojche(){}
    void pechati(){
        cout<<"Devojche: "<<name<<" "<<surname<<" "<<age<<endl;
    }
    int get_godini(){
        return age;
    }
};

class Sredba{
private:
    Momche m;
    Devojche d;
public:
    Sredba(Momche mm, Devojche dd){
        m=mm;
        d=dd;
    }
    ~Sredba(){}
    void pechati(){
        cout<<"Sredba: "<<endl;
        m.pechati();
        d.pechati();
    }
    void dali_si_odgovaraat(){
        if(abs(m.get_godini()-d.get_godini())<5){
            cout<<"Si odgovaraat"<<endl;
        }else{
            cout<<"Ne si odgovaraat"<<endl;
        }
    }
};

int main(){
    int age;
    char name[20], surname[20];
    cin>>name>>surname>>age;
    Momche m(name,surname,age);
    cin>>name>>surname>>age;
    Devojche d(name,surname,age);
    Sredba s(m,d);
    s.pechati();
    s.dali_si_odgovaraat();
    return 0;
}*/

class Momche{
private:
    char ime[20];
    char prezime[20];
    int godini;
public:
    Momche(){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->godini=godini;
    }
    Momche(char *ime, char *prezime, int godini){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->godini=godini;
    }
    Momche(const Momche &m){
        strcpy(this->ime,m.ime);
        strcpy(this->prezime,m.prezime);
        this->godini=m.godini;
    }
    ~Momche(){}
    int getGodini(){
        return godini;
    }
    void print(){
        cout<<"Momche: "<<ime<<" "<<prezime<<" "<<godini<<endl;
    }
};
class Devojche{
private:
    char ime[20];
    char prezime[20];
    int godini;
public:
    Devojche(){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->godini=godini;
    }
    Devojche(char *ime, char *prezime, int godini){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->godini=godini;
    }
    Devojche(const Devojche &d){
        strcpy(this->ime,d.ime);
        strcpy(this->prezime,d.prezime);
        this->godini=d.godini;
    }
    ~Devojche(){}
    int getGodini(){
        return godini;
    }
    void print(){
        cout<<"Devojche: "<<ime<<" "<<prezime<<" "<<godini<<endl;
    }
};
class Sredba{
private:
    Momche m;
    Devojche d;
public:
    Sredba(const Momche m, const Devojche d){
        this->m=m;
        this->d=d;
    }
    ~Sredba(){}
    void print(){
        cout<<"Sredba: ";
        m.print();
        d.print();
    }
    void daliSiOdgovaraat(){
        if(abs(m.getGodini()-d.getGodini())<5){
            cout<<"Si odgovaraat"<<endl;
        }else{
            cout<<"Ne si odgovaraat"<<endl;
        }
    }
};
int main(){
    char ime[20], prezime[20];
    int godini;
    cout<<"Informacii za momche: "<<endl;
    cin>>ime>>prezime>>godini;
    Momche m(ime, prezime, godini);
    Momche momche(m);
    cout<<"Informacii za devojche: "<<endl;
    cin>>ime>>prezime>>godini;
    Devojche d(ime, prezime, godini);
    Devojche devojche(d);
    Sredba s(m,d);
    s.print();
    s.daliSiOdgovaraat();
    return 0;
}