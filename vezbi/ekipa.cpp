#include<iostream>
#include<cstring>
using namespace std;

class Ekipa {
private:
    string ime;
    string grad;
    int godina;
public:
    Ekipa(string ime="", string grad="", int godina=0) {
        this->ime=ime;
        this->grad=grad;
        this->godina=godina;
    }
    Ekipa(const Ekipa &e){
        this->ime=e.ime;
        this->grad=e.grad;
        this->godina=e.godina;
    }
    ~Ekipa(){}

    string getIme() {
        return ime;
    }

    friend class Natprevar;
};

class Natprevar {
private:
    Ekipa domakjin;
    Ekipa gostin;
    int golovi_d;
    int golovi_g;
public:
    Natprevar(){}
    Natprevar(Ekipa &domakjin, Ekipa &gostin, int golovi_d=0, int golovi_g=0) {
        this->domakjin=domakjin;
        this->gostin=gostin;
        this->golovi_d=golovi_d;
        this->golovi_g=golovi_g;
    }

    Ekipa getDomakjin() {
        return domakjin;
    }
    Ekipa getGostin() {
        return gostin;
    }
    int getGoloviDomakjin() {
        return golovi_d;
    }
    int getGoloviGostin() {
        return golovi_g;
    }

    ~Natprevar(){}
};

bool revans(Natprevar n1, Natprevar n2){
    if((n1.getDomakjin().getIme() == n2.getGostin().getIme()) && (n2.getDomakjin().getIme() == n1.getGostin().getIme())){
        return true;
    }
    return false;
}

Ekipa duel(Natprevar n1, Natprevar n2){
    if(revans(n1,n2)){
        int golovi_n1 = n1.getGoloviDomakjin()+n2.getGoloviGostin();
        int golovi_n2 = n1.getGoloviGostin()+n2.getGoloviDomakjin();
        if(golovi_n1>golovi_n2){
            return n1.getDomakjin();
        }
        else if (golovi_n2>golovi_n1){
            return n1.getGostin();
        }
        else return 0;
    }
    else {
        cout<<"Natprevarite ne se sovpagjaat!"<<endl;
        return 0;
    }
}

int main() {
    Ekipa e1("real madrid", "madrid", 1880);
    Ekipa e2("besiktas", "istanbul", 1903);

    const Natprevar n1(e1, e2, 1, 2);
    const Natprevar n2(e2, e1, 1, 0);

    cout<<duel(n1, n2).getIme();
    return 0;
}