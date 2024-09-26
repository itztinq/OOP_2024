#include<iostream>
#include<string>
using namespace std;

class TeniskiIgrac{
protected:
    string ime;
    string prezime;
    bool liga;
public:
    TeniskiIgrac(string ime="", string prezime="", bool liga=false){
        this->ime=ime;
        this->prezime=prezime;
        this->liga=liga;
    }
    bool igraVoLiga(){
        return this->liga;
    }
    friend ostream &operator<<(ostream &o, TeniskiIgrac &t){
        o<<t.ime + t.prezime<<" "<<t.liga;
        return o;
    }

    ~TeniskiIgrac(){}
};

class RangiranTeniskiIgrac : public TeniskiIgrac{
private:
    int rang;
public:
    RangiranTeniskiIgrac(string ime="", string prezime="", bool liga=false, int rang=0)
    :TeniskiIgrac(ime,prezime,liga){
        this->rang=rang;
    }
    RangiranTeniskiIgrac(const TeniskiIgrac &t, int rang=0):TeniskiIgrac(t){
        this->rang=rang;
    }
    ~RangiranTeniskiIgrac(){}
    friend ostream &operator<<(ostream &o, RangiranTeniskiIgrac &t){
        o<<TeniskiIgrac(t);
        o<<t.rang;
        return o;
    }
};