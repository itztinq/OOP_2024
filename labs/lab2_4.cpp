#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Book{
private:
    char ime[100];
    char avtorIme[100];
    char avtorPrezime[100];
    char ISBN[100];
    int godina;
public:
    Book(){}
    Book(char *ime, char *avtorIme, char *avtorPrezime, char *ISBN, int godina){
        strcpy(this->ime,ime);
        strcpy(this->avtorIme,avtorIme);
        strcpy(this->avtorPrezime,avtorPrezime);
        strcpy(this->ISBN,ISBN);
        this->godina=godina;
    }
    ~Book(){}

    void setIme(char *ime){
        strcpy(this->ime,ime);
    }
    void setAvtorIme(char *avtorIme){
        strcpy(this->avtorIme,avtorIme);
    }
    void setAvtorPrezime(char *avtorPrezime){
        strcpy(this->avtorPrezime,avtorPrezime);
    }
    void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    }
    void setGodina(int godina){
        this->godina=godina;
    }
    char *getIme(){
        return ime;
    }
    char *getAvtorIme(){
        return avtorIme;
    }
    char *getAvtorPrezime(){
        return avtorPrezime;
    }
    char *getISBN(){
        return ISBN;
    }
    int getGodina(){
        return godina;
    }

    void display(){
        cout<<ime<<", "<<avtorIme<<" "<<avtorPrezime<<", "<<ISBN<<", "<<godina<<endl;
    }
};

void booksByOrder(Book *books, int n){
    for(int i=0;i<n;i++){
        for(int j=0;i<n-1-i;j++){
            if(books[j].getGodina()>books[j+1].getGodina()){
                Book temp=books[j];
                books[j]=books[j+1];
                books[j+1]=temp;
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    char ime[100], avtorIme[100], avtorPrezime[100], ISBN[100];
    int godina;
    Book kniga[n];
    for(int i=0;i<n;i++){
        cin>>ime>>avtorIme>>avtorPrezime>>ISBN>>godina;
        kniga[i].setIme(ime);
        kniga[i].setAvtorIme(avtorIme);
        kniga[i].setAvtorPrezime(avtorPrezime);
        kniga[i].setISBN(ISBN);
        kniga[i].setGodina(godina);
    }
    booksByOrder(kniga,n);
    for(int i=0;i<n;i++){
        kniga[i].display();
    }
    return 0;
}