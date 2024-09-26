#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

void wtf() {
    ofstream fout("input.txt");
    string fname;
    string lname;
    int points;
    string line;

    while(getline(cin, line)) {
        if(line=="----") {
            break;
        }
        fout<<line<<endl;
    }
}

void rff1() {
    ifstream fin("output1.txt");
    string line;
    while(getline(fin, line)) {
        cout<<line<<endl;
    }
}

void rff2() {
    ifstream fin("output2.txt");
    string line;
    while(getline(fin, line)) {
        cout<<line<<endl;
    }
}

class Book : public error_code {
private:
    string name;
    string author;
    int year;
public:
    Book(string name="", string author="", int year=1990) {
        this->name=name;
        this->author=author;
        this->year=year;
    }

    bool operator==(const Book &b) const {
        return name==b.name &&
               author==b.author &&
               year==b.year;
    }

    bool operator!=(const Book &b) const {
        return !(b==*this);
    }

    string &getAuthor() {
        return author;
    }
};

class BookAlreadyExistException {
private:
    Book b;
public:
    BookAlreadyExistException(const Book &b) {
        this->b=b;
    }
    void message() {
        cout<<"Book \""<< b <<"\" already exist in the library."<<endl;
    }
};

class Library {
private:
    string name;
    int n;
    Book *books;
public:
    Library(string name="") {
        this->name=name;
        n=0;
        books=new Book[0];
    }

    Library &operator+=(const Book &b) {
        for(int i=0;i<n;i++) {
            if(books[i]==b) {
                throw BookAlreadyExistException(b);
            }
        }

        Book *tmp=new Book[n+1];
        for(int i=0;i<n;i++) {
            tmp[i]=books[i];
        }
        tmp[n]=b;
        n++;
        delete[] books;
        books=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Library &l) {
        o<<l.n<<endl;
        for(int i=0;i<l.n;i++) {
            o<<l.books[i]<<endl;
        }
        return o;
    }

    Book *getBooksByAuthor(string &author, int &numberFound) {
        numberFound=0;
        for(int i=0;i<n;i++) {
            if(books[i].getAuthor()==author) {
                numberFound++;
            }
        }

        Book *result=new Book[numberFound];
        int j=0;
        for(int i=0;i<n;i++) {
            if(books[i].getAuthor()==author) {
                result[j++]=books[i];
            }
        }

        if(numberFound==0) {
            return nullptr;
        } else {
            return result;
        }
    }
};

int main() {
    wtf(); //creating the input.txt file

    //YOUR CODE STARTS HERE

    /*
     * FINKI Library
        5
        To Kill a Mockingbird
        Harper Lee
        1960
        1984
        George Orwell
        1949
        The Great Gatsby
        F. Scott Fitzgerald
        1925
        Pride and Prejudice
        Jane Austen
        1813
        Moby Dick
        Herman Melville
        1851
     **/

    ifstream ifs("input.txt");

    string library;
    getline(ifs, library);
    Library l(library);

    int n;
    ifs>>n;
    ifs.ignore();

    string title, a;
    int year;

    for(int i=0;i<n;i++) {
        getline(ifs, title);
        getline(ifs, a);
        ifs>>year;
        ifs.ignore();

        Book b(title, a, year);
        try {
            l+=b;
        } catch (BookAlreadyExistException &e) {
            e.message();
        }
    }
    ifs.close();

    ofstream ofs1("output1.txt");
    ofs1<<l;
    ofs1.close();

    //DO NOT MODIFY THE NEXT PART

    string author;
    getline(std::cin, author);

    //DO NOT MODIFY THE PART ABOVE, CONTINUE AFTER THIS COMMENT

    ofstream ofs2("ofstream2.txt");
    Book *result=l.getBooksByAuthor(author,n);
    if(result== nullptr) {
        ofs2<<"None";
    } else {
        for(int i=0;i<n;i++) {
            ofs2<<result[i]<<endl;
        }
    }
    ofs2.close();

    //YOUR CODE ENDS HERE
    rff1();
    cout << "Books written by " << author << " are: " << endl;
    rff2();

    return 0;

}