#include<iostream>
#include<cstring>
using namespace std;

class Hero{
protected:
    string name;
    float attackDamage;
    float attackSpeed;
    float abilityPower;
public:
    Hero(string name="", float attackDamage=0, float attackSpeed=0, float abilityPower=0){
        this->name=name;
        this->attackDamage=attackDamage;
        this->attackSpeed=attackSpeed;
        this->abilityPower=abilityPower;
    }
    virtual void displayInfo()=0;
    virtual float power()=0;
};

class LegendaryHero: virtual public Hero{
private:
    int hiddenPowers;
public:
    LegendaryHero(string name="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, int hiddenPowers=0)
    : Hero(name, attackDamage, attackSpeed, abilityPower){
        this->hiddenPowers=hiddenPowers;
    }
    float power(){
        return (0.4*attackDamage*hiddenPowers)+(0.25*attackSpeed*hiddenPowers)+(0.35*abilityPower*hiddenPowers);
    }
    void displayInfo(){
        cout<<"LegendaryHero: "<<name<<endl;
        cout<<"Number of hidden powers: "<<hiddenPowers<<endl;
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

class SuperHero: virtual public Hero{
private:
    bool isShapeshifter;
public:
    SuperHero(string name="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, bool isShapeshifter=0)
            : Hero(name, attackDamage, attackSpeed, abilityPower){
        this->isShapeshifter=isShapeshifter;
    }
    float power(){
        if(!isShapeshifter){
            return attackDamage+attackSpeed+abilityPower;
        }else if(isShapeshifter){
            return (attackDamage+attackSpeed+abilityPower)*2;
        }
    }
    void displayInfo(){
        cout<<"SuperHero: "<<name<<endl;
        cout<<"Shapeshifter: "<<isShapeshifter<<endl;
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

class LegendarySuperHero: public LegendaryHero, public SuperHero{
public:
    LegendarySuperHero(string name="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, int hiddenPowers=0, bool isShapeshifter=0)
    : Hero(name, attackDamage, attackSpeed, abilityPower), LegendaryHero(name, attackDamage, attackSpeed, abilityPower, hiddenPowers), SuperHero(name, attackDamage, attackSpeed, abilityPower, isShapeshifter){}
    float power(){
        return (LegendaryHero::power()+SuperHero::power())/2;
    }
    void displayInfo(){
        cout<<"LegendarySuperHero: "<<name<<endl;
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

Hero *mostPowerfulLegendaryHero(Hero **heroes, int n){
    Hero *mostPowerful= nullptr;
    float maxPower=-1;
    for(int i=0;i<n;i++){
        if(dynamic_cast<LegendaryHero*>(heroes[i])){
            float currentPower=heroes[i]->power();
            if(currentPower>maxPower){
                mostPowerful=heroes[i];
                maxPower=currentPower;
            }
        }
    }
    return mostPowerful;
}

