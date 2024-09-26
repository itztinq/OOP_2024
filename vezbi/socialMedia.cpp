#include<iostream>
#include<cstring>
using namespace std;

class User {
private:
    char *username;
    char *companyName;
    int position;
public:
    User(char *username=0, char *companyName=0, int position=0) {
        this->username=new char[strlen(username)+1];
        strcpy(this->username, username);
        this->companyName=new char[strlen(companyName)+1];
        strcpy(this->companyName, companyName);
        this->position=position;
    }

    User(const User &u) {
        this->username=new char[strlen(u.username)+1];
        strcpy(this->username, u.username);
        this->companyName=new char[strlen(companyName)+1];
        strcpy(this->companyName, u.companyName);
        this->position=u.position;
    }

    User &operator=(const User &u) {
        if(this!=&u) {
            delete[] username;
            delete[] companyName;
            this->username=new char[strlen(u.username)+1];
            strcpy(this->username, u.username);
            this->companyName=new char[strlen(companyName)+1];
            strcpy(this->companyName, u.companyName);
            this->position=u.position;
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] companyName;
    }

    char *getUsername() {
        return username;
    }
    char *getCompanyName() {
        return companyName;
    }
    int getPosition() {
        return position;
    }

    void setUsername(char *username) {
        delete[] this->username;
        this->username=new char[strlen(username)+1];
        strcpy(this->username, username);
    }
    void setCompanyName(char *companyName) {
        delete[] this->companyName;
        this->companyName=new char[strlen(companyName)+1];
        strcpy(this->companyName, companyName);
    }
    void setPosition(int position) {
        this->position=position;
    }

    friend ostream &operator<<(ostream &o, const User &u) {
        o<<"Username: "<<u.username<<" Company name: "<<u.companyName<<" Position: "<<u.position<<endl;
        return o;
    }

    friend istream &operator>>(istream &i, User &u) {
        i>>ws;
        return i>>u.username>>u.companyName>>u.position;
    }

    bool operator==(User &u) {
        return strcmp(this->username, u.username)==0;
    }
};

class Group {
protected:
    string name;
    User *users;
    int n;
public:
    Group(string name="", User *users=0, int n=0) {
        this->name=name;
        this->n=0;
        this->users=new User[0];
    }

    Group(const Group &g) {
        this->name=g.name;
        this->n=g.n;
        this->users=new User[n];
        for(int i=0;i<n;i++){
            this->users[i]=g.users[i];
        }
    }

    virtual ~Group() {
        delete [] users;
    }

    Group &operator=(const Group &g) {
        if(this!=&g) {
            delete[] users;
            this->name=g.name;
            this->n=g.n;
            this->users=new User[n];
            for(int i=0;i<n;i++){
                this->users[i]=g.users[i];
            }
        }
        return *this;
    }

    virtual void addMember(User & u) {
        for(int i=0;i<n;i++) {
            if(users[i]==u) {
                return;
            }
        }
        User *tmp=new User[n+1];
        for(int i=0;i<n;i++) {
            tmp[i]=users[i];
        }
        tmp[n]=u;
        n++;
        delete[] users;
        users=tmp;
    }

    double averagePositions() const {
        double sum=0;
        for(int i=0;i<n;i++) {
            sum+=users[i].getPosition();
        }
        return sum/n;
    }

    virtual double rating() const {
        //(10 - average level of the members' positions) * number of members / 100
        return (10.0 - averagePositions())*n/100.0;
    }

    friend ostream &operator<<(ostream &o, const Group &g) {
        o<<"Group: "<<g.name<<endl;
        o<<"Members: "<<g.users<<endl;
        o<<"Rating: "<<g.rating()<<endl;
        o<<"Members list: "<<endl;
        for(int i=0;i<g.n;i++) {
            o<<i+1<<". "<<g.users[i]<<endl;
        }
        return o;
    }

};

class PrivateGroup : public Group {
private:
    static int capacity;
    const static double coef;
public:
    PrivateGroup(string name="", User *users=0, int n=0)
    : Group(name, users, n) {}

    void addMember(User & u) override {
        if(n==capacity){
            return;
        }
        Group::addMember(u);
    }

    double rating() const override {
        //(10 - average level of the positions of the members) * (number of members / group capacity) * private group coefficient
        return (10-averagePositions())*((double)n/capacity)*coef;
    }

    static void setCapacity(int c) {
        capacity=c;
    }

};
int PrivateGroup::capacity=10;
const double PrivateGroup::coef=0.8;

int main() {
    cout << "INTEGRATION TEST" << endl;
    char name[50];
    int nGroups;
    cin >> nGroups;
    Group **groups = new Group *[nGroups];
    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type;
        cin >> name;
        if (type == 1) { //normal group
            groups[i] = new Group(name);
        } else { //private group
            groups[i] = new PrivateGroup(name);
        }
        int nUsers;
        cin >> nUsers;
        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;

            groups[i]->addMember(u);

        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }

    PrivateGroup::setCapacity(15);
    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
}