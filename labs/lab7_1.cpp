#include<iostream>
#include<string>
using namespace std;

class ZicanInstrument{
protected:
    string ime;
    int brojZici;
    float osnovna_cena;
public:
    ZicanInstrument(string ime="", int brojZici=0, float osnovna_cena=0){
        this->ime=ime;
        this->brojZici=brojZici;
        this->osnovna_cena=osnovna_cena;
    }
    virtual double cena()=0;
    int getBrojZici(){
        return brojZici;
    }
    friend ostream &operator<<(ostream &o, ZicanInstrument &z){
        return o<<z.ime<<" "<<z.brojZici<<" "<<z.cena()<<endl;
    }
    virtual bool operator==(const ZicanInstrument &z)const {
        return brojZici==z.brojZici;
    }
};

class Mandolina:public ZicanInstrument{
private:
    string forma;
public:
    Mandolina(string ime="", int brojZici=0, float osnovna_cena=0, string forma="")
    : ZicanInstrument(ime, brojZici, osnovna_cena){
        this->forma=forma;
    }
    double cena(){
        double cena=osnovna_cena;
        if(forma=="Neapolitan"){
            cena*=1.15;
        }
        return cena;
    }
    const bool &operator==(const ZicanInstrument &z) {
        if(const Mandolina *m=dynamic_cast<const Mandolina*>(&z)){
            return forma==m->forma;
        }
        return ZicanInstrument::operator==(z);
    }
};

class Violina:public ZicanInstrument{
private:
    float golemina;
public:
    Violina(string ime="", int brojZici=0, float osnovna_cena=0, float golemina=0)
    : ZicanInstrument(ime, brojZici, osnovna_cena){
        this->golemina=golemina;
    }
    double cena(){
        double cena=osnovna_cena;
        if(golemina==0.25){
            cena*=1.10;
        }else if(golemina==1.00){
            cena*=1.20;
        }
        return cena;
    }
    const bool &operator==(const ZicanInstrument &z){
        if(const Violina *v=dynamic_cast<const Violina*>(&z)){
            return golemina==v->golemina;
        }
        return ZicanInstrument::operator==(z);
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **instrumenti, int n){
    for(int i=0;i<n;i++){
        if(*instrumenti[i]==zi){
            cout<<instrumenti[i]->cena()<<endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}