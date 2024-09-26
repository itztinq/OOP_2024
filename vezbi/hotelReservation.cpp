#include<iostream>
#include<cstring>
using namespace std;

class HotelReservation {
protected:
    int days;
    int people;
    string name;
    static int price_perPerson_perDay;
public:
    HotelReservation(string name="", int days=0, int people=0) {
        this->name=name;
        this->days=days;
        this->people=people;
    }

    virtual int price() {
        return days*people*price_perPerson_perDay;
    }

    int price(int amount) {
        if(amount>=price()) {
            return amount-price();
        }
        return -1;
    }

    virtual void print() {
        cout<<"Regular hotel teservation for: "<<name<<" "<<days<<" "<<people<<" "<<price()<<endl;
    }
};
int HotelReservation::price_perPerson_perDay=25; //euro

class HalfBoardHotelReservation : public HotelReservation {
private:
    static int price_perBreakfast;
public:
    HalfBoardHotelReservation(string name="", int days=0, int people=0)
    : HotelReservation(name, days, people) {}

    int price() {
        return HotelReservation::price()+(days*people*price_perBreakfast);
    }

    void print() {
        cout<<"Half board hotel reservation for: "<<name<<" "<<days<<" "<<people<<" "<<price()<<endl;
    }

};
int HalfBoardHotelReservation::price_perBreakfast=5; //euro

class Hotel {
private:
    string name;
    int income;
public:
    Hotel(string name="", int income=0.0) {
        this->name=name;
        this->income=income;
    }

    int pay(HotelReservation &hr, int amount) {
        int tmp=hr.price(amount);
        if(tmp>-1) {
            income+=hr.price();
        }
        return tmp;
    }

    void print() {
        cout<<"Hotel: "<<name<<" Income: "<<income<<endl;
    }
};

int main() {
    HotelReservation *hr1=new HotelReservation("Lila", 7, 4);
    HotelReservation *hr2=new HalfBoardHotelReservation("Lila", 6, 4);
    hr1->price();
    hr2->print();

    Hotel hotel("Hilton");
    cout<<hotel.pay(*hr1, 1000)<<endl;
    cout<<hotel.pay(*hr2,900)<<endl;
    hotel.print();

    return 0;
}