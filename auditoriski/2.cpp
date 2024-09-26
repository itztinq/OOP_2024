#include<iostream>
#include<cstring>
using namespace std;

struct Student {
    char ime[30];
    char prezime[30];
    int indeks;
    int poeni[4];
    int vkupnoPoeni;
};

void citaj(Student s[],int &n){
    n=0;
    while(cin>>s[n].prezime>>s[n].ime>>s[n].indeks){
        s[n].vkupnoPoeni=0;
        for(int i=0;i<4;i++){
            cin>>s[n].poeni[i];
            s[n].vkupnoPoeni+=s[n].poeni[i];
        }
        n++;
    }
}

void sortiraj(Student s[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(s[j].poeni<s[j+1].poeni){
                swap(s[j],s[j+1]);
            }
        }
    }
}

void pecati(Student s[], int n){
    for(int i=0;i<n;i++){
        cout<<s[i].ime<<" "<<s[i].prezime<<" "<<s[i].indeks<<" "<<s[i].poeni<<endl;
    }
}

int main(){
    Student s[100];
    int n;
    cin>>n;
    citaj(s,n);
    sortiraj(s,n);
    pecati(s,n);
    return 0;
}