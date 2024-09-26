#include<iostream>
#include<cstring>
using namespace std;

class Transport {
protected:
    char destinacija[20];
    int cena;
    int rastojanie;
public:
    Transport (char *destinacija = "", int cena = 0, int rastojanie = 0) {
        strcpy(this->destinacija, destinacija);
        this->cena = cena;
        this->rastojanie = rastojanie;
    }

    bool operator < (const Transport &t) const {
        return rastojanie < t.rastojanie;
    }

    virtual int cenaTransport() = 0;

    int getRastojanie() const {
        return rastojanie;
    }

    int getCenaTransport() {
        return cena;
    }

    char *getDestinacija() {
        return destinacija;
    }
};

class AvtomobilTransport : public Transport {
private:
    bool shofer;
public:
    AvtomobilTransport (char *destinacija = "", int cena = 0, int rastojanie = 0, bool shofer = false)
        : Transport(destinacija, cena, rastojanie) {
        this->shofer = shofer;
    }

    int cenaTransport() override {
        if(shofer) {
            return cena + cena * 0.20;
        }
        return cena;
    }
};

class KombeTransport : public Transport {
private:
    int lugje;
public:
    KombeTransport (char *destinacija = "", int cena = 0, int rastojanie = 0, int lugje = 0)
        : Transport(destinacija, cena, rastojanie) {
        this->lugje = lugje;
    }

   int cenaTransport() override {
        int namaluvanje = lugje * 200;
        return cena - namaluvanje;
    }
};

void pecatiPoloshiPonudi (Transport *ponudi[], int n, Transport &t) {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(*ponudi[j] < *ponudi[i]) {
                Transport *tmp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = tmp;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(ponudi[i]->cenaTransport() > t.cenaTransport()) {
            cout<<ponudi[i]->getDestinacija()<<" "<<ponudi[i]->getRastojanie()<<" "<<ponudi[i]->cenaTransport()<<endl;
        }
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}