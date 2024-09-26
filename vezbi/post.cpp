#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

/*
YOUR CODE HERE
DO NOT MODIFY THE FUNCTIONS BELOW!!!
*/

class Post {
protected:
    string username;
    string content;
    bool hasImage;
    int likes;
public:
    Post(string username="", string content="", bool hasImage=true, int likes=0) {
        this->username=username;
        this->content=content;
        this->hasImage=hasImage;
        this->likes=likes;
    }

    virtual double popularity() const =0;
    virtual void print()=0;

    bool operator<(const Post &p) const {
        return popularity() < p.popularity();
    }
    bool operator>(const Post &p) const {
        return p<*this;
    }
    bool operator<=(const Post &p) const {
        return !(p<*this);
    }
    bool operator>=(const Post &p) const {
        return !(*this<p);
    }

    friend double mostPopularPostWithPhoto(Post **posts, int n);
};

class FacebookPost : public Post {
private:
    int shares;
public:
    FacebookPost(string username="", string content="", bool hasImage=true, int likes=0, int shares=0)
    : Post(username, content, hasImage, likes) {
        this->shares=shares;
    }

    double popularity() const override {
        double p=likes*shares;
        if(hasImage) {
            p*=1.2;
        }
        return p;
    }

    void print() {
        cout<<"Facebook post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(hasImage) {
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
    TwitterPost(string username="", string content="", bool hasImage=true, int likes=0, int retweets=0, int replies=0)
    : Post(username, content, hasImage, likes) {
        this->retweets=retweets;
        this->replies=replies;
    }

    double popularity() const override {
        double p=likes*retweets*replies;
        if(hasImage) {
            p*=1.1;
        }
        if(content.find("#crypto")!=-1) {
            p*=1.2;
        }
        return p;
    }

    void print() {
        cout<<"Twitter post"<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Content: "<<content<<endl;
        if(hasImage) {
            cout<<"With photo"<<endl;
        } else {
            cout<<"Without photo"<<endl;
        }
        cout<<"Likes: "<<likes<<" Retweets: "<<retweets<<" Replies: "<<replies<<endl;
        cout<<"Popularity: "<<popularity()<<endl;
    }
};

double mostPopularPostWithPhoto(Post **posts, int n) {
    double max=-1;
    for(int i=0;i<n;i++) {
        if(posts[i]->hasImage && posts[i]->popularity()>max) {
            max=posts[i]->popularity();
        }
    }
    return max;
}

Post *leastPopularTwitterPost(Post **posts, int n) {
    Post *least= nullptr;
    for (int i=0;i<n;i++) {
        if(dynamic_cast<TwitterPost*>(posts[i])) {
            if(least==nullptr || posts[i]->popularity()<least->popularity()) {
                least=posts[i];
            }
        }
    }
    return least;
}

Post *readFbPost() {
    string username;
    string content;
    bool photo;
    int likes;
    int shares;
    cin.ignore();
    getline(std::cin, username);
    getline(std::cin, content);
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
    getline(std::cin, username);
    getline(std::cin, content);
    cin >> photo >> likes >> retweets >> replies;
    return new TwitterPost(username, content, photo, likes, retweets, replies);
}

Post **readMultiplePosts(int *n) {

    cin >> *n;
    Post **posts = new Post *[*n];
    for (int i = 0; i < *n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            posts[i] = readFbPost();
        } else {
            posts[i] = readTwPost();
        }
    }
    return posts;
}

int main() {
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test FacebookPost" << endl;
        Post *post = readFbPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 2) {
        cout << "Test TwitterPost" << endl;
        Post *post = readTwPost();
        cout << "Popularity: " << post->popularity() << endl;
        post->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        Post **posts = readMultiplePosts(&n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*posts[i]) >= (*posts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        Post **posts = readMultiplePosts(&n);
        for (int i = 0; i < n; i++) {
            posts[i]->print();
            cout << endl;
        }
        cout << "The most popular post with photo has a popularity of: " << mostPopularPostWithPhoto(posts, n) << endl;

        cout << "The least popular twitter post is: " << endl;
        Post * result = leastPopularTwitterPost(posts,n);
        if (result== nullptr){
            cout << "None";
        } else {
            result->print();
        }
    }

    return 0;
}