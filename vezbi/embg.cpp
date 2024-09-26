#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

class EmbgLengthNotValidException {
private:
    string embg;
public:
    EmbgLengthNotValidException(string &embg) {
        this->embg=embg;
    }
    void message() {
        cout<<"EMBG "<<embg<<" must be 13 digits long"<<endl;
    }
};

class EmbgFormatNotValidException {
private:
    string embg;
public:
    EmbgFormatNotValidException(string &embg) {
        this->embg=embg;
    }
    void message() {
        cout<<"EMBG "<<embg<<" must contain only digits"<<endl;
    }
};

class Citizen {
private:
    string name;
    string embg;
public:
    Citizen(string name="", string embg="") {
        if(embg.length()!=13) {
            throw EmbgLengthNotValidException(embg);
        }

        for(int i=0;i<embg.length();i++) {
            if(!isdigit(embg[i])) {
                throw EmbgFormatNotValidException(embg);
            }
        }

        this->name=name;
        this->embg=embg;
    }
};

int main() {
    string name, embg;
    cin>>name>>embg;

    try {
        Citizen c(name, embg);
        cout<<"Citizen created"<<endl;
    }
    catch (EmbgLengthNotValidException &e) {
        e.message();
    }
    catch (EmbgFormatNotValidException &e) {
        e.message();
    }

    return 0;
}