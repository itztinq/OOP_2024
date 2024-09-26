#include<iostream>
#include<cstring>
using namespace std;

enum Size {
    small, big, family
};

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    double basePrice;
public:
    Pizza (char *name = "", char *ingredients = "", double basePrice = 0) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->basePrice = basePrice;
    }

    virtual ~Pizza() {}

    virtual double price() const = 0;

    bool operator < (const Pizza &p) const {
        return price() < p.price();
    }

    friend ostream &operator << (ostream &o, const Pizza &p) {
        return o << p.name <<": "<< p.ingredients << p.price();
    }

};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza (char *name = "", char *ingredients = "", double basePrice = 0, Size size = small)
        : Pizza (name, ingredients, basePrice) {
        this->size = size;
    }

    double price() const {
        switch (size) {
            case small: return basePrice * 1.10; break;
            case big: return basePrice * 1.20; break;
            case family: return basePrice * 1.30; break;
        }
        return basePrice;
    }

    friend ostream& operator << (ostream &o, const FlatPizza &flat) {
        o<<(Pizza&)flat<<", ";
        switch(flat.size) {
            case small: o<<"small"; break;
            case big: o<<"big"; break;
            case family: o<<"family"; break;
        }
        o<<" - "<<flat.price()<<endl;
        return o;
    }
};

class FoldedPizza : public Pizza {
private:
    bool whiteFlour;
public:
    FoldedPizza (char *name = "", char *ingredients = "", double basePrice = 0, bool whiteFlour = false)
        : Pizza (name, ingredients, basePrice) {
        this->whiteFlour = whiteFlour;
    }

    void setWhiteFlour (bool whiteFlour) {
        this->whiteFlour = whiteFlour;
    }

    double price() const {
        if(whiteFlour) {
            return basePrice * 1.10;
        } else {
            return basePrice * 1.30;
        }
    }

    friend ostream& operator << (ostream &o, const FoldedPizza &folded) {
        o<<(Pizza&)folded<<", ";
        if(folded.whiteFlour == true) {
            o<<"wf";
        } else {
            o<<"nwf";
        }
        o<<" - "<<folded.price()<<endl;
        return o;
    }
};

void expensivePizza(Pizza **pizza, int n) {
    Pizza *najskapa = pizza[0];
    for(int i = 1; i < n; i++) {
        if(*najskapa < *pizza[i]) {
            najskapa = pizza[i];
        }
    }
    if(auto *flatPizza = dynamic_cast<FlatPizza*>(najskapa)) {
        cout<<*flatPizza<<endl;
    } else if(auto *foldedPizza = dynamic_cast<FoldedPizza*>(najskapa)) {
        cout<<*foldedPizza<<endl;
    }
}

int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);

  }
  return 0;
}
