#include<iostream>
#include<cstring>
using namespace std;

class Vehicle {
private:
    Vehicle(int i) {

    }

    char id[8];
    char *driver;
    int location;
    int maxPassengers;
    double km;
public:
    Vehicle(char *id="", char *driver="", int location=0, int maxPassengers=0) {
        strcpy(this->id, id);
        this->driver=new char[strlen(driver)+1];
        strcpy(this->driver, driver);
        this->location=location;
        this->maxPassengers=maxPassengers;
        this->km=0;
    }
    Vehicle(const Vehicle &v) {
        strcpy(this->id, v.id);
        this->driver=new char[strlen(v.driver)+1];
        strcpy(this->driver, v.driver);
        this->location=v.location;
        this->maxPassengers=v.maxPassengers;
        this->km=v.km;
    }
    ~Vehicle() {
        delete[] driver;
    }

    Vehicle &operator=(const Vehicle &v) {
        if(this!=&v) {
            delete[] driver;
            strcpy(this->id, v.id);
            this->driver=new char[strlen(v.driver)+1];
            strcpy(this->driver, v.driver);
            this->location=v.location;
            this->maxPassengers=v.maxPassengers;
            this->km=v.km;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Vehicle &v) {
        return o<<"ID: "<<v.id<<", Driver: "<<v.driver<<", Location: "<<v.location<<", Passenger capacity: "<<v.maxPassengers<<", kms driven: "<<v.km<<endl;
    }

    bool operator==(const Vehicle &v) {
        return strcmp(this->id, v.id)==0;
    }

    Vehicle &operator+=(const Vehicle &v) {
        this->km=v.km;
        return *this;
    }

    int distance(int area){
        return abs(this->location-area);
    }

    friend class RideApp;
};

class RideApp {
private:
    char appName[20];
    Vehicle *vehicles;
    int n;
public:
    RideApp(char *appName="") {
        strcpy(this->appName, appName);
        this->n=0;
        vehicles=new Vehicle[0];
    }
    RideApp(const RideApp &a) {
        strcpy(this->appName, a.appName);
        this->n=a.n;
        vehicles=new Vehicle[this->n];
        for(int i=0;i<n;i++) {
            this->vehicles[i]=a.vehicles[i];
        }
    }
    ~RideApp() {
        delete[] vehicles;
    }

    RideApp &operator+=(const Vehicle &v) {
        for(int i=0;i<n;i++){
            if(vehicles[i]==v){
                return *this;
            }
        }
        Vehicle *tmp=new Vehicle[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=vehicles[i];
        }
        tmp[n++]=v;
        delete[] vehicles;
        vehicles=tmp;
        return *this;
    }

    void addRide(int area, int passengers, int distanceKm) {
        bool first=true;
        int index=-1;
        int minDistance;
        for(int i=0;i<n;i++) {
            if(vehicles[i].maxPassengers >= passengers) {
                if(first) {
                    first=false;
                    index=i;
                    minDistance=vehicles[i].distance(area);
                } else {
                    if(vehicles[i].distance(area) < minDistance){
                        index=i;
                        minDistance=vehicles[i].distance(area);
                    }
                }
            }
        }
        vehicles[index]+=distanceKm;
        vehicles[index].location=area;
    }

    friend ostream &operator<<(ostream &o, const RideApp &a) {
        o<<a.appName<<endl;
        if(a.n==0) {
            o<<"Empty"<<endl;
        }
        for(int i=0;i<a.n;i++) {
            o<<a.vehicles[i]<<endl;
        }
        return o;
    }

};

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle("NE1234SA", "Stefan", 5, 4);
        cout << vehicle << endl;
        cout << "CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle = Vehicle("NE1234SA", "Stefan", 5, 4);
        cout << vehicle << endl;
        cout << "COPY-CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle" << endl;
        Vehicle vehicle;
        Vehicle vehicle2("NE1234SA", "Stefan", 5, 4);
        vehicle = vehicle2;
        cout << vehicle << endl;
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR RideApp" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        cout << app;
        cout << "CONSTRUCTOR RideApp OK" << endl;
    } else if (testCase == 5) {
        cout << "RideApp signUpVehicle test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[9];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location >> capacity;
            app += Vehicle(ID, name, location, capacity);
        }
        cout << app;
    } else if (testCase == 6) {
        cout << "RideApp addRide test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location >> capacity;
            app += Vehicle(ID, name, location, capacity);
        }
        cin >> n;
        for (int i = 0; i < n; i++) {
            int area, passengers, kms;
            cin >> area >> passengers >> kms;
            app.addRide(area, passengers, kms);
        }

        cout << app;
    }
    return 0;
}