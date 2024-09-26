#include<iostream>
#include<cstring>
using namespace std;

class Library {
protected:
    string name;
    string city;
    double baseMembership;
    bool weekends;
public:
    Library(string name="", string city="", double baseMembership=0.0, bool weekends=true) {
        this->name=name;
        this->city=city;
        this->baseMembership=baseMembership;
        this->weekends=weekends;
    }
    virtual void printDetail()=0;
    virtual double calculateMembershipCardCost()=0;

    bool getWeekends() {
        return weekends;
    }
};

class AcademicLibrary : public Library {
private:
    bool openOpportunities;
    int specializedCollections;
public:
    AcademicLibrary(string name="", string city="", double baseMembership=0.0, bool weekends=true, bool openOpportunities=true, int specializedCollections=0)
    : Library(name, city, baseMembership, weekends) {
        this->openOpportunities=openOpportunities;
        this->specializedCollections=specializedCollections;
    }

    double calculateMembershipCardCost() {
        double fee=baseMembership;
        if(openOpportunities==1) {
            fee*=1.24; // increase by 24%
        }
        fee+=specializedCollections*6;
        return fee;
    }

    void printDetail() {
        //[Library Name] - (Academic) [City] [Number of specialized collections] [Membership fee]
        cout<<name<<" - (Academic) "<<city<<" "<<specializedCollections<<" "<<calculateMembershipCardCost()<<endl;

    }
};

class NationalLibrary : public Library {
private:
    bool educationalPrograms;
    int preservedManuscripts;
public:
    NationalLibrary(string name="", string city="", double baseMembership=0.0, bool weekends=true, bool educationalPrograms=true, int preservedManuscripts=0)
    : Library(name, city, baseMembership, weekends) {
        this->educationalPrograms=educationalPrograms;
        this->preservedManuscripts=preservedManuscripts;
    }

    double calculateMembershipCardCost() {
        double fee=baseMembership;
        if(educationalPrograms==1) {
            fee*=0.93; // decreases by 7%
        }
        fee+=preservedManuscripts*15;
        return fee;
    }

    void printDetail() {
        // [Library Name] - (National) [City] [Number of manuscripts] [Membership fee]
        cout<<name<<" - (National) "<<city<<" "<<preservedManuscripts<<" "<<calculateMembershipCardCost()<<endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index=-1;
    double highestFee=-1.0;
    for(int i=0;i<n;i++) {
        NationalLibrary *nl=dynamic_cast<NationalLibrary*>(l[i]);
        if(nl != nullptr) {
            double fee=nl->calculateMembershipCardCost();
            if(fee>highestFee || (fee==highestFee && nl->getWeekends())) {
                highestFee=fee;
                index=i;
            }
        }
    }
    return index;
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