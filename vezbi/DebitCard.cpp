#include<iostream>
#include<cstring>
using namespace std;

class DebitCard {
protected:
    string holder;
    string id;
    double balance;
public:
    DebitCard(string holder="", string id="", double balance=0.0) {
        this->holder=holder;
        this->id=id;
        this->balance=balance;
    }

    friend ostream &operator<<(ostream &o, const DebitCard &d) {
        o<<"Holder: "<<d.holder<<" ID: "<<d.id<<" Balance: "<<d.balance;
        return o;
    }

    void deposit(double amount) {
        balance+=amount;
    }

    virtual void withdraw(double amount) {
        if(amount<=balance) {
            balance-=amount;
        } else {
            cout<<"Insufficient balance!"<<endl;
        }
    }
};

class CreditCard : public DebitCard {
private:
    double limit;
    static double interest;
public:
    CreditCard(string holder="", string id="", double balance=0.0, double limit=0.0)
    : DebitCard(holder, id, balance) {
        this->limit=limit;
    }

    friend ostream &operator<<(ostream &o, const CreditCard &c) {
        o<<static_cast<const DebitCard &>(c)<<" limit: "<<c.limit;
        return o;
    }

    void withdraw(double amount) {
        double positive=0;
        double negative=0;

        if(balance>0) {
            if(amount>balance) {
                positive=balance;
                negative=amount-balance;
            } else {
                positive=balance;
                negative=0;
            }
        } else {
            positive=0;
            negative=amount;
        }

        negative*=(1+interest);
        if((balance-positive-negative)>=limit) {
            balance-=positive;
            balance-=negative;
        } else {
            cout<<"Insufficient amount!"<<endl;
        }
    }
};
double CreditCard::interest=0.05;

int main() {
    CreditCard cc("Ana", "12341234", 1000, -40000);
    cout<<cc<<endl;

    cc.withdraw(5000);
    cout<<cc<<endl;

    cc.withdraw(1000);
    cout<<cc<<endl;

    cc.deposit(500);
    cout<<cc<<endl;

    cc.withdraw(30000);
    cout<<cc<<endl;

    cc.withdraw(30000);
    cout<<cc<<endl;

    return 0;
}