#include<iostream>
#include<cstring>
using namespace std;

class ExistingGame {
private:
    char msg[300];
public:
    ExistingGame(char *msg = "") {
        strcpy(this->msg, msg);
    }

    void message() {
        cout << msg << endl;
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool onSale;
public:
    Game (char *name = "", float price = 0, bool onSale = false) {
        strcpy(this->name, name);
        this->price = price;
        this->onSale = onSale;
    }

    bool operator == (const Game &g) {
        return strcmp(this->name, g.name) == 0;
    }

    virtual float calculatePrice() {
        if(onSale) {
            return price * 0.3;
        } else return price;
    }

    friend ostream &operator << (ostream &o, const Game &g) {
        o<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.onSale) {
            o<<", bought on sale";
        }
        return o;
    }

    friend istream &operator >> (istream &i, Game &g) {
        i.get();
        i.getline(g.name, 100);
        i>>g.price>>g.onSale;
        return i;
    }

    virtual bool isSubscription() {
        return false;
    }

    virtual ~Game() {};
};

class SubscriptionGame : public Game {
public:
    double monthlyFee;
    int month;
    int year;
public:
    SubscriptionGame(char *name = "", double price = 0, bool onSale = false, double monthlyFee = 0, int month = 0, int year = 0)
        : Game(name, price, onSale) {
        this->monthlyFee = monthlyFee;
        this->month = month;
        this->year = year;
    }

    bool isSubscription() override {
        return true;
    }

    float calculatePrice() override {
        int monthsPassed = (2018 - year) * 12 + (5 - month);
        return Game::calculatePrice() + monthsPassed * monthlyFee;
    }

    friend ostream &operator << (ostream &o, const SubscriptionGame &sg) {
        o<<(const Game&)sg;
        o<<", monthly fee: $"<<sg.monthlyFee<<", purchased: "<<sg.month<<"-"<<sg.year<<endl;
        return o;
    }

    friend istream &operator >> (istream &i, SubscriptionGame &sg) {
        i>>(Game&)sg;
        i>>sg.monthlyFee>>sg.month>>sg.year;
        return i;
    }
};

class User {
private:
    char username[100];
    Game **games;
    int n;
public:
    User (char *username = "") {
        strcpy(this->username, username);
        n = 0;
        games = 0;
    }

    User (const User &u) {
        strcpy(this->username, u.username);
        this->n = u.n;
        this->games = new Game *[this->n];
        for(int i = 0; i < this->n; i++) {
            this->games[i] = u.games[i];
        }
    }

    User &operator = (const User &u) {
        if(this != &u) {
            delete [] games;
            strcpy(this->username, u.username);
            this->n = u.n;
            this->games = new Game *[this->n];
            for(int i = 0; i < this->n; i++) {
                this->games[i] = u.games[i];
            }
        }
    }

    ~User() {
        for(int i = 0; i < this->n; i++) {
            delete [] games[i];
        }
        delete [] games;
    }

    User &operator += (Game &g) {
        for(int i = 0; i < this->n; i++) {
            if(*games[i] == g) {
                throw ExistingGame("The game is already in the collection");
            }
        }

        Game **tmp = new Game *[this->n+1];
        for(int i = 0; i < this->n; i++) {
            tmp[i] = games[i];
        }
        tmp[n++] = &g;
        delete [] games;
        games = tmp;
        return *this;
    }

    float total_spent() const {
        float total = 0;
        for(int i = 0; i < n; i++) {
            total += games[i]->calculatePrice();
        }
        return total;
    }

    friend ostream &operator << (ostream &o, User &u) {
        o<<endl;
        o<<"User: "<<u.username<<endl;
        for(int i = 0; i < u.n; i++) {
            o<<"- "<<*u.games[i]<<endl;
        }
        return o;
    }
};

int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u<<endl;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}