#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

enum tip {
	mobilen, laptop
};

class Device {
private:
	char model[100];
	tip tipDevice;
	static float pocetniCasovi;
	int godina;
public:
	Device (char *model = "", tip tipDevice = mobilen, int godina = 0) {
		strcpy (this->model, model);
		this->tipDevice = tipDevice;
		this->godina = godina;
	}

	static void setPocetniCasovi (float casovi) {
		pocetniCasovi = casovi;
	}

	float totalCasoviProverka() const {
		float casovi = pocetniCasovi;
		if(godina > 2015) {
			if(tipDevice == laptop) {
				casovi += 2.0;
			} else {
				casovi += 1.5;
			}
		} else if(tipDevice == laptop) {
			casovi += 2.0;
		}

		return round(casovi);
	}

	int getGodina() const {
		return godina;
	}

	friend ostream &operator << (ostream &o, const Device &d) {
		o<<d.model<<endl;
		switch(d.tipDevice) {
			case 0: o<<"Mobilen "; break;
			case 1: o<<"Laptop "; break;
		}
		o<<d.totalCasoviProverka();
		return o;
	}
};

float Device::pocetniCasovi = 1;

class InvalidProductionDate {
public:
	void message() {
		cout<<"Невалидна година на производство"<<endl;
	}
};

class MobileServis {
private:
	char ime[100];
	Device *devices;
	int n;
public:
	MobileServis (char *ime = "") {
		strcpy(this->ime, ime);
		devices = nullptr;
		n = 0;
	}

	MobileServis (const MobileServis &m) {
		strcpy(this->ime, m.ime);
		this->n = m.n;
		this->devices = new Device [n+1];
		for (int i = 0; i < n; i++) {
			this->devices[i] = m.devices[i];
		}
	}

	MobileServis &operator = (const MobileServis &m) {
		if(this != &m) {
			delete [] devices;
			strcpy(this->ime, m.ime);
			this->n = m.n;
			this->devices = new Device [n];
			for (int i = 0; i < n; i++) {
				this->devices[i] = m.devices[i];
			}
		}
		return *this;
	}

	~MobileServis() {
		delete [] devices;
	}

	MobileServis &operator += (const Device &d) {
		if(d.getGodina() < 2000 || d.getGodina() > 2019) {
			throw InvalidProductionDate();
		}

		Device *tmp = new Device [n+1];
		for (int i = 0; i < n; i++) {
			tmp[i] = devices[i];
		}
		tmp[n++] = d;
		delete [] devices;
		devices = tmp;
		return *this;
	}

	void pecatiCasovi() {
		cout<<"Ime: "<<ime<<endl;
		for(int i = 0; i < n; i++) {
			cout << devices[i]<<endl;
		}
	}
};

int main() {
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try {
	            t+=tmp;
            } catch (InvalidProductionDate &e) {
	            e.message();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
			try {
				t+=tmp;
			} catch (InvalidProductionDate &e) {
				e.message();
			}
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
			try {
				t+=tmp;
			} catch (InvalidProductionDate &e) {
				e.message();
			}
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

			try {
				t+=tmp;
			} catch (InvalidProductionDate &e) {
				e.message();
			}
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
			try {
				t+=tmp;
			} catch (InvalidProductionDate &e) {
				e.message();
			}
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}