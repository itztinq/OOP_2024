#include<iostream>
#include<cstring>
using namespace std;

class LibraryMember {
private:
    string memberName;
    int id;
public:
    LibraryMember(string memberName="", int id=0) {
        this->memberName=memberName;
        this->id=id;
    }
    ~LibraryMember(){}
    void setName(string memberName){
        this->memberName=memberName;
    }
    void setID(int id){
        this->id=id;
    }
    string getName(){
        return memberName;
    }
    int getID(){
        return id;
    }
    friend class Book;
};

class Library;

class Book {
private:
    string name;
    string author;
    bool availability;
    friend class Library;
    friend void checkOutBook(LibraryMember &member, Library &library, int &index);
public:
    Book(string name="", string author="", bool availability=true) {
        this->name=name;
        this->author=author;
        this->availability=availability;
    }
    Book(const Book &b) {
        this->name=b.name;
        this->author=b.author;
        this->availability=b.availability;
    }
    ~Book(){}
};

class Library {
private:
    string name;
    Book books[20];
    int numOfBooks;
    friend void checkOutBook(LibraryMember &member, Library &library, int &index);
public:
    Library() {
        string name="Brakja Miladinovci";
        int numOfBooks=0;
    }
    ~Library(){}

    void addBook(Book &b){
        if(numOfBooks<20){
            books[numOfBooks++]=b;
        }
        else {
            cout<<"Library is full."<<endl;
        }
    }

    void print(){
        cout<<"Library: "<<name<<endl;
        cout<<"Books: "<<endl;
        cout<<"-------------------"<<endl;
        for(int i=0;i<numOfBooks;i++) {
            cout << books[i].name << " " << books[i].author << " " << books[i].availability << endl;
        }
    }
};

void checkOutBook(LibraryMember &member, Library &library, int &index) {
    if(library.books[index].availability){
        cout<<member.getName()<<" ID: "<<member.getID()<<" cheeks out "<<library.books[index].name<<endl;
        library.books[index].availability=false;
    }
    else {
        cout<<"Sorry "<<library.books[index].name<<" is not available."<<endl;
    }
}

int main() {
    Library l;
    int n;
    cin>>n;
    string name, author;
    bool availability;
    for(int i=0;i<n;i++){
        cin>>name>>author>>availability;
        Book b=Book(name, author, availability);
        l.addBook(b);
    }
    l.print();
    LibraryMember m("Ana", 11124);
    int index;
    cin>>index;
    checkOutBook(m, l, index);
    return 0;
}