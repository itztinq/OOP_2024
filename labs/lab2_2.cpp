#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class SpaceObject{
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    SpaceObject(){}
    SpaceObject(char *n, char *t, int d){
        strcpy(name,n);
        strcpy(type,t);
        distanceFromEarth=d;
    }
    ~SpaceObject(){}

    void print(){
        cout<<name<<"( "<<type<<" )"<<" - distance: "<<distanceFromEarth<<" light years away from Earth"<<endl;
    }
    int getDistanceFromEarth(){
        return distanceFromEarth;
    }
};

class Alien{
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;  //broj na omileni vselenski objekti
    SpaceObject *spaceObjects; //omileni vselenski objekti
public:
    Alien(){}
    Alien(char *n, int a, char *planet, int num, SpaceObject *objects){
        strcpy(name,n);
        strcpy(homePlanet,planet);
        age=a;
        numObj=num;
        spaceObjects=new SpaceObject[num];
        for(int i=0;i<num;i++){
            spaceObjects[i]=objects[i];
        }
    }
    Alien(const Alien &a){
        strcpy(name,a.name);
        strcpy(homePlanet,a.homePlanet);
        age=a.age;
        numObj=a.numObj;
        spaceObjects=new SpaceObject[numObj];
        for(int i=0;i<numObj;i++){
            spaceObjects[i]=a.spaceObjects[i];
        }
    }
    ~Alien(){
        delete[] spaceObjects;
    }

    SpaceObject getObjectClosestToEarth(){
        SpaceObject closest=spaceObjects[0];
        for(int i=1;i<numObj;i++){
            if(spaceObjects[i].getDistanceFromEarth()<closest.getDistanceFromEarth()){
                closest=spaceObjects[i];
            }
        }
        return closest;
    }
    void print(){
        cout<<"Alien name: "<<name<<endl;
        cout<<"Alien age: "<<age<<endl;
        cout<<"Alien homePlanet: "<<homePlanet<<endl;
        cout<<"Favourite space object closest to earth: ";
        getObjectClosestToEarth().print();
    }
};

int main()
{
    char name[100], homePlanet[100];
    int age, numObj;
    cin>>name>>age>>homePlanet>>numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for(int i=0; i<numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin>>spaceObjectName>>spaceObjectType>>distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i]=SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien=Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}