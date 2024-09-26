#include<iostream>
#include<cstring>
using namespace std;

class Delo {
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo (char *ime = "", int godina = 0, char zemja[50] = "") {
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->zemja, zemja);
    }

    bool operator == (const Delo &d) {
        return strcmp(ime, d.ime) == 0;
    }

    char *getIme() {
        return ime;
    }
    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }
    int getGodina() {
        return godina;
    }
    void setGodina(int godina) {
        this->godina = godina;
    }
    char *getZemja() {
        return zemja;
    }
    void setZemja(char *zemja) {
        strcpy(this->zemja, zemja);
    }
};

class Pretstava {
protected:
    Delo delo;
    int brojProdadeni;
    char data[15];
public:
    Pretstava (Delo &delo, int brojProdadeni = 0, char data[15] = "") {
        this->delo = delo;
        this->brojProdadeni = brojProdadeni;
        strcpy(this->data, data);
    }

    Delo &getDelo() {
        return delo;
    }
    int getBrojProdadeni() {
        return brojProdadeni;
    }

    virtual int cena() {
        int M;
        if(delo.getGodina() >= 1900 && delo.getGodina() <= 2099) {
            M = 50;
        } else if(delo.getGodina() >= 1800 && delo.getGodina() <= 1899) {
            M = 75;
        } else {
            M = 100;
        }

        int N;
        if(strcmp(delo.getZemja(), "Italija") == 0) {
            N = 100;
        } else if(strcmp(delo.getZemja(), "Rusija") == 0) {
            N = 150;
        } else {
            N = 80;
        }

        return M+N;
    }

};

class Balet : public Pretstava {
private:
    static double cenaBalet;
public:
    Balet (Delo &delo, int brojProdadeni, char data[15] = "")
        : Pretstava(delo, brojProdadeni, data) {}

    static void setCenaBalet(int cena) {
        cenaBalet = cena;
    }

    int cena() override {
        return Pretstava::cena() + cenaBalet;
    }

};
double Balet::cenaBalet = 150;

class Opera : public Pretstava {
public:
    Opera (Delo &delo, int brojProdadeni, char data[15] = "")
        : Pretstava(delo, brojProdadeni, data) {}

    int cena() override {
        return Pretstava::cena();
    }
};

int prihod(Pretstava **pretstavi, int n) {
    if(n == 0) {
        return 0;
    }

    int vkupno = 0;
    for(int i = 0; i < n; i++) {
        vkupno += pretstavi[i]->getBrojProdadeni() * pretstavi[i]->cena();
    }
    return vkupno;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo &delo) {
    int brojac = 0;
    for(int i = 0; i < n; i++) {
        if(pretstavi[i]->getDelo() == delo) {
            brojac++;
        }
    }
    return brojac;
}


//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}