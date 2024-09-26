#include<iostream>
#include<cstring>
using namespace std;

class Word {
private:
    char *content;
    int frequency;
public:
    Word (char *content="", int frequency=1) {
        this->content = new char[strlen(content)+1];
        strcpy(this->content, content);
        this->frequency = frequency;
    }

    Word (const Word &w) {
        this->content = new char[strlen(w.content)+1];
        strcpy(this->content, w.content);
        this->frequency = w.frequency;
    }

    Word &operator = (const Word &w) {
        if (this != &w) {
            delete [] content;
            this->content = new char[strlen(w.content)+1];
            strcpy(this->content, w.content);
            this->frequency = w.frequency;
        }
        return *this;
    }

    ~Word () {
        delete [] content;
    }

    void print() {
        cout<<content<<" "<<frequency<<endl;
    }

    Word &increaseFrequency() {
        ++frequency;
        return *this;
    }

    bool equals(const Word &w) {
        if(strlen(content) != strlen(w.content)) return false;

        for(int i=0;i<strlen(content);i++) {
            if(tolower(content[i]) != tolower(w.content[i])) return false;
        }

        return true;
    }

    int getFrequency() {
        return frequency;
    }
};

class Text {
private:
    Word *words;
    int n;
public:
    Text () {
        this->n = 0;
        this->words = new Word[0];
    }

    Text (const Text &t) {
        this->n = t.n;
        this->words = new Word[this->n+1];
        for(int i=0; i<n; i++) {
            this->words[i] = t.words[i];
        }
    }

    Text &operator = (const Text &t) {
        if(this != &t) {
            delete [] words;
            this->n = t.n;
            this->words = new Word[this->n+1];
            for(int i=0; i<n; i++) {
                this->words[i] = t.words[i];
            }
        }
        return *this;
    }

    ~Text () {
        delete [] words;
    }

    void addWord(const Word &w) {
        for(int i=0; i<n; i++) {
            if(words[i].equals(w)) {
                words[i].increaseFrequency();
                return;
            }
        }

        //shablonski e ovoj del
        Word *tmp = new Word[n+1];
        for(int i=0; i<n; i++) {
            tmp[i] = words[i]; //se povikuva operator =
        }
        tmp[n++] = w;
        delete [] words;
        words = tmp;
    }

    void print() {
        for(int i=0; i<n; i++) {
            words[i].print();
        }
    }

    int getFrequencyFor(char *word) {
        for(int i=0; i<n; i++) {
            if(words[i].equals(word)) {
                return words[i].getFrequency();
            }
        }
        return -1;
    }
};

int main() {
    //daden od tamu me mrzeshe da prepisham :)
    return 0;
}