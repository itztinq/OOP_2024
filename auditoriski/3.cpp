#include <iostream>
#include <cstring>
using namespace std;

struct Grad {
    char ime [100];
    int ziteli;
};

struct Pretsedatel{
    char ime[30];
    char prezime[30];
    char partija[30];
};

struct Drzava {
    char ime[100];
    Pretsedatel pretsedatel;
    Grad glaven;
    int ziteli;
};

Drzava drzavi[100];
int n;

void citaj() {
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>drzavi[i].ime;
        cin>>drzavi[i].pretsedatel.ime;
        cin>>drzavi[i].pretsedatel.prezime;
        cin>>drzavi[i].pretsedatel.partija;
        cin>>drzavi[i].glaven.ime;
        cin>>drzavi[i].glaven.ziteli;
        cin>>drzavi[i].ziteli;
    }
}

void pecati(){
    for(int i=0;i<n;i++){
        cout << drzavi[i].ime << "\t" << drzavi[i].pretsedatel.ime << drzavi[i].pretsedatel.prezime << drzavi[i].pretsedatel.partija << "\t";
        cout << drzavi[i].glaven.ime << "\t";
        cout << drzavi[i].glaven.ziteli << "\t";
        cout << drzavi[i].ziteli << endl;
    }
}

void najmnoguZiteli() {
    Drzava max = drzavi[0];
    for (int i = 1; i < n; ++i) {
        if (drzavi[i].glaven.ziteli > max.glaven.ziteli) {
            max = drzavi[i];
        }
    }
    cout << max.pretsedatel.ime << " " << max.pretsedatel.prezime << endl;
}

int main() {
    citaj();
    pecati();
    najmnoguZiteli();
    return 0;
}