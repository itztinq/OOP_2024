#include<iostream>
#include<cstring>
using namespace std;

class FudbalskaEkipa {
protected:
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa (char *trener = "", int *golovi = nullptr) {
        strcpy(this->trener, trener);
        if(golovi != nullptr) {
            for(int i = 0; i < 10; i++) {
                this->golovi[i] = golovi[i];
            }
        } else {
            for(int i = 0; i < 10; i++) {
                this->golovi[i] = 0;
            }
        }
    }

    virtual int uspeh() const = 0;

    FudbalskaEkipa &operator += (int posledenNatprevar) {
        for(int i = 0; i < 9; i++) {
            golovi[i] = golovi[i+1];
        }

        golovi[9] = posledenNatprevar;
        return *this;
    }

    bool operator > (const FudbalskaEkipa &f) const {
        return uspeh() > f.uspeh();
    }

    virtual void print(ostream &o) const = 0;

    friend ostream &operator<<(ostream &o, const FudbalskaEkipa &f) {
        f.print(o);
        return o;
    }
};

class Klub : public FudbalskaEkipa {
private:
    char ime[100];
    int tituli;
public:
    Klub (char *trener = "", int *golovi = nullptr, char *ime = "", int tituli = 0)
        : FudbalskaEkipa(trener, golovi) {
        strcpy(this->ime, ime);
        this->tituli = tituli;
    }

    int uspeh() const override {
        int zbir = 0;
        for(int i = 0; i < 10; i++) {
            zbir += golovi[i];
        }

        return zbir * 3 + tituli * 1000;
    }

    void print(ostream &o) const override {
        o<<ime<<endl<<trener<<endl<<uspeh()<<endl;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char drzava[100];
    int nastapi;
public:
    Reprezentacija (char *trener = "", int *golovi = nullptr, char *drzava = "", int nastapi = 0)
        : FudbalskaEkipa(trener, golovi) {
        strcpy(this->drzava, drzava);
        this->nastapi = nastapi;
    }

    int uspeh() const override {
        int zbir = 0;
        for(int i = 0; i < 10; i++) {
            zbir += golovi[i];
        }

        return zbir * 3 + nastapi * 50;
    }

    void print(ostream &o) const override {
        o<<drzava<<endl<<trener<<endl<<uspeh()<<endl;
    }
};

void najdobarTrener(FudbalskaEkipa *niza[], int n) {
    FudbalskaEkipa *best = niza[0];
    for(int i = 1; i < n; i++) {
        if(*niza[i] > *best) {
            best = niza[i];
        }
    }
    cout<<*best<<endl;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}