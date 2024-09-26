#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Library;
class LibraryMember;

class Book{
private:
    char imeKniga[20];
    char avtor[20];
    bool dostapnost;
    friend class Library;
    friend void proveriKniga(LibraryMember &member, Library &lib, int &index);
public:
    Book(char *imeKniga="", char *avtor="", bool dostapnost=0){
        strcpy(this->imeKniga, imeKniga);
        strcpy(this->avtor, avtor);
        this->dostapnost=dostapnost;
    }
    Book(const Book &b){
        strcpy(this->imeKniga, b.imeKniga);
        strcpy(this->avtor, b.avtor);
        this->dostapnost=b.dostapnost;
    }
    ~Book(){}
};

class LibraryMember{
private:
    char imeMember[20];
    int id;
    friend void proveriKniga(LibraryMember &member, Library &lib, int &index);
public:
    LibraryMember(char *imeMember="", int id=0){
        strcpy(this->imeMember, imeMember);
        this->id=id;
    }
    ~LibraryMember(){}
};

class Library{
private:
    char biblioteka[20];
    Book knigi[30];
    int brojKnigi;
    friend void proveriKniga(LibraryMember &member, Library &lib, int &index);
public:
    Library(){
        strcpy(biblioteka, "Brakja Miladinovci");
        brojKnigi=0;
    }
    ~Library(){}
    void addBook(Book &b){
        if(brojKnigi<30){
            knigi[brojKnigi++]=b;
        }else{
            cout<<"Bibliotekata e polna."<<endl;
        }
    }
    void print(){
        cout<<"Biblioteka: "<<biblioteka<<endl;
        for(int i=0;i<brojKnigi;i++){
            cout<<knigi[i].imeKniga<<" "<<knigi[i].avtor<<" "<<knigi[i].dostapnost<<endl;
        }
    }
};

void proveriKniga(LibraryMember &member, Library &lib, int &index){
    if(lib.knigi[index].dostapnost){
        cout<<member.imeMember<<" ID: "<<member.id<<" checks out "<<lib.knigi[index].imeKniga<<endl;
        lib.knigi[index].dostapnost=false;
    }else{
        cout<<"Sorry "<<lib.knigi[index].imeKniga<<" is not available"<<endl;
    }
}

int main(){
    Library l1;
    int n;
    cin>>n;
    char ime[20], avtor[20];
    bool dostapnost;
    for(int i=0;i<n;i++){
        cin>>ime>>avtor>>dostapnost;
        Book b=Book(ime,avtor,dostapnost);
        l1.addBook(b);
    }
    l1.print();
    LibraryMember m1("Marko", 9541);
    int index;
    cin>>index;
    proveriKniga(m1,l1,index);
    return 0;
}

