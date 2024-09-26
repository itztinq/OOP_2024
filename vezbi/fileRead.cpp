#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main() {
    ifstream fin("C:\\Users\\tinas\\CLionProjects\\OOP-23-24\\vezbi\\vlezna.txt");
    ofstream fout("C:\\Users\\tinas\\CLionProjects\\OOP-23-24\\vezbi\\izlezna.txt");
    if(!fin.is_open()) {
        cout<<"File vlezna.txt cannot be opened!"<<endl;
        return -1;
    }
    if(!fout.is_open()) {
        cout<<"File izlezna.txt cannot be opened!"<<endl;
        return -1;
    }

    string line;
    while(getline(fin, line)) {
        int num=0;
        for(char c:line) {
            if(!isspace(c)) {
                num++;
            }
        }
        fout<<num<<endl;
        fout<<line<<endl;
    }
    return 0;
}