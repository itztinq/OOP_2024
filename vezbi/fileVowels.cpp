#include<iostream>
#include<cstring>
#include<fstream>
#include<cctype>
using namespace std;

bool isVowel(char c) {
    c=tolower(c);
    switch(c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

int main() {
    ifstream fin("C:\\Users\\tinas\\CLionProjects\\OOP-23-24\\Primer.txt");
    if(!fin.is_open()) {
        cout<<"The file cannot be opened!"<<endl;
        return -1;
    }

    char c;
     int vowelsPerLine=0;
     int linesWithMoreThan10Vowels=0;
     int total=0;
     while(fin.get(c)) {
         if(isVowel(c)) {
             cout<<c;
             vowelsPerLine++;
             total++;
         }
         if(c=='\n') {
             cout<<endl;
             if(vowelsPerLine>10){
                 linesWithMoreThan10Vowels++;
             }
             vowelsPerLine=0;
         }
     }
     if(vowelsPerLine>10) {
         linesWithMoreThan10Vowels++;
     }

     cout<<"A total of "<<linesWithMoreThan10Vowels<<" rows have more than 10 vowels."<<endl;
     cout<<"The file has a total of "<<total<<" vowels."<<endl;
     return 0;
}