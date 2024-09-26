#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Country{
private:
    char name[100];
    char capital[100];
    float area;
    float population;
public:
    Country(){}
    Country(char *n, char *c, float a, float p){
        strcpy(name,n);
        strcpy(capital,c);
        area=a;
        population=p;
    }
    ~Country(){}

    void setName(char *name)
    {
        strcpy(this->name,name);
    }
    void setCapital(char *capital)
    {
        strcpy(this->capital,capital);
    }
    void setArea(float area)
    {
        this->area=area;
    }
    void setPopulation(float population)
    {
        this->population=population;
    }
    char *getName(){
        return name;
    }
    char *getCapital(){
        return capital;
    }
    float getArea()
    {
        return area;
    }
    float getPopulation()
    {
        return population;
    }

    void display(){
        cout<<"Country: "<<name<<endl;
        cout<<"Capital: "<<capital<<endl;
        cout<<"Area: "<<area<<endl;
        cout<<"Population: "<<population<<endl;
    }
};

void sortCountries(Country *countries, int n){
    for(int i=0;i<n;i++){
        for(int j=0;i<n-i-1;j++){
            if(countries[j].getArea()>countries[j+1].getArea()){
                Country temp=countries[j];
                countries[j]=countries[j+1];
                countries[j+1]=temp;
            }
        }
    }
}

int main(){

}