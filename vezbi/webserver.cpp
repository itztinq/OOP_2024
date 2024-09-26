#include<iostream>
#include<cstring>
using namespace std;

class WebPage {
private:
    char url[100];
    char *content;
public:
    WebPage(char *url="finki.ukim.mk", char *content="Web sajt na FINKI") {
        strcpy(this->url, url);
        this->content = new char[strlen(content)+1];
        strcpy(this->content, content);
    };

    WebPage(WebPage &wp) {
        strcpy(this->url, wp.url);
        this->content = new char[strlen(wp.content)+1];
        strcpy(this->content, wp.content);
    }

    WebPage & operator=(WebPage &wp) {
        if(this!=&wp) {
            delete [] content;
            strcpy(this->url, wp.url);
            this->content = new char[strlen(wp.content)+1];
            strcpy(this->content, wp.content);
        }
        return *this;
    }

    ~WebPage() {
        delete [] content;
    }

    void print() {
        cout<<url<<endl<<content<<endl;
    }

    bool equal (WebPage &wp) {
        return strcmp(this->url, wp.url)==0;
    }
};

class WebServer {
private:
    char name[30];
    WebPage *pages;
    int size;
public:
    WebServer (char *name="FINKI") {
        strcpy(this->name, name);
        this->size = 0;
        pages = new WebPage[size];
    }

    WebServer (const WebServer &ws) {
        strcpy(this->name, ws.name);
        this->size = ws.size;
        pages = new WebPage[size];
        for (int i = 0; i < size; i++) {
            this->pages[i] = ws.pages[i];
        }
    }

    WebServer & operator=(const WebServer &ws) {
        if (this!=&ws) {
            delete [] this->pages;
            strcpy(this->name, ws.name);
            this->size = ws.size;
            pages = new WebPage[size];
            for (int i = 0; i < size; i++) {
                this->pages[i] = ws.pages[i];
            }
        }
        return *this;
    }

    ~WebServer() {
        delete [] pages;
    }

    void addPage(WebPage &wp) {
        for(int i=0; i<size; i++) {
            if(pages[i].equal(wp)) {
                return;
            }
        }

        WebPage *tmp = new WebPage[size+1];
        for(int i=0; i<size; i++) {
            tmp[i] = pages[i];
        }
        tmp[size++] = wp;
        delete [] pages;
        pages = tmp;
    }

    void print() {
        cout<<name<<endl;
        for(int i=0; i<size; i++) {
            pages[i].print();
        }
    }
};

int main() {
    WebPage wp;

    WebPage copy(wp);
    WebPage testAssigment;
    testAssigment=wp;

    wp.print(); //default constructor
    copy.print(); //copy constructor
    testAssigment.print(); //operator =

    WebServer ws("FINKI");
    ws.addPage(wp);

    WebPage courses("courses.finki.ukim.mk", "Moodle za potrebite na FINKI");
    ws.addPage(copy);
    ws.addPage(testAssigment);
    ws.print();

    return 0;
}