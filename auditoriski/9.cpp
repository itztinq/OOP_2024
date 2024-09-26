#include<iostream>
#include<cstring>
#define MAX 100
using namespace std;

class Ucenik{
private:
    char *ime;
    float prosek;
    int godina;
public:
    Ucenik(char *ime="", float prosek=0, int godina=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->prosek=prosek;
        this->godina=godina;
    }
    Ucenik(const Ucenik &u){
        this->ime=new char[strlen(u.ime)+1];
        strcpy(this->ime,u.ime);
        this->prosek=u.prosek;
        this->godina=u.godina;
    }
    ~Ucenik(){
        delete [] ime;
    }
    Ucenik &operator=(const Ucenik &u){
        if(this!=&u){
            delete [] ime;
            this->ime=new char[strlen(u.ime)+1];
            strcpy(this->ime,u.ime);
            this->prosek=u.prosek;
            this->godina=u.godina;
        }
        return *this;
    }
    Ucenik &operator++(){
        godina++;
        return *this;
    }
    Ucenik &operator++(int){
        Ucenik u(*this);
        godina++;
        return u;
    }
    float getProsek(){
        return prosek;
    }
    friend ostream &operator<<(ostream &o, const Ucenik &u){
        return o<<"Ime: "<<u.ime<<", prosek: "<<u.prosek<<", godina: "<<u.godina<<endl;
    }
    friend bool operator>(const Ucenik &u1, const Ucenik &u2){
        return(u1.prosek>u2.prosek);
    }
};

class Paralelka{
private:
    Ucenik *ucenici;
    int n;
public:
    Paralelka(Ucenik *ucenici=0, int n=0){
        this->n=n;
        ucenici=new Ucenik[n];
        for(int i=0;i<n;i++){
            this->ucenici[i]=ucenici[i];
        }
    }
    Paralelka(const Paralelka &p){
        this->n=p.n;
        this->ucenici=new Ucenik[p.n];
        for(int i=0;i<n;i++){
            this->ucenici[i]=p.ucenici[i];
        }
    }
    ~Paralelka(){
        delete [] ucenici;
    }
    Paralelka &operator+=(Ucenik u){
        Ucenik *tmp=new Ucenik[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=ucenici[i];
        }
        tmp[n++]=u;
        delete[] ucenici;
        ucenici=tmp;
        return *this;
    }
    Paralelka &operator++(){
        for(int i=0;i<n;i++){
            ucenici[i]++;
        }
        return *this;
    }
    Paralelka &operator++(int){
        Paralelka p(*this);
        for(int i=0;i<n;i++){
            ucenici[i]++;
        }
        return p;
    }
    friend ostream &operator<<(ostream &o, const Paralelka &p){
        for(int i=0;i<p.n;i++){
            o<<p.ucenici[i];
        }
        return o;
    }
    void nagradi(){
        for(int i=0;i<n;i++){
            if(ucenici[i].getProsek()==10.0){
                cout<<ucenici[i];
                cout<<endl;
            }
        }
    }
    void najvisokProsek(){
        Ucenik tmp=ucenici[0];
        for(int i=0;i<n;i++){
            if(ucenici[i]>tmp){
                tmp=ucenici[i];
            }
        }
        cout<<"Najvisok prosek vo paralelkata: "<<tmp.getProsek()<<endl;
    }
};
int main(){
    Ucenik u1("Martina Martinovska",9.5,3);
    Ucenik u2("Darko Darkoski",7.3,2);
    Ucenik u3("Angela Angelovska", 10, 3);
    Paralelka p;
    p+=u1;
    p+=u2;
    p+=u3;
    cout<<p;
    cout<<"Nagradeni:"<<endl;
    p.nagradi();
    p.najvisokProsek();
    cout<<endl;
    u2++;
    cout<<p;
    cout<<endl;
    p++;
    cout<<p;
    return 0;
}