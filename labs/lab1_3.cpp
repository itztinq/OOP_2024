#include<iostream>
using namespace std;

struct FudbalskiIgrac{
    char ime[50];
    int dresBroj;
    int dadeniGolovi;
};

struct FudbalskiTim{
    char timIme[50];
    FudbalskiIgrac igraci[11];
    int golovi=0;
    void vcitaj(){
        cin>>timIme;
        for(int i=0;i<11;i++){
            cin>>igraci[i].ime>>igraci[i].dresBroj>>igraci[i].dadeniGolovi;
            golovi+=igraci[i].dadeniGolovi;
        }
    }
};

void najdobarTim(FudbalskiTim *timovi,int n){
    int indexMaxGol=0;
    int maxGol=0;
    for(int i=0;i<n;i++){
        if(timovi[i].golovi>maxGol){
            maxGol=timovi[i].golovi;
            indexMaxGol=i;
        }
    }
    cout<<"Najdobar tim e: "<<timovi[indexMaxGol].timIme<<endl;
}

int main(){
    int n;
    cin>>n;
    FudbalskiTim timovi[n];
    for(int i=0;i<n;i++){
        timovi[i].vcitaj();
    }
    najdobarTim(timovi,n);
    return 0;
}