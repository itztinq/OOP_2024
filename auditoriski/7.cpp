#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

/*
class Ekipa{
private:
    char name[20];
    int godina;
    char grad[20];
public:
    Ekipa(char *i="",char *g="",int god=0){
        strcpy(name,i);
        strcpy(grad,g);
        godina=god;
    }
    ~Ekipa(){}
    char *get_ime(){
        return name;
    }
    char *get_grad(){
        return grad;
    }
    int get_godina(){
        return godina;
    }
};

class Natprevar{
private:
    Ekipa domakjin, gostin;
    int goloviDomakjin;
    int goloviGostin;
public:
    Natprevar(){}
    Natprevar(Ekipa d,Ekipa g, int gd, int gg){
        domakjin=d;
        gostin=g;
        goloviDomakjin=gd;
        goloviGostin=gg;
    }
    ~Natprevar(){}
    Ekipa getDomakjin(){
        return domakjin;
    }
    Ekipa getGostin(){
        return gostin;
    }
    int get_goloviDomakjin(){
        return goloviDomakjin;
    }
    int get_goloviGostin(){
        return goloviGostin;
    }
};

bool revans(Natprevar n1, Natprevar n2){
    if(n1.getDomakjin().get_ime() == n2.getGostin().get_ime()
        && n1.getGostin().get_ime() == n2.getDomakjin().get_ime()){
        return true;
    }else{
        return false;
    }
}

Ekipa duel(Natprevar n1, Natprevar n2){
    if(revans(n1,n2)){
        int golovi1=n1.get_goloviDomakjin()+n2.get_goloviGostin();
        int golovi2=n1.get_goloviGostin()+n2.get_goloviDomakjin();
        if(golovi1>golovi2){
            return n1.getDomakjin();
        }else if(golovi1<golovi2){
            return n2.getDomakjin();
        }else {
            return 0;
        }
    }else{
        cout<<"Ne se sovpagjaat"<<endl;
        return 0;
    }
}

int main(){
    Ekipa e1("real madrid","madrid");
    Ekipa e2("fc barcelona","barcelona");
    Natprevar n1(e1,e1,2,1);
    Natprevar n2(e2,e1,1,2);
    cout<<duel(n1,n2).get_ime();
    return 0;
}*/

class Ekipa{
private:
    char ime[20];
    int godina;
    char grad[20];
public:
    Ekipa(){
        strcpy(this->ime,ime);
        strcpy(this->grad,grad);
        this->godina=godina;
    }
    Ekipa(char *ime, int godina, char *grad){
        strcpy(this->ime,ime);
        strcpy(this->grad,grad);
        this->godina=godina;
    }
    const char *getIme(){
        return ime;
    }
    ~Ekipa(){}
};
class Natprevar{
private:
    Ekipa domakjin;
    Ekipa gostin;
    int goloviDomakjin;
    int goloviGostin;
public:
    Natprevar(const Ekipa &domakkjin, const Ekipa &gostin, int goloviDomakjin, int goloviGostin){
        this->domakjin=domakjin;
        this->gostin=gostin;
        this->goloviDomakjin=goloviDomakjin;
        this->goloviGostin=goloviGostin;
    }
    Ekipa getDomakjin() const {
        return domakjin;
    }
    Ekipa getGostin() const {
        return gostin;
    }
    int getGoloviDomakjin() const {
        return goloviDomakjin;
    }
    int getGoloviGostin() const {
        return goloviGostin;
    }
    ~Natprevar(){}
};
bool revans(const Natprevar n1, const Natprevar n2){
    if(strcmp(n1.getDomakjin().getIme(),n2.getGostin().getIme())==0 && strcmp(n1.getGostin().getIme(),n2.getDomakjin().getIme())==0){
        return true;
    }
}
Ekipa duel(const Natprevar n1, const Natprevar n2){
    if(revans(n1,n2)){
        int golovi1=n1.getGoloviDomakjin()+n2.getGoloviGostin();
        int golovi2=n1.getGoloviGostin()+n2.getGoloviDomakjin();
        if(golovi1>golovi2){
            return n1.getDomakjin();
        }else if(golovi1<golovi2){
            return n1.getGostin();
        }else{
            return 0;
        }
    }else{
        cout<<"Ne se sovpagjaat"<<endl;
        return 0;
    }
}