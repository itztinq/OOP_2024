#include<iostream>
#include<cstring>
using namespace std;

class Trud {
private:
    char tip;
    int godina;
public:
    Trud (char tip = 'C', int godina = 0) {
        this->tip = tip;
        this->godina = godina;
    }

    int getGodina() const {
        return godina;
    }

    char getTip() const {
        return tip;
    }

	friend istream& operator >> (istream &i, Trud &t) {
	    return i>>t.tip>>t.godina;
    }
};

class Student {
protected:
    char ime[30];
    int indeks;
    int godinaUpis;
    int n;
    int oceni[30];
public:
    Student (char *ime = "", int indeks = 0, int godinaUpis = 0, int *oceni = 0, int n = 0) {
        strcpy(this->ime, ime);
        this->indeks = indeks;
        this->godinaUpis = godinaUpis;
        this->n = n;
        for(int i = 0; i < n; i++) {
            this->oceni[i] = oceni[i];
        }
    }

    Student (const Student &s) {
        strcpy(this->ime, s.ime);
        this->indeks = s.indeks;
        this->godinaUpis = s.godinaUpis;
        this->n = s.n;
        for(int i = 0; i < s.n; i++) {
            this->oceni[i] = s.oceni[i];
        }
    }

    virtual double rang() const {
        double sum = 0;
        for(int i = 0; i < n; i++) {
            sum += oceni[i];
        }
        if(n <= 0) return 5.0;
        return sum / n;
    }

    friend ostream &operator << (ostream &o, const Student &s) {
        return o<<s.indeks<<" "<<s.ime<<" "<<s.godinaUpis<<" "<<s.rang()<<endl;
    }

	int getIndeks() {
	    return indeks;
    }

	char *getIme() {
	    return ime;
    }

	int getUpis() {
	    return godinaUpis;
    }

	double getRang() {
	    return rang();
    }
};

class Exception {
private:
	Student *s;
public:
	Exception(Student *s) {
		this->s = s;
	}
    void message() {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
		cout<<s->getIndeks()<<" "<<s->getIme()<<" "<<s->getUpis()<<" "<<s->getRang()<<endl;
    }
};

class PhDStudent : public Student {
private:
    Trud *trudovi;
    int nTrudovi;
    static int konferenciski;
    static int spisanie;
public:
    PhDStudent (char *ime = "", int indeks = 0, int godinaUpis = 0, int *oceni = 0, int n = 0, Trud *trudovi = 0, int nTrudovi = 0)
        : Student(ime, indeks, godinaUpis, oceni, n) {
        this->nTrudovi = nTrudovi;
        this->trudovi = new Trud[nTrudovi+1];
        for(int i = 0; i < nTrudovi; i++) {
            if(trudovi[i].getGodina() < godinaUpis) {
                throw Exception(this);
            }
            this->trudovi[i] = trudovi[i];
        }
    }

    PhDStudent &operator += (const Trud &t) {
        if(t.getGodina() < godinaUpis) {
            throw Exception(this);
        }

        Trud *tmp = new Trud[nTrudovi+1];
        for(int i = 0; i < nTrudovi; i++) {
            tmp[i] = trudovi[i];
        }
        tmp[nTrudovi++] = t;
        delete [] trudovi;
        trudovi = tmp;
        return *this;
    }

    ~PhDStudent () {
        delete [] trudovi;
    }

    double rang() const override {
        double rang = Student::rang();
        double poeni = 0;
        for(int i = 0; i < nTrudovi; i++) {
            if(trudovi[i].getTip() == 'c') {
                poeni += konferenciski;
            } else if(trudovi[i].getTip() == 'j') {
                poeni += spisanie;
            }
        }
    	if(nTrudovi > 0) {
    		return rang + poeni;
    	}
    }

	static void setPoeni(int konf, int spis) {
	    konferenciski = konf;
    	spisanie = spis;
    }
};

int PhDStudent::konferenciski = 1;
int PhDStudent::spisanie = 3;

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		try {
			PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
			cout << phd;
		}
		catch (Exception &e) {
			e.message();
		}
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

		for(int i = 0; i < m; i++) {
			PhDStudent *phd = dynamic_cast<PhDStudent*>(niza[i]);
			if(phd && phd->getIndeks() == indeks) {
				try {
					*phd += t;
				} catch (Exception &e) {
					e.message();
				}
			}
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

		for(int i = 0; i < m; i++) {
			PhDStudent *phd = dynamic_cast<PhDStudent*>(niza[i]);
			if(phd && phd->getIndeks() == indeks) {
				try {
					*phd += t;
				} catch (Exception &e) {
					e.message();
				}
			}
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		try {
			PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
			cout << phd;
		} catch (Exception &e) {
			e.message();
		}
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		for(int i = 0; i < m; i++) {
			PhDStudent *phd = dynamic_cast<PhDStudent*>(niza[i]);
			if(phd && phd->getIndeks() == indeks) {
				try {
					*phd += t;
				} catch (Exception &e) {
					e.message();
				}
			}
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

		PhDStudent::setPoeni(conf, journal);

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}