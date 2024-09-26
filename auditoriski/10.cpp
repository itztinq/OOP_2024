#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Vehicle{
private:
    char regBroj[8];
    char *vozac;
    int reon;
    int maxPatnici;
    float izvozeniKM;
public:
    Vehicle(char *regBroj="", char *vozac="", int reon=0, int maxPatnici=0){
        strcpy(this->regBroj,regBroj);
        this->vozac=new char[strlen(vozac)+1];
        strcpy(this->vozac,vozac);
        this->reon=reon;
        this->maxPatnici=maxPatnici;
        this->izvozeniKM=0;
    }
    Vehicle(const Vehicle &v){
        strcpy(this->regBroj,v.regBroj);
        this->vozac=new char[strlen(v.vozac)+1];
        strcpy(this->vozac,v.vozac);
        this->reon=v.reon;
        this->maxPatnici=v.maxPatnici;
        this->izvozeniKM=v.izvozeniKM;
    }
    ~Vehicle(){
        delete[] vozac;
    }
    Vehicle &operator=(const Vehicle &v){
        if(this!=&v){
            delete[] vozac;
            strcpy(this->regBroj,v.regBroj);
            this->vozac=new char[strlen(v.vozac)+1];
            strcpy(this->vozac,v.vozac);
            this->reon=v.reon;
            this->maxPatnici=v.maxPatnici;
            this->izvozeniKM=v.izvozeniKM;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &o, const Vehicle &v){
        return o<<"ID: "<<v.regBroj<<" Driver's name: "<<v.vozac<<" Passenger capacity: "<<v.maxPatnici<<" Location: "<<v.reon<<" kms driven: "<<v.izvozeniKM;
    }
    bool operator==(const Vehicle &v){
        return strcmp(this->regBroj,v.regBroj)==0;
    }
    Vehicle &operator+=(const Vehicle &v){
        this->izvozeniKM=izvozeniKM;
        return *this;
    }
    int distanca(int area){
        return abs(this->reon-area);
    }
    friend class RideApp;
};

class RideApp{
private:
    char ime[20];
    Vehicle *vozila;
    int n;
public:
    RideApp(char *ime=""){
        strcpy(this->ime,ime);
        vozila=new Vehicle[0];
        n=0;
    }
    RideApp(const RideApp &app){
        strcpy(this->ime,app.ime);
        this->n=app.n;
        vozila=new Vehicle[this->n];
        for(int i=0;i<n;i++){
            vozila[i]=app.vozila[i];
        }
    }
    RideApp &operator+=(const Vehicle &v){
        for(int i=0;i<n;i++){
            if(vozila[i]==v){
                return *this;
            }
        }
        Vehicle *tmp=new Vehicle[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=vozila[i];
        }
        tmp[n++]=v;
        delete[] vozila;
        vozila=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &o, const RideApp &app){
        o<<app.ime<<endl;
        if(app.n==0){
            o<<"W=EMPTY"<<endl;
        }
        for(int i=0;i<app.n;i++){
            o<<app.vozila[i]<<endl;
        }
        return o;
    }
    void addRide(int area, int patnici, int distancaKM){
        bool prv=true;
        int idx=-1;
        int minDistanca;
        for(int i=0;i<n;i++){
            if(vozila[i].maxPatnici>=patnici){
                if(prv){
                    prv=false;
                    idx=i;
                    minDistanca=vozila[i].distanca(area);
                }else{
                    if(vozila[i].distanca(area)<minDistanca){
                        idx=i;
                        minDistanca=vozila[i].distanca(area);
                    }
                }
            }
        }
        vozila[idx]+=distancaKM;
        vozila[idx].reon=area;
    }
};
