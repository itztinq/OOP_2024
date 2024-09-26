#include<iostream>
#include<cstring>
using namespace std;

class Oglas {
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena; //vo evra
public:
    Oglas (char *naslov = "", char *kategorija = "", char *opis = "", float cena = 0) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }

    bool operator > (const Oglas &o) {
        return cena > o.cena;
    }

    friend ostream &operator << (ostream &os, const Oglas &o) {
        return os<<o.naslov<<endl<<o.opis<<endl<<o.cena<<" evra"<<endl;
    }

    int getCena() {
        return cena;
    }

    char *getKategorija() {
        return kategorija;
    }

};

class NegativnaVrednost {
public:
    void message() {
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *oglasi;
    int n;
public:
    Oglasnik (char *ime = "") {
        strcpy(this->ime, ime);
        this->n = 0;
        this->oglasi = nullptr;
    }

    Oglasnik &operator += (Oglas &o) {
        if(o.getCena() < 0) {
            throw NegativnaVrednost();
        }

        Oglas *tmp = new Oglas [n+1];
        for (int i = 0; i < n; i++) {
            tmp[i] = oglasi[i];
        }
        tmp[n++] = o;
        delete [] oglasi;
        oglasi = tmp;
        return *this;
    }

    ~Oglasnik() {
        delete [] oglasi;
    }

    friend ostream &operator << (ostream &os, const Oglasnik &ogl) {
        os<<ogl.ime<<endl;
        for (int i = 0; i < ogl.n; i++) {
            os<<ogl.oglasi[i]<<endl;
        }
        return os;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < n; i++) {
            if(strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout<<oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena() {
        int minIndex = 0;
        for (int i = 0; i < n; i++) {
            if(oglasi[i].getCena() < oglasi[minIndex].getCena()) {
                minIndex = i;
            }
        }
        cout<<oglasi[minIndex]<<endl;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl+=o;
            } catch (NegativnaVrednost &e) {
                e.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl+=o;
            } catch (NegativnaVrednost &e) {
                e.message();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl+=o;
            } catch (NegativnaVrednost &e) {
                e.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl+=o;
            } catch (NegativnaVrednost &e) {
                e.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}