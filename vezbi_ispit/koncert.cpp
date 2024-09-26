#include<iostream>
#include<cstring>
using namespace std;

class Koncert {
protected:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    double cenaBilet;
public:
    Koncert (char *naziv = "", char *lokacija = "", double cenaBilet = 0) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cenaBilet = cenaBilet;
    }

    static void setSezonskiPopust (float popust) {
        sezonskiPopust = popust;
    }

    static float getSezonskiPopust () {
        return sezonskiPopust;
    }

    virtual double cena() const {
        return cenaBilet * (1 - sezonskiPopust);
    }

    const char *getNaziv() const {
        return naziv;
    }


};
float Koncert::sezonskiPopust = 0.20;

class ElektronskiKoncert : public Koncert {
private:
    char *dj;
    float vremetraenje;
    bool dnevna;
public:
    ElektronskiKoncert (char *naziv = "", char *lokacija = "", double cenaBilet = 0, char *dj = 0,float vremetraenje = 0, bool dnevna = false)
        : Koncert (naziv, lokacija, cenaBilet) {
        this->dj = new char [strlen(dj) + 1];
        strcpy(this->dj, dj);
        this->vremetraenje = vremetraenje;
        this->dnevna = dnevna;
    }

    double cena() const override {
        double total = Koncert::cena();
        if(vremetraenje > 7) {
            total += 360;
        } else if(vremetraenje > 5) {
            total += 150;
        }

        if(dnevna) {
            total -= 50;
        } else {
            total += 100;
        }
        return total;
    }

    ~ElektronskiKoncert () {
        delete [] dj;
    }

};

void najskapKoncert(Koncert ** koncerti, int n) {
    int najskapIndeks = 0;
    int elektroncki = 0;
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])) {
            elektroncki++;
        }
        if(koncerti[i]->cena() > koncerti[najskapIndeks]->cena()) {
            najskapIndeks = i;
        }
    }

    cout<<"Najskap koncert: "<<koncerti[najskapIndeks]->getNaziv()<<" "<<koncerti[najskapIndeks]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<elektroncki<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski) {
    if(elektronski) {
        for(int i = 0; i < n; i++) {
            if(dynamic_cast<ElektronskiKoncert*>(koncerti[i])) {
                if(strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    return true;
                }
            }
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}