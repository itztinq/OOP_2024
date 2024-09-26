#include<iostream>
#include<cstring>
using namespace std;

class TennisPlayer {
protected:
    string name;
    string surname;
    bool league;
public:
    TennisPlayer(string name="", string surname="", bool league=false) {
        this->name=name;
        this->surname=surname;
        this->league=league;
    }

    TennisPlayer(const TennisPlayer &t) {
        this->name=t.name;
        this->surname=t.surname;
        this->league=t.league;
    }

    friend ostream &operator<<(ostream &o, const TennisPlayer &t) {
        o<<"TennisPlayer: "<<t.name<<" "<<t.surname<<" Plays in league? "<<(t.league? "yes" : "no");
        return o;
    }

    void setLeague(bool league) {
        this->league=league;
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;
public:
    RankedTennisPlayer(string name = "", string surname = "", bool league = false, int rank = 0)
    : TennisPlayer(name, surname, league) {
        this->rank=rank;
    }

    RankedTennisPlayer(const TennisPlayer &t, int rank) : TennisPlayer(t) {
        this->rank=rank;
    }

    RankedTennisPlayer(const TennisPlayer &t) : TennisPlayer(t) {
        this->rank=rank;
    }

    friend ostream &operator<<(ostream &o, const RankedTennisPlayer &rtp) {
        o<<"Ranked ";
        TennisPlayer tmp(rtp);
        o<<tmp<<", is ranked "<<rtp.rank;
        return o;
    }
};

int main() {
    TennisPlayer tp("Jovana", "Jovanovska", false);
    cout<<tp<<endl;

    RankedTennisPlayer rtp("Novak", "Gjokovic", 1);
    cout<<rtp<<endl;

    rtp.setLeague(false);
    cout<<rtp<<endl;

    return 0;
}