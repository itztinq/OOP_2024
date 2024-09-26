#include<iostream>
#include<cstring>
using namespace std;

class User {
private:
    char *username;
    char *companyName;
    int position;
public:
    User (char *username = "", char *companyName = "", int position = 0) {
        this->username = new char[strlen(username)+1];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName)+1];
        strcpy(this->companyName, companyName);
        this->position = position;
    };

    User (const User &u) {
        this->username = new char[strlen(u.username)+1];
        strcpy(this->username, u.username);
        this->companyName = new char[strlen(u.companyName)+1];
        strcpy(this->companyName, u.companyName);
        this->position = u.position;
    }

    User &operator = (const User &u) {
        if(this != &u) {
            delete [] username;
            delete [] companyName;
            this->username = new char[strlen(u.username)+1];
            strcpy(this->username, u.username);
            this->companyName = new char[strlen(u.companyName)+1];
            strcpy(this->companyName, u.companyName);
            this->position = u.position;
        }
        return *this;
    }

    ~User () {
        delete [] username;
        delete [] companyName;
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
        this->username = new char[strlen(username)+1];
        strcpy(this->username, username);
    }
    void setCompanyName(char *companyName) {
        this->companyName = new char[strlen(companyName)+1];
        strcpy(this->companyName, companyName);
    }
    void setPosition(int position) {
        this->position = position;
    }

    friend ostream &operator << (ostream &o, const User &u) {
        return o<<"Username: "<<u.username
                << " Company name: "<<u.companyName
                << " Position: "<<u.position<<endl;
    }

    friend istream &operator >> (istream &i, User &u) {
        return i>>u.username>>u.companyName>>u.position;
    }

    bool operator == (User &u) {
        return strcmp(this->username, u.username)==0;
    }
};

class OperationNotSupported {
    char message[100];
public:
    OperationNotSupported(char *message = "test") {
        strcpy(this->message, message);
    }
    void showMessage() {
        cout<<message<<endl;
    }
};

class Group {
protected:
    User *users;
    int n;
    char name[50];
public:
    Group (char *name = "test") {
        strcpy(this->name, name);
        this->n = 0;
        users = new User[0];
    }

    Group (const Group &g) {
        strcpy(this->name, g.name);
        this->n = g.n;
        users = new User[n];
        for (int i = 0; i < n; i++) {
            users[i] = g.users[i];
        }
    }

    Group &operator = (const Group &g) {
        if(this != &g) {
            delete [] users;
            strcpy(this->name, g.name);
            this->n = g.n;
            users = new User[n];
            for (int i = 0; i < n; i++) {
                users[i] = g.users[i];
            }
        }
        return *this;
    }

    ~Group () {
        delete [] users;
    }

    virtual void addMember (User &u) {
        for(int i = 0; i < n; i++) {
            if(users[i] == u) {
                throw OperationNotSupported("Username already exists");
            }
        }

        User *tmp = new User[n+1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete [] users;
        users = tmp;
    }

    double avveragePositionOfMembers() const {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += users[i].getPosition();
        }
        if(n==0) {
            return 0;
        }
        return sum/n;
    }

    virtual double rating() const {
        //formula: (10 - просечно_ниво_на_позициите_на_членовите) * број_на_членови / 100
        return (10 - avveragePositionOfMembers()) * n / 100.0;
    }

    friend ostream &operator << (ostream &o, const Group &g) {
        o<<"Group: "<<g.name<<endl;
        o<<"Members: "<<g.n<<endl;
        o<<"Rating: "<<g.rating()<<endl;
        o<<"Members list: "<<endl;
        if(g.n == 0) {
            return o<<"EMPTY"<<endl;
        }
        for (int i = 0; i < g.n; i++) {
            o<<i+1<<". "<<g.users[i]<<endl;
        }
        return o;
    }
};

class PrivateGroup : public Group {
private:
    static int CAPACITY;
    const static double COEF;
public:
    PrivateGroup (char *name = "test") : Group (name) {}

    static void setCapacity(int capacity) {
        CAPACITY = capacity;
    }

    static int getCapacity() {
        return CAPACITY;
    }

    void addMember (User &u) {
        if(this->n == CAPACITY) {
            throw OperationNotSupported("The group’s capacity has been exceeded.");
        }
        Group::addMember(u);
    }

