#include<iostream>
#include<cstring>
using namespace std;

class Library {
protected:
    string name;
    string city;
    float baseMembership;
    bool weekend;
public:
    Library(string name = "", string city = "", float baseMembership = 0, bool weekend = false) {
        this->name = name;
        this->city = city;
        this->baseMembership = baseMembership;
        this->weekend = weekend;
    }

    bool getWeekends() {
        return weekend;
    }

    virtual void printDetail() = 0;

    virtual double calculateMembershipCardCost() = 0;
};

class  AcademicLibrary : public Library {
private:
    bool opportunities;
    int collections;
public:
    AcademicLibrary (string name = "", string city = "", float baseMembership = 0, bool weekend = false, bool opportunities = false, int collections = 0)
        : Library(name, city, baseMembership, weekend) {
        this->opportunities = opportunities;
        this->collections = collections;
    }

    double calculateMembershipCardCost() override {
        if(opportunities) {
            baseMembership *= 1.24;
        }
       baseMembership += collections * 6;
        return baseMembership;
    }

    void printDetail() override {
        cout<<name<<" - (Academic) "<<city<<" "<<collections<<" "<<calculateMembershipCardCost()<<endl;
    }
};

class NationalLibrary : public Library {
private:
    bool educationalPrograms;
    int originalManuscripts;
public:
    NationalLibrary (string name = "", string city = "", float baseMembership = 0, bool weekend = false, bool educationalPrograms = false, int originalManuscripts = 0)
        : Library(name, city, baseMembership, weekend) {
        this->educationalPrograms = educationalPrograms;
        this->originalManuscripts = originalManuscripts;
    }

    double calculateMembershipCardCost() override {
        if(educationalPrograms) {
            baseMembership *= 0.93;
        }
        baseMembership += originalManuscripts * 15;
        return baseMembership;
    }

    void printDetail() override {
        cout<<name<<" - (National) "<<city<<" "<<originalManuscripts<<" "<<calculateMembershipCardCost()<<endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int maxIndex = -1;
    float maxFee = -1;

    for(int i = 0; i < n; i++) {
       NationalLibrary *nl = dynamic_cast<NationalLibrary *>(l[i]);
        if(nl != NULL) {
            float fee = nl->calculateMembershipCardCost();

            if(fee > maxFee || fee == maxFee && nl->getWeekends()) {
                maxFee = fee;
                maxIndex = i;
            }
        }
    }

    return maxIndex;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}