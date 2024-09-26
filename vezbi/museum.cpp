#include<iostream>
#include<cstring>
using namespace std;

class Museum {
protected:
    string name;
    string city;
    double ticketPrice;
    int workingHours;
public:
    Museum(string name="", string city="", double ticketPrice=0.0, int workingHours=0) {
        this->name=name;
        this->city=city;
        this->ticketPrice=ticketPrice;
        this->workingHours=workingHours;
    }

    virtual void printDetail()=0;
    virtual double calculateTicketCost()=0;

    int getWorkingHours() {
        return workingHours;
    }
};

class ScientificMuseum : public Museum {
private:
    bool interactiveExhibits;
    int presentations;
public:
    ScientificMuseum(string name="", string city="", double ticketPrice=0.0, int workingHours=0, bool interactiveExhibits=true, int presentations=0)
    : Museum(name, city, ticketPrice, workingHours) {
        this->interactiveExhibits=interactiveExhibits;
        this->presentations=presentations;
    }

    double calculateTicketCost() {
        double price=ticketPrice;
        if(interactiveExhibits) {
            price*=1.12; // increas 12%
        }
        price+=presentations*6;
        return price;
    }

    void printDetail() {
        // [Museum Name] - (Scientific) [City] [Number of multimedia presentations] [Ticket price]
        cout<<name<<" - (Scientific) "<<city<<" "<<presentations<<" "<<calculateTicketCost()<<endl;
    }
};

class ArtMuseum : public Museum {
private:
    bool amateurExhibitions;
    int originalArtworks;
public:
    ArtMuseum(string name="", string city="", double ticketPrice=0.0, int workingHours=0, bool amateurExhibitions=true, int originalArtworks=0)
    : Museum(name, city, ticketPrice, workingHours) {
        this->amateurExhibitions=amateurExhibitions;
        this->originalArtworks=originalArtworks;
    }

    double calculateTicketCost() {
        double price=ticketPrice;
        if(amateurExhibitions) {
            price*=0.82; // decrease 18%
        }
        price+=originalArtworks*3;
        return price;
    }

    void printDetail() {
        // [Museum Name] - (Scientific) [City] [Number of multimedia presentations] [Ticket price]
        cout<<name<<" - (Art) "<<city<<" "<<amateurExhibitions<<" "<<calculateTicketCost()<<endl;
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index=-1;
    double cheapestTicket;
    int mostHours=0;
    bool first=false;

    for(int i=0;i<n;i++) {
        Museum *sm=dynamic_cast<ScientificMuseum*>(m[i]);
        if(sm!=nullptr) {
            double price=sm->calculateTicketCost();
            int hours=sm->getWorkingHours();
            if(!first) {
                cheapestTicket=price;
                mostHours=hours;
                index=i;
                first=true;
            }else if(price<cheapestTicket || (price==cheapestTicket && hours>mostHours)){
                cheapestTicket=price;
                mostHours=hours;
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

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}