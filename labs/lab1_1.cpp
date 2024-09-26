#include<iostream>
using namespace std;

struct Transakcija{
    int id;
    int pl_suma;
    int provizija;
    bool DebitnaKreditna;
};

void rez(Transakcija *t,int n){
    bool flag=false;
    for(int i=0;i<n;i++){
        int suma=0;
        if(t[i].DebitnaKreditna==1){
            flag=true;
            suma=t[i].pl_suma+t[i].provizija;
            cout<<t[i].id<<" "<<suma<<endl;
        }
    }
    if(flag==false){
        cout<<"No credit card transaction"<<endl;
    }
}

int main(){
    Transakcija t[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>t[i].id>>t[i].pl_suma>>t[i].provizija>>t[i].DebitnaKreditna;
    }
    rez(t,n);
    return 0;
}
