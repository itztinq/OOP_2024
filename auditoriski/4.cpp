#include <iostream>
#include <cmath>
using namespace std;

class Triagolnik{
private:
    float a,b,c;
public:
    Triagolnik(float a, float b, float c){
        this->a=a;
        this->b=b;
        this->c=c;
    }
    ~Triagolnik(){}
    float perimetar(){
        return a+b+c;
    }
    float plostina(){
        float s=(a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }
};
int main(){
    float a,b,c;
    cin>>a>>b>>c;
    Triagolnik t(a,b,c);
    cout<<"Perimetar: "<<t.perimetar()<<endl;
    cout<<"Plostina: "<<t.plostina();
    return 0;
}