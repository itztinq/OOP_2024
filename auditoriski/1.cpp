//ZADACA 1
#include <iostream>
using namespace std;

struct Date{
    int den;
    int mesec;
    int godina;
};

int razlika(Date d1, Date d2){
    int denovi=0;
    denovi=(d2.godina-d1.godina)*360+(d2.mesec-d1.mesec)*30+(d2.den-d1.den);
    return denovi;
}

int main(){
    Date d1, d2;
    cin>>d1.den>>d1.mesec>>d1.godina;
    cin>>d2.den>>d2.mesec>>d2.godina;
    int denovi=razlika(d1,d2);
    cout<<"Razlikata vo denovi e "<<denovi<<endl;
    return 0;
}