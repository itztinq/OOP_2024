#include <iostream>
#include <cstring>
using namespace std;

enum pozicija{
    vraboten, direktor, shef
};
class Vraboten{
private:
    char ime[15];
    int plata;
    pozicija poz;
public:
    Vraboten(){}
    Vraboten(char *ime, int plata, pozicija poz){
        strcpy(this->ime,ime);
        this->plata=plata;
        this->poz=poz;
    }
    ~Vraboten(){}
    void setIme(char *ime){
        strcpy(this->ime,ime);
    }
    char *getIme(){
        return ime;
    }
    void setPlata(int plata){
        this->plata=plata;
    }
    int getPlata(){
        return plata;
    }
    void setPozicija(pozicija poz){
        this->poz=poz;
    }
    pozicija getPozicija(){
        return poz;
    }
};
void sort(Vraboten x[], int n){
    Vraboten v;
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            if(x[i].getPlata()<x[j].getPlata()){
                v=x[j];
                x[j]=x[i];
                x[i]=v;
            }
        }
    }
}
int main(){
    Vraboten v[100];
    int plata, poz, n;
    char ime[15];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>ime>>plata>>poz;
        v[i].setIme(ime);
        v[i].setPlata(plata);
        v[i].setPozicija((pozicija)poz);
    }
    sort(v,n);
    for(int i=0;i<n;i++){
        cout<<v[i].getIme()<<" "<<v[i].getPlata()<<" "<<v[i].getPozicija()<<endl;
    }
    return 0;
}