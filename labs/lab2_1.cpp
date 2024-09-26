#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class BasketballPlayer{
private:
    char ime[20];
    char prezime[20];
    int dresBroj;
    int poeni_n1;
    int poeni_n2;
    int poeni_n3;
public:
    BasketballPlayer(char *i, char *p, int dres, int p1, int p2, int p3){
        strcpy(ime,i);
        strcpy(prezime,p);
        dresBroj=dres;
        poeni_n1=p1;
        poeni_n2=p2;
        poeni_n3=p3;
    }
    ~BasketballPlayer(){}
    void print(){
        double poeni=static_cast<double>(poeni_n1+poeni_n2+poeni_n3)/3;
        cout<<"Player: "<<ime<<" "<<prezime<<" with number: "<<dresBroj<<" has "<<poeni<<" points on average"<<endl;
    }
};

int main(){
    char i[20], p[20];
    int dres, p1, p2, p3;
    cin>>i>>p>>dres>>p1>>p2>>p3;
    BasketballPlayer bp(i,p,dres,p1,p2,p3);
    bp.print();
    return 0;
}