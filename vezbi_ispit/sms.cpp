#include<iostream>
#include<cstring>
using namespace std;

class SMS {
protected:
	char tel[13];
	float cena;
public:
	SMS (char *tel = "", float cena = 0) {
		strcpy(this->tel, tel);
		this->cena = cena;
	}

	virtual float SMS_cena() const = 0;

	virtual ~SMS() {}

	friend ostream &operator << (ostream &o, const SMS &sms) {
		return o<<"Tel: "<<sms.tel<<" - cena: "<<sms.cena<<"den."<<endl;
	}
};

class RegularSMS : public SMS {
private:
	char msg[1001];
	bool roam;
	static int rProcent;
public:
	RegularSMS (char *tel = "", float cena = 0, char *msg = "", bool roam = false)
		: SMS(tel, cena) {
		strcpy(this->msg, msg);
		this->roam = roam;
	}

	static void set_rProcent(int procent) {
		rProcent = procent;
	}

	int brojPoraki() const {
		int dolz = strlen(msg);
		int poraki = dolz / 160;
		if(dolz % 160 != 0) {
			poraki += 1;
		}
		return poraki;
	}

	float SMS_cena() const override {
		int poraki = brojPoraki();
		float total = cena;

		if(roam) {
			total += cena * rProcent / 100.0;
		} else {
			total += cena * 0.18; //18%
		}
		return total * poraki;
	}


	friend ostream& operator << (ostream &o, const RegularSMS &r) {
		return o<<(SMS&)r<<" - cena: "<<r.SMS_cena()<<"den."<<endl;
	}
};

int RegularSMS::rProcent = 300;

class SpecialSMS : public SMS {
private:
	bool hum;
	static int sProcent;
public:
	SpecialSMS (char *tel = "", float cena = 0, bool hum = false)
		: SMS(tel, cena) {
		this->hum = hum;
	}

	static void set_sProcent(int procent) {
		sProcent = procent;
	}

	float SMS_cena() const override {
		float total = cena;
		if(!hum) {
			total += cena * sProcent / 100;
		}

		return total;
	}

	friend ostream& operator << (ostream &o, const SpecialSMS &s) {
		return o<<(SMS&)s<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
	}
};
int SpecialSMS::sProcent = 150;

void vkupno_SMS(SMS **poraka, int n) {
	int regularni = 0, specialni = 0;
	float cenaRegularni = 0, cenaSpecialni = 0;

	for(int i = 0; i < n; i++) {
		RegularSMS *rsms = dynamic_cast<RegularSMS *>(poraka[i]);
		SpecialSMS *ssms = dynamic_cast<SpecialSMS *>(poraka[i]);

		if(rsms) {
			regularni++;
			cenaRegularni += rsms->SMS_cena();
		} else if(ssms) {
			specialni++;
			cenaSpecialni += ssms->SMS_cena();
		}
	}

	cout<<"Vkupno ima "<<regularni<<" regularni SMS poraki i nivnata cena e: "<<cenaRegularni<<endl;
	cout<<"Vkupno ima "<<specialni<<" specijalni SMS poraki i nivnata cena e: "<<cenaSpecialni<<endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}