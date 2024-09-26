#include<iostream>
#include<cstring>
using namespace std;

enum pozicija {
    vraboten, //0
    direktor, //1
    shef      //2
};

class Vraboten {
private:
    string ime;
    int plata;
    pozicija poz;
public:
    Vraboten(string ime="", int plata=0, pozicija poz=vraboten){
        this->ime=ime;
        this->plata=plata;
        this->poz=poz;
    }
    ~Vraboten() {}

    void print(){
        cout<<ime<<" "<<plata<<" ";
        switch (poz) {
            case vraboten:
                cout<<"vraboten"<<endl; break;
            case direktor:
                cout<<"direktor"<<endl; break;
            default:
                cout<<"shef"<<endl; break;
        }
    }

    void setIme(string ime) {
        this->ime=ime;
    }
    void setPlata(int plata) {
        this->plata=plata;
    }
    void setPozicija(pozicija poz) {
        this->poz=poz;
    }
    string getIme() {
        return ime;
    }
    int getPlata() {
        return plata;
    }
    pozicija getPozicija() {
        return poz;
    }
};

void sort(Vraboten v[], int n) {
    Vraboten e;
    for(int i=0; i<n-1; i++) {
        for(int j=i; j<n; j++) {
            if(v[i].getPlata() < v[j].getPlata()) {
                e=v[j];
                v[j]=v[i];
                v[i]=e;
            }
        }
    }
}

int main() {
    int n;
    cin>>n;
    Vraboten v[10];
    string ime;
    int plata;
    int poz;
    for(int i=0; i<n; i++) {
        cin>>ime>>plata>>poz;
        v[i]=Vraboten(ime, plata, (pozicija)poz);
    }

    sort(v,n);
    for(int i=0; i<n; i++) {
        v[i].print();
    }

    return 0;
}