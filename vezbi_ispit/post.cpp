#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class Post {
protected:
    string username;
    string content;
    bool photo;
    int likes;
public:
    Post(const string &username = "", const string &content = "", bool photo = false, int likes = 0) {
        this->username = username;
        this->content = content;
        this->photo = photo;
        this->likes = likes;
    }

    virtual double popularity() const = 0;

    virtual void print() = 0;

    bool operator<(const Post &rhs) const {
        return popularity() < rhs.popularity();
    }

    bool operator>(const Post &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Post &rhs) const {
        return popularity() <= rhs.popularity();
    }

    bool operator>=(const Post &rhs) const {
        return popularity() >= rhs.popularity();
    }

    friend double mostPopularPostWithPhoto(Post **posts, int n);
};

class FacebookPost : public Post {
private:
    int shares;
public:
    FacebookPost (const string &username = "", const string &content = "", bool photo = false, int likes = 0, int shares = 0)
        : Post(username, content, photo, likes) {
        this->shares = shares;
    }

    double popularity() const override {
        double total = likes * shares;
        if(photo) {
            return total *= 1.20; // 20% zgolemi
        }

        return total;
    }

    void print() override {
        cout<<"Facebook post: "<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(photo) {
            cout<<"With photo"<<endl;
        } else {
            cout<<"Without photo"<<endl;
        }
        cout<<"Likes: "<<likes<<" Shares: "<<shares<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

class TwitterPost : public Post {
private:
    int retweets;
    int replies;
public:
    TwitterPost (const string &username = "", const string &content = "", bool photo = false, int likes = 0, int retweets = 0, int replies = 0)
        : Post(username, content, photo, likes) {
        this->retweets = retweets;
        this->replies = replies;
    }

    double popularity() const override {
        double total = likes * retweets * replies;
        if(photo) {
            total *= 1.1; // 10% zgolemi
        }

        if(content.find('#crtpto') != -1) {
            return total *= 1.2;
        }

        return total;
    }

    void print() override {
        cout<<"Twitter post: "<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(photo) {
            cout<<"With photo"<<endl;
        } else {
            cout<<"Without photo"<<endl;
        }
        cout<<"Likes: "<<likes<<" "<<"Retweets: "<<retweets<<" Replies: "<<replies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

double mostPopularPostWithPhoto(Post **posts, int n) {
    Post *mostPopular = posts[0];
    for(int i = 1; i < n; i++) {
        if(posts[i]->photo && posts[i]->popularity() > mostPopular->popularity()) {
            mostPopular = posts[i];
        }
    }
    return mostPopular->popularity();
}

Post *leastPopularTwitterPost(Post **posts, int n) {
    Post *leastPopular = nullptr;
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<TwitterPost*>(posts[i])) {
            if(leastPopular == nullptr || posts[i]->popularity() < leastPopular->popularity()) {
                leastPopular = posts[i];
            }
        }
    }

    return leastPopular;
}

Post *readFbPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int shares;
    cin.ignore();
    getline(cin, username);
    getline(cin, content);
    cin >> photo >> likes >> shares;
    return new FacebookPost(username, content, photo, likes, shares);
}

Post *readTwPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int retweets;
    int replies;
    cin.ignore();
    getline(cin, username);
    getline(cin, content);
    cin >> photo >> likes >> retweets >> replies;
    return new TwitterPost(username, content, photo, likes, retweets, replies);
}

Post **readMultiplePosts(int *n) {
    cin>>*n;
    Post **posts = new Post*[*n];
    for(int i = 0; i < *n; i++) {
        int type;
        cin>>type;
        if(type == 1) {
            posts[i] = readFbPost();
        } else {
            posts[i] = readTwPost();
        }
    }
    return posts;
}

int main() {
    int testCase;
    cin>>testCase;

    if(testCase == 1) {
        cout<<"Test FacebookPost"<<endl;
        Post *post = readFbPost();
        cout<<"Popularity: "<<post->popularity()<<endl;
        post->print();
    } else if(testCase == 2) {
        cout<<"Test TwitterPost"<<endl;
        Post *post = readTwPost();
        cout<<"Popularity: "<<post->popularity()<<endl;
        post->print();
    } else if(testCase == 3) {
        cout<<"Test operator >="<<endl;
        int n;
        Post **posts = readMultiplePosts(&n);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    if((*posts[i]) >= (*posts[j])) {
                        cout<<i<<" >= "<<j<<endl;
                    } else {
                        cout<<i<<" < "<<j<<endl;
                    }
                }
            }
        }
    } else {
        int n;
        cin>>n;
        Post **posts = readMultiplePosts(&n);
        for(int i = 0; i < n; i++) {
            posts[i]->print();
            cout<<endl;
        }
        cout<<"The most popular post with photo has a popularity "<<endl;
        cout<<"The least popular Twitter post is: "<<endl;
        Post *result = leastPopularTwitterPost(posts, n);
        if(result != nullptr) {
            result->print();
        } else {
            cout<<"None"<<endl;
        }
    }
    return 0;
}