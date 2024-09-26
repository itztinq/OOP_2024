#include<iostream>
#include<string>
using namespace std;

class DebitAccount{
protected:
    string ime;
    long broj_smetka;
    double saldo;
public:
    DebitAccount(string ime="", long broj_smetka=0, double saldo=0.0){
        this->ime=ime;
        this->broj_smetka=broj_smetka;
        this->saldo=saldo;
    }
    void pregled(){
        cout<<ime<<" "<<broj_smetka<<" "<<saldo;
    }
    void investiraj(double iznos){
        if(iznos>=0){
            saldo+=iznos;
        }else{
            cout<<"Ne moze da investirate negativen iznos"<<endl;
        }
    }
    void podigni(double iznos){
        if(iznos<=saldo){
            saldo-=iznos;
        }else{
            return;
        }
    }
    double getSaldo(){
        return this->saldo;
    }
    ~DebitAccount(){}
};

class CreditAccount:public DebitAccount{
private:
    double limit;
    double kamata;
    double minus;
public:
    CreditAccount(string ime="", long broj_smetka=0, double saldo=0.0, double limit=1000, double kamata=0.05, double minus=0)
    :DebitAccount(ime,broj_smetka,saldo){
        this->limit=limit;
        this->kamata=kamata;
        this->minus=minus;
    }
    void podigni(double iznos){
        int saldo=getSaldo();
        if(iznos<=saldo){
            DebitAccount::podigni(iznos);
        }else if(iznos<=saldo+limit-minus){
            double 
        }
    }
};