    double rating() const {
        //formula:  (10 - просечно_ниво_на_позициите_на_членовите) * (број_на_членови / капацитет_на_група) * коефициент_за_приватна_група
        return (10 - avveragePositionOfMembers()) * ((double)this->n / CAPACITY) * COEF;
    }

    friend ostream &operator << (ostream &o, const PrivateGroup &pg) {
        cout<<"Private ";
        Group g(pg);
        o<<g;
    }

};

int PrivateGroup::CAPACITY = 10;
const double PrivateGroup::COEF = 0.8;

int main() {
    int testCase;
    cin>>testCase;
    if(testCase == 1) {
        cout<<"TESTING CLASS GROUP: CONSTRUCOR AND OPERATOR <<"<<endl;
        Group g("test");
        cout<<g;
    } else if(testCase == 2) {
        cout<<"TESTING CLASS PRIVATE GROUP: CONSTRUCOR AND OPERATOR <<"<<endl;
        PrivateGroup pg("private test");
        cout<<pg;
    } else if  (testCase == 3) {
        cout<<"TESTING CLASS GROUP: CONSTRUCOR, METHOD ADD_MEMBER AND OPERATOR <<"<<endl;
        Group *g = new Group("FINKI students");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            g->addMember(u);
        }
        cout<<*g;
        delete g;
    } else if(testCase == 4) {
        cout<<"TESTING CLASS PRIVATE GROUP: CONSTRUCOR, METHOD ADD_MEMBER AND OPERATOR <<"<<endl;
        Group *g = new PrivateGroup("FINKI students");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            g->addMember(u);
        }
        cout<<*g;
        delete g;
    } else if(testCase == 5) {
        cout<<"TESTING CLASS GROUP: CONSTRUCOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<"<<endl;
        Group *g = new Group("FINKI students");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported &e) {
                e.showMessage();
            }
        }
        cout<<*g;
        delete g;
    } else if(testCase == 6) {
        cout<<"TESTING CLASS PRIVATE GROUP: CONSTRUCOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<"<<endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.showMessage();
            }
        }
        cout<<*g;
        delete g;
    } else if(testCase == 7) {
        cout<<"TESTING CLASS PRIVATE GROUP: CONSTRUCOR, METHOD ADD_MEMBER AND CHANGE OF ST"<<endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            g->addMember(u);
        }
        cout<<"RATING BEFORE CHANGE"<<endl;
        cout<<g->rating();
        PrivateGroup::setCapacity(20);
        cout<<"RATING AFTER CHANGE"<<endl;
        cout<<g->rating();
        delete g;
    } else if(testCase == 8) {
        cout<<"TESTING CLASS PRIVATE GROUP: CONSTRUCOR, METHOD ADD_MEMBER, EXCEPTION AND CHANGE OF ST"<<endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin>>n;
        for(int i = 0; i < n; i++) {
            User u;
            cin>>u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported &e) {
                int capacity = PrivateGroup::getCapacity();
                cout<<"Increasing capacity from "<<capacity<<" to "<<capacity+1<<endl;
                PrivateGroup::setCapacity(capacity+1);
                g->addMember(u);
                cout<<g->rating()<<endl;
            }
        }
    } else {
        cout<<"INTEGRATION TEST"<<endl;
        char name[50];
        int nGroups;
        cin>>nGroups;
        Group **groups = new Group*[nGroups];
        for(int i = 0; i < nGroups; i++) {
            int type;
            cin>>type;
            cin>>name;
            if(type == 1) { //normal
                groups[i] = new Group(name);
            } else { //private
                groups[i] = new PrivateGroup(name);
            }
            int nUsers;
            cin>>nUsers;
            for(int j = 0; j < nUsers; j++) {
                User u;
                cin>>u;
                try {
                    groups[i]->addMember(u);
                } catch (OperationNotSupported &e) {
                    e.showMessage();
                }
            }
        }
        cout<<"BEFORE CHANGE OF PRIVATE GROUP COEFICIENT"<<endl;
        for(int i = 0; i < nGroups; i++) {
            cout<<*groups[i];
        }
        PrivateGroup::setCapacity(15);
        cout<<"AFTER CHNAGE OF PRIVATE GROUP COEFICIENT"<<endl;
        for(int i = 0; i < nGroups; i++) {
            cout<<*groups[i];
        }
    }

    return 0;
}