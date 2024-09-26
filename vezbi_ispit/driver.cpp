#include<iostream>
#include<cstring>
using namespace std;

class Vozac {
protected:
    char ime[100];
    int vozrast;
    int brojTrki;
    bool veteran;
public:
    Vozac(char *ime = "", int vozrast = 0, int brojTrki = 0, bool veteran = false) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->brojTrki = brojTrki;
        this->veteran = veteran;
    }

    friend ostream &operator << (ostream& o, const Vozac &v) {
        o << v.ime << endl << v.vozrast << endl << v.brojTrki << endl;
        if(v.veteran) {
            o<<"VETERAN"<<endl;
        }
        return o;
    }

    virtual double zarabotuvackaPoTrka() const = 0;

    virtual double danok() const = 0;

    bool operator == (const Vozac &v) {
        return zarabotuvackaPoTrka() == v.zarabotuvackaPoTrka();
    }
};

class Avtomobilist : public Vozac {
private:
    double cenaAvtomobil;
public:
    Avtomobilist (char *ime = "", int vozrast = 0, int brojTrki = 0, bool veteran = false, double cenaAvtomobil = 0)
        : Vozac(ime, vozrast, brojTrki, veteran) {
        this->cenaAvtomobil = cenaAvtomobil;
    }

    double zarabotuvackaPoTrka() const {
        return cenaAvtomobil / 5;
    }

    double danok() const {
        if(brojTrki > 10) {
            return zarabotuvackaPoTrka() * 0.15;
        }
        return zarabotuvackaPoTrka() * 0.10;
    }

    friend ostream &operator << (ostream &o, const Avtomobilist &a) {
        return o << (Vozac&)a << endl << a.cenaAvtomobil << endl;
    }
};

class Motociklist : public Vozac {
private:
    int mokjnost;
public:
    Motociklist (char *ime = "", int vozrast = 0, int brojTrki = 0, bool veteran = false, int mokjnost = 0)
        : Vozac(ime, vozrast, brojTrki, veteran) {
        this->mokjnost = mokjnost;
    }

    double zarabotuvackaPoTrka() const {
        return mokjnost * 20;
    }

    double danok() const {
        if(veteran) {
            return zarabotuvackaPoTrka() * 0.25;
        }
        return zarabotuvackaPoTrka() * 0.20;
    }

    friend ostream &operator << (ostream &o, const Motociklist &m) {
        return o << (Vozac&)m << endl << m.mokjnost << endl;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, const Vozac *v) {
    int brojac = 0;
    for(int i = 0; i < n; i++) {
        if(*vozaci[i] == *v) {
            brojac++;
        }
    }
    return brojac;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}