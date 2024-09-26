#include<iostream>
#include<cstring>
using namespace std;

class Book {
protected:
	char isbn[20];
	char title[50];
	char author[30];
	double base_price;
public:
	Book (char *isbn = "", char *title = "", char *author = "", double base_price = 0.0) {
		strcpy(this->isbn,isbn);
		strcpy(this->title,title);
		strcpy(this->author,author);
		this->base_price = base_price;
	}

	Book (const Book &b) {
		strcpy(this->isbn,b.isbn);
		strcpy(this->title,b.title);
		strcpy(this->author,b.author);
		this->base_price = b.base_price;
	}

	void setISBN(const char *isbn) {
		strcpy(this->isbn,isbn);
	}

	virtual double bookPrice() = 0;

	bool operator > (Book &b) {
		return bookPrice() > b.bookPrice();
	}

	friend ostream &operator << (ostream &o, Book &b) {
		return o<<b.isbn<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice();
	}

};

class OnlineBook : public Book {
private:
	char *url;
	int size;
public:
	OnlineBook (char *isbn = "", char *title = "", char *author = "", double base_price = 0.0, char *url = "", int size = 0)
		: Book(isbn, title, author, base_price) {
		this->url = new char[strlen(url)+1];
		for (int i = 0; i < strlen(url); i++) {
			this->url[i] = url[i];
		}
		this->size = size;
	}

	OnlineBook (const OnlineBook &ob) : Book(ob) {
		this->url = new char[strlen(ob.url)+1];
		strcpy(this->url, ob.url);
		this->size = ob.size;
	}

	OnlineBook &operator = (const OnlineBook &ob) {
		if (this != &ob) {
			delete [] url;
			Book::operator=(ob);
			this->url = new char[strlen(ob.url)+1];
			strcpy(this->url, ob.url);
		}
		return *this;
	}

	~OnlineBook() {
		delete [] url;
	}

	double bookPrice() override {
		if(size > 20) {
			return base_price * 1.2; //zgolemi za 20%
		}
		return base_price;
	}

	friend ostream &operator << (ostream &o, OnlineBook &ob) {
		return o<<ob.isbn<<": "<<ob.title<<", "<<ob.author<<" "<<ob.bookPrice()<<endl;
	}
};

class PrintBook : public Book {
private:
	double weight;
	bool inStock;
public:
	PrintBook (char *isbn = "", char *title = "", char *author = "", double base_price = 0.0, double weight = 0.0, bool inStock = false)
		: Book(isbn, title, author, base_price) {
		this->weight = weight;
		this->inStock = inStock;
	}

	double bookPrice() {
		if(weight > 0.7) {
			return base_price * 1.15;
		}
		return base_price;
	}

	friend ostream &operator << (ostream &o, PrintBook &pb) {
		return o<<pb.isbn<<": "<<pb.title<<", "<<pb.author<<" "<<pb.bookPrice()<<endl;
	}
};

void mostExpensiveBook (Book **books, int n) {
	int online = 0, print = 0;
	Book *mostExpensive = books[0];

	for (int i = 0; i < n; i++) {
		if(dynamic_cast<OnlineBook *>(books[i])) {
			online++;
		} else if(dynamic_cast<PrintBook *>(books[i])) {
			print++;
		}

		if(*books[i] > *mostExpensive) {
			mostExpensive = books[i];
		}
	}

	cout<<"FINKI-Education"<<endl;
	cout<<"Total number of online books: "<<online<<endl;
	cout<<"Total number of print books: "<<print<<endl;
	cout<<"The most expensive book is: "<<endl;
	cout<<*mostExpensive<<endl;
}

int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i]<<endl;
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0]<<endl;
		else
			cout << *books[1]<<endl;
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i]<<endl;
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0]<<endl;
		else
			cout << *books[1]<<endl;
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
