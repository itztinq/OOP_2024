#include<iostream>
#include<cmath>
using namespace std;

class Triagolnik {
private:
    int a, b, c;
public:
    Triagolnik(int a=0, int b=0, int c=0) {
        this->a=a;
        this->b=b;
        this->c=c;
    }
    ~Triagolnik() {}

    int perimetar() {
        return a+b+c;
    }
    float plostina() {
        float s=(a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }
};

int main() {
    int a, b, c;
    cin>>a>>b>>c;
    Triagolnik t(a,b,c);
    cout<<"Perimetar: "<<t.perimetar()<<endl;
    cout<<"Plostina: "<<t.plostina()<<endl;
    return 0;
}