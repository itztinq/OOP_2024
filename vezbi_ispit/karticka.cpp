#include<iostream>
#include<cstring>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char *smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin = pin;
        this->povekjePin = false;
    }
    // дополниете ја класата

    Karticka (const Karticka &k) {
        strcpy(this->smetka,k.smetka);
        this->pin = k.pin;
        this->povekjePin = k.povekjePin;
    }

    virtual int tezinaZaProbivanje() const {
        int cifri = 0;
        int tmp = pin;
        while (tmp > 0) {
            cifri++;
            tmp /= 10;
        }
        return cifri;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    char *getSmetka() {
        return smetka;
    }

    friend ostream &operator << (ostream &o, const Karticka &k) {
        return o<<k.smetka<<": "<<k.tezinaZaProbivanje();
    }
};

//вметнете го кодот за SpecijalnaKarticka

class OutOfBoundException {
public:
    void message() {
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    int num;
    int *dopolnitelniPinovi;
public:
    SpecijalnaKarticka(char *smetka,int pin) : Karticka(smetka,pin) {
        povekjePin = true;
        this->num = 0;
        this->dopolnitelniPinovi = new int[num];
    }

    ~SpecijalnaKarticka() {
        delete[] dopolnitelniPinovi;
    }

    int tezinaZaProbivanje() const override {
        return Karticka::tezinaZaProbivanje() + num;
    }

    SpecijalnaKarticka &operator += (int novPin) {
        if(num >= 4) {
            throw OutOfBoundException();
        }

        int *tmp = new int[num+1];
        for(int i=0;i<num;i++) {
            tmp[i] = dopolnitelniPinovi[i];
        }
        tmp[num++] = novPin;
        delete[] dopolnitelniPinovi;
        dopolnitelniPinovi = tmp;
        return *this;
    }
};


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka **karticki, int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата

    static void setLIMIT(int l) {
        LIMIT = l;
    }

    void pecatiKarticki() const {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0; i<broj; i++) {
            if(karticki[i]->tezinaZaProbivanje() <= LIMIT) {
                cout<<*karticki[i]<<endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for(int i=0; i<broj; i++) {
            if(strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(sk) {
                    try {
                        *sk += novPin;
                    } catch (OutOfBoundException &e) {
                        e.message();
                    }
                }
            }
        }
    }

};
int Banka::LIMIT = 7;


int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}