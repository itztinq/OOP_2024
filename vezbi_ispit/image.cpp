#include<iostream>
#include<cstring>
using namespace std;

class Image {
protected:
    char *name;
    char username[50];
    int width, height;
public:
    Image (char *name = "untitled", char *username = "unknown", int width = 800, int height = 800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->username, username);
        this->width = width;
        this->height = height;
    }

    Image (const Image &i) {
        this->name = new char[strlen(i.name) + 1];
        strcpy(this->name, i.name);
        strcpy(this->username, i.username);
        this->width = i.width;
        this->height = i.height;
    }

    Image &operator = (const Image &i) {
        if (this != &i) {
            delete [] name;
            this->name = new char[strlen(i.name) + 1];
            strcpy(this->name, i.name);
            strcpy(this->username, i.username);
            this->width = i.width;
            this->height = i.height;
        }
        return *this;
    }

    virtual ~Image() {
        delete[] name;
    }

    virtual int fileSize() const {
        return height * width * 3;
    }

    bool operator > (const Image &i) const {
        return fileSize() > i.fileSize();
    }

    friend ostream &operator << (ostream &o, const Image &i) {
        return o<<i.name<<" "<<i.username<<" "<<i.fileSize()<<endl;
    }
};

class TransparentImage : public Image {
private:
    bool transparent;
public:
    TransparentImage(char *name = "untitled", char *username = "unknown", int width = 800, int height = 800, bool transparent = false)
      : Image(name, username, width, height) {
        this->transparent = transparent;
    }

    int fileSize() const override {
        if (transparent == true) {
            return width * height * 4;
        } else {
            return (width * height) + (width * height) / 8;
        }
    }

    friend ostream &operator << (ostream &o, const TransparentImage &ti) {
        return o<<ti.name<<" "<<ti.username<<" "<<ti.fileSize()<<endl;
    }

};

class Folder {
    char name[255];
    char username[50];
    Image **images;
    int capacity;
    int num;
public:
    Folder (char *name = "", char *username = "unknown") {
        strcpy(this->name, name);
        strcpy(this->username, username);
        this->num = 0;
        images = new Image *[num];
    }

    Folder (const Folder &f) {
        strcpy(this->name, f.name);
        strcpy(this->username, f.username);
        this->num = f.num;
        this->images = new Image *[f.num+1];
        for(int i = 0; i < f.num; i++) {
            images[i] = new Image(*f.images[i]);
        }
    }

    Folder &operator = (const Folder &f) {
        if (this != &f) {
            for(int i = 0; i < f.num; i++) {
                delete images[i];
            }
            delete [] images;

            strcpy(this->name, f.name);
            strcpy(this->username, f.username);
            this->num = f.num;
            this->images = new Image *[f.num+1];
            for(int i = 0; i < f.num; i++) {
                images[i] = new Image(*f.images[i]);
            }
        }
        return *this;
    }

    ~Folder() {
        for(int i = 0; i < num; i++) {
            delete images[i];
        }
        delete[] images;
    }

    int folderSize() const {
        int total = 0;
        for (int i = 0; i < num; i++) {
            total += images[i]->fileSize();
        }
        return total;
    }

    Image *getMaxFile() const {
        Image *maxFile = images[0];
        for (int i = 1; i < num; i++) {
            if(*images[i] > *maxFile) {
                maxFile = images[i];
            }
        }
        return maxFile;
    }

    Folder &operator += (Image &i) {
        if(num < 100) {
            images[num++] = &i;
        }
        return *this;
    }

    friend ostream &operator << (ostream &o, const Folder &f) {
        o<<f.name<<" "<<f.username<<endl<<"-- "<<endl;
        for (int i = 0; i < f.num; i++) {
            o<<*f.images[i];
        }
        o<<"--"<<endl<<"Folder size: "<<f.folderSize()<<endl;
        return o;
    }

    Image *operator [] (int index) const {
        if(index < 0 || index >= num) {
            return nullptr;
        }
        return images[index];
    }
};

Folder max_folder_size(Folder f[], int numFolders) {
    Folder *maxFolder = &f[0];
    for (int i = 0; i < numFolders; i++) {
        if(f[i].folderSize() > maxFolder->folderSize()) {
            maxFolder = &f[i];
        }
    }
    return *maxFolder;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
